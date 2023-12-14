/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <string>
#include <cassert>

#include "DynIntegrator.h"
#include "BasicIntegrator.h"
#include "SystemSolver.h"
#include "Solver.h"
#include "Item.h"
#include "SingularMatrixError.h"
#include "SimulationStoppingError.h"
#include "TooSmallStepSizeError.h"
#include "TooManyTriesError.h"
#include "Constraint.h"
#include "Part.h"
#include "DiscontinuityError.h"
#include "BasicDAEIntegrator.h"

using namespace MbD;

void MbD::DynIntegrator::assignEquationNumbers()
{
	//"Equation order is p,q,s,u,w,mubar,mu."

	auto parts = system->parts();
	//auto contactEndFrames = system->contactEndFrames();
	//auto uHolders = system->uHolders();
	auto constraints = system->allConstraints();
	ncon = (int)constraints->size();
	auto eqnNo = 0;
	for (auto& part : *parts) {
		part->ipX = eqnNo;
		eqnNo = eqnNo + 3;
		part->ipE = eqnNo;
		eqnNo = eqnNo + 4;
	}
	for (auto& part : *parts) {
		part->iqX(eqnNo);
		eqnNo = eqnNo + 3;
		part->iqE(eqnNo);
		eqnNo = eqnNo + 4;
	}
	//for (auto& endFrm : *contactEndFrames) {
	//	endFrm->is(eqnNo);
	//	eqnNo = eqnNo + endFrm->sSize();
	//}
	//for (auto& uHolder : *uHolders) {
	//	uHolder->iu(eqnNo);
	//	eqnNo += 1;
	//}
	for (auto& con : *constraints) {
		con->iG = eqnNo;
		eqnNo += 1;
	}
	neqn = eqnNo;
}

void MbD::DynIntegrator::checkForDiscontinuity()
{
	//"Check for discontinuity in (tpast,t] or [t,tpast) if integrating 
	//backward."

	auto t = integrator->t;
	auto tprevious = integrator->tprevious();
	auto epsilon = std::numeric_limits<double>::epsilon();
	double tstartNew;
	if (direction == 0) {
		tstartNew = epsilon;
	}
	else {
		epsilon = std::abs(t) * epsilon;
		tstartNew = ((direction * t) + epsilon) / direction;
	}
	system->partsJointsMotionsForcesTorquesDo([&](std::shared_ptr<Item> item) { tstartNew = item->checkForDynDiscontinuityBetweenand(tprevious, tstartNew); });
	if ((direction * tstartNew) > (direction * t)) {
		//"No discontinuity in step"
		return;
	}
	else {
		this->checkForOutputThrough(tstartNew);
		this->interpolateAt(tstartNew);
		system->tstartPastsAddFirst(tstart);
		system->tstart = tstartNew;
		system->toutFirst = tout;
		auto discontinuityTypes = std::make_shared<std::vector<DiscontinuityType>>();
		system->partsJointsMotionsForcesTorquesDo([&](std::shared_ptr<Item> item) { item->discontinuityAtaddTypeTo(tstartNew, discontinuityTypes); });
		this->throwDiscontinuityError("", discontinuityTypes);
	}
}

void MbD::DynIntegrator::checkForOutputThrough(double t)
{
	//"Inclusive of t."

	auto tlimit = t;
	auto thereIsOutput = false;
	if (direction * tend <= (direction * tlimit)) {
		integrator->_continue = false;
		tlimit = tend + (0.1 * direction * hout);
	}
	while (direction * tout <= (direction * tlimit)) {
		thereIsOutput = true;
		auto yout = integrator->yDerivat(0, tout);
		auto ydotout = integrator->yDerivat(1, tout);
		auto yddotout = integrator->yDerivat(2, tout);
		system->time(tout);
		system->partsJointsMotionsDo([&](std::shared_ptr<Item> item) {
			item->setpqsumu(yout);
			item->setpqsumudot(ydotout);
			item->setpqsumuddot(yddotout);
			});
		preDAEOutput();
		system->output();
		tout = tout + (direction * hout);
	}
	if (thereIsOutput) {
		//"Reset system to integrator time."
		system->time(integrator->t);
		auto integ = std::static_pointer_cast<BasicDAEIntegrator>(integrator);
		auto& y = integ->y;
		auto& ydot = integ->ydot;
		system->partsJointsMotionsDo([&](std::shared_ptr<Item> item) {
			item->setpqsumu(y);
			item->setpqsumudot(ydot);
			});
		postDAEOutput();
	}
}

