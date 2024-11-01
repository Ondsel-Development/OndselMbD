/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
//#include <iostream>

#include "AccNewtonRaphson.h"
#include "SystemSolver.h"
#include "Part.h"
#include "Constraint.h"
#include "SimulationStoppingError.h"
#include "GESpMatParPvPrecise.h"

using namespace MbD;

std::shared_ptr<AccNewtonRaphson> MbD::AccNewtonRaphson::With()
{
	auto inst = std::make_shared<AccNewtonRaphson>();
	inst->initialize();
	return inst;
}

void AccNewtonRaphson::askSystemToUpdate()
{
	system->partsJointsMotionsForcesTorquesDo([&](std::shared_ptr<Item> item) { item->postAccICIteration(); });
}

void AccNewtonRaphson::assignEquationNumbers()
{
	auto parts = system->parts();
	//auto contactEndFrames = system->contactEndFrames();
	//auto uHolders = system->uHolders();
	auto constraints = system->allConstraints();
	size_t eqnNo = 0;
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
	auto nEqns = eqnNo;	//C++ uses index 0.
	for (auto& con : *constraints) {
		con->iG = eqnNo;
		eqnNo += 1;
	}
	//auto lastEqnNo = eqnNo - 1;
	nEqns = eqnNo;	//C++ uses index 0.
	n = nEqns;
}

void AccNewtonRaphson::fillPyPx()
{
	pypx->zeroSelf();
	system->partsJointsMotionsForcesTorquesDo([&](std::shared_ptr<Item> item) {
		item->fillAccICIterJacob(pypx);
		});
}

void AccNewtonRaphson::fillY()
{
	y->zeroSelf();
	system->partsJointsMotionsForcesTorquesDo([&](std::shared_ptr<Item> item) {
		item->fillAccICIterError(y);
		//std::cout << item->name << *y << std::endl;
		});
	//std::cout << "Final" << *y << std::endl;
}

void AccNewtonRaphson::incrementIterNo()
{
	iterNo++;
	if (iterNo > iterMax)
	{
		std::stringstream ss;
		ss << "MbD: No convergence after " << iterNo << " iterations.";
		auto str = ss.str();
		system->logString(str);
		ss.str("");
		ss << "A force function of joint reactions can cause this problem";
		str = ss.str();
		system->logString(str);
		ss.str("");
		ss << "if the function returns large values.";
		str = ss.str();
		system->logString(str);

		throw SimulationStoppingError("");
	}
}

void AccNewtonRaphson::initializeGlobally()
{
	SystemNewtonRaphson::initializeGlobally();
	system->partsJointsMotionsDo([&](std::shared_ptr<Item> item) { item->fillqsuddotlam(x); });
}

void AccNewtonRaphson::logSingularMatrixMessage()
{
	std::string str = "MbD: Some parts with zero masses or moment of inertias have infinite accelerations.";
	system->logString(str);
	str = "Add masses and inertias to or properly constrain those parts.";
	system->logString(str);
}

void AccNewtonRaphson::passRootToSystem()
{
	system->partsJointsMotionsDo([&](std::shared_ptr<Item> item) { item->setqsuddotlam(x); });
}

void AccNewtonRaphson::postRun()
{
	system->partsJointsMotionsForcesTorquesDo([&](std::shared_ptr<Item> item) { item->postAccIC(); });
}

void AccNewtonRaphson::preRun()
{
	system->partsJointsMotionsForcesTorquesDo([&](std::shared_ptr<Item> item) { item->preAccIC(); });
}

void MbD::AccNewtonRaphson::handleSingularMatrix()
{
	auto& r = *matrixSolver;
	std::string str = typeid(r).name();
	if (str.find("GESpMatParPvMarkoFast") != std::string::npos) {
		matrixSolver = GESpMatParPvPrecise::With();
		solveEquations();
	} else {
		str = typeid(r).name();
		if (str.find("GESpMatParPvPrecise") != std::string::npos) {
			logSingularMatrixMessage();
			matrixSolver->throwSingularMatrixError("AccNewtonRaphson");
		} else {
			assert(false);
		}
	}
}

void MbD::AccNewtonRaphson::run()
{
	assert(false);
}

void MbD::AccNewtonRaphson::iterate()
{
	assert(false);
}