void MbD::DynIntegrator::fillF(FColDsptr col)
{
	system->partsJointsMotionsForcesTorquesDo([&](std::shared_ptr<Item> item) { item->fillDynError(col); });
}

void MbD::DynIntegrator::fillpFpy(SpMatDsptr mat)
{
	system->partsJointsMotionsForcesTorquesDo([&](std::shared_ptr<Item> item) { item->fillpFpy(mat); });
}

void MbD::DynIntegrator::fillpFpydot(SpMatDsptr mat)
{
	system->partsJointsMotionsForcesTorquesDo([&](std::shared_ptr<Item> item) { item->fillpFpydot(mat); });
}

void MbD::DynIntegrator::preRun()
{
	std::string str("MbD: Solving for quasi kinematic acceleration.");
	system->logString(str);
	system->partsJointsMotionsForcesTorquesDo([&](std::shared_ptr<Item> item) { item->preDyn(); });
}

void MbD::DynIntegrator::run()
{
	try {
		try {
			try {
				IntegratorInterface::run();
			}
			catch (SingularMatrixError ex) {
				std::stringstream ss;
				ss << "MbD: Solver has encountered a singular matrix." << std::endl;
				ss << "MbD: Check to see if a massless or a very low mass part is under constrained." << std::endl;
				ss << "MbD: Check to see if the system is in a locked position." << std::endl;
				ss << "MbD: Check to see if the error tolerance is too demanding." << std::endl;
				ss << "MbD: Check to see if a curve-curve is about to have multiple contact points." << std::endl;
				auto str = ss.str();
				this->logString(str);
				throw SimulationStoppingError("");
			}
		}
		catch (TooSmallStepSizeError ex) {
			std::stringstream ss;
			ss << "MbD: Step size is prevented from going below the user specified minimum." << std::endl;
			ss << "MbD: Check to see if the system is in a locked position." << std::endl;
			ss << "MbD: Check to see if a curve-curve is about to have multiple contact points." << std::endl;
			ss << "MbD: If they are not, lower the permitted minimum step size." << std::endl;
			auto str = ss.str();
			this->logString(str);
			throw SimulationStoppingError("");
		}
	}
	catch (TooManyTriesError ex) {
		std::stringstream ss;
		ss << "MbD: Check to see if the error tolerance is too demanding." << std::endl;
		auto str = ss.str();
		this->logString(str);
		throw SimulationStoppingError("");
	}
}

void MbD::DynIntegrator::fillY(FColDsptr y)
{
	system->partsJointsMotionsDo([&](std::shared_ptr<Item> item) { item->fillpqsumu(y); });
}

void MbD::DynIntegrator::fillYdot(FColDsptr ydot)
{
	system->partsJointsMotionsDo([&](std::shared_ptr<Item> item) { item->fillpqsumudot(ydot); });
}

void MbD::DynIntegrator::incrementTime(double aDouble)
{
	system->partsJointsMotionsForcesTorquesDo([](std::shared_ptr<Item> item) { item->storeDynState(); });
	system->time(aDouble);
}

void MbD::DynIntegrator::interpolateAt(double t)
{
	assert(false);
}

int MbD::DynIntegrator::iterMax()
{
	return system->iterMaxDyn;
}

void MbD::DynIntegrator::postDAECorrector()
{
	system->partsJointsMotionsForcesTorquesDo([](std::shared_ptr<Item> item) { item->postDynCorrector(); });
}

void MbD::DynIntegrator::postDAECorrectorIteration()
{
	assert(false);
}

void MbD::DynIntegrator::postDAEFirstStep()
{
	system->partsJointsMotionsForcesTorquesDo([](std::shared_ptr<Item> item) { item->postDynFirstStep(); });
	if (integrator->istep >= 0) {
		//"Noise make checking at the start unreliable."
		checkForDiscontinuity();
	}
	checkForOutputThrough(integrator->t);
}

void MbD::DynIntegrator::postDAEOutput()
{
	system->partsJointsMotionsForcesTorquesDo([](std::shared_ptr<Item> item) { item->postDynOutput(); });
}

double MbD::DynIntegrator::suggestSmallerOrAcceptFirstStepSize(double hnew)
{
	auto hnew2 = hnew;
	system->partsJointsMotionsForcesTorquesDo([&](std::shared_ptr<Item> item) { hnew2 = item->suggestSmallerOrAcceptDynFirstStepSize(hnew2); });
	return hnew2;
}

double MbD::DynIntegrator::suggestSmallerOrAcceptStepSize(double hnew)
{
	auto hnew2 = hnew;
	system->partsJointsMotionsForcesTorquesDo([&](std::shared_ptr<Item> item) { hnew2 = item->suggestSmallerOrAcceptDynStepSize(hnew2); });
	if (hnew2 > hmax) {
		hnew2 = hmax;
		Solver::logString("MbD: Step size is at user specified maximum.");
	}
	if (hnew2 < hmin) {
		std::stringstream ss;
		ss << "MbD: Step size " << hnew2 << " < " << hmin << "  user specified minimum.";
		auto str = ss.str();
		system->logString(str);
		throw TooSmallStepSizeError("");
	}
	return hnew2;
}

void MbD::DynIntegrator::updateForDAECorrector()
{
	system->partsJointsMotionsForcesTorquesDo([](std::shared_ptr<Item> item) { item->postDynCorrectorIteration(); });
}

void MbD::DynIntegrator::y(FColDsptr col)
{
	system->partsJointsMotionsDo([&](std::shared_ptr<Item> item) { item->setpqsumu(col); });
}

void MbD::DynIntegrator::ydot(FColDsptr col)
{
	system->partsJointsMotionsDo([&](std::shared_ptr<Item> item) { item->setpqsumudot(col); });
}

void MbD::DynIntegrator::throwDiscontinuityError(const char* chars, std::shared_ptr<std::vector<DiscontinuityType>> discontinuityTypes)
{
	throw DiscontinuityError(chars, discontinuityTypes);
}

void MbD::DynIntegrator::postDAEPredictor()
{
	system->partsJointsMotionsForcesTorquesDo([](std::shared_ptr<Item> item) { item->postDynPredictor(); });
}

void MbD::DynIntegrator::postDAEStep()
{
	system->partsJointsMotionsForcesTorquesDo([](std::shared_ptr<Item> item) { item->postDynStep(); });
	if (integrator->istep >= 0) {
		//"Noise make checking at the start unreliable."
		checkForDiscontinuity();
	}
	checkForOutputThrough(integrator->t);
}

void MbD::DynIntegrator::postRun()
{
	assert(false);
}

void MbD::DynIntegrator::preDAECorrector()
{
	system->partsJointsMotionsForcesTorquesDo([](std::shared_ptr<Item> item) { item->preDynCorrector(); });
}

void MbD::DynIntegrator::preDAECorrectorIteration()
{
	assert(false);
}

void MbD::DynIntegrator::preDAEFirstStep()
{
	assert(false);
}

void MbD::DynIntegrator::preDAEOutput()
{
	system->partsJointsMotionsForcesTorquesDo([](std::shared_ptr<Item> item) { item->preDynOutput(); });
}

void MbD::DynIntegrator::preDAEPredictor()
{
	system->partsJointsMotionsForcesTorquesDo([](std::shared_ptr<Item> item) { item->preDynPredictor(); });
}

void MbD::DynIntegrator::preDAEStep()
{
	assert(false);
}
