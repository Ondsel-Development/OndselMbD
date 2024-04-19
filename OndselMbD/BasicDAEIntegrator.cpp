/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <cassert>
#include <memory>

#include "BasicDAEIntegrator.h"
#include "IntegratorInterface.h"
#include "DynIntegrator.h"
#include "DAECorrector.h"
#include "MaximumIterationError.h"
#include "SingularMatrixError.h"
#include "TooManyTriesError.h"

using namespace MbD;

std::shared_ptr<BasicDAEIntegrator> MbD::BasicDAEIntegrator::With()
{
	auto inst = std::make_shared<BasicDAEIntegrator>();
	inst->initialize();
	return inst;
}

void MbD::BasicDAEIntegrator::initialize()
{
	BasicIntegrator::initialize();
	extrapolator = Extrapolator::With();
	extrapolator->timeNodes = tpast;
	newtonRaphson = DAECorrector::With();
	newtonRaphson->setSystem(this);
	ypast = std::make_shared<std::vector<FColDsptr>>();
	ydotpast = std::make_shared<std::vector<FColDsptr>>();
}

void MbD::BasicDAEIntegrator::initializeGlobally()
{
	//"Get info from system and prepare for start of simulation."
	//"Integrator asks system for info. Not system setting integrator."

	BasicIntegrator::initializeGlobally();
	auto daeSystem = static_cast<DynIntegrator*>(system);
	integRelTol = daeSystem->integrationRelativeTolerance();
	integAbsTol = daeSystem->integrationAbsoluteTolerance();
	corRelTol = daeSystem->correctorRelativeTolerance();
	corAbsTol = daeSystem->correctorAbsoluteTolerance();
	auto size = daeSystem->neqn;
	y = std::make_shared<FullColumn<double>>(size);
	daeSystem->fillY(y);
	ydot = std::make_shared<FullColumn<double>>(size);
	daeSystem->fillYdot(ydot);
	aF = std::make_shared<FullColumn<double>>(size);
	pFpy = std::make_shared<SparseMatrix<double>>(size, size);
	pFpydot = std::make_shared<SparseMatrix<double>>(size, size);
}

void MbD::BasicDAEIntegrator::firstStep()
{
	istep = 0;
	preFirstStep();
	iTry = 1;
	orderNew = 1;
	selectFirstStepSize();
	incrementTime();
	predictFirstStep();
	correctFirstStep();
	reportTrialStepStats();
	while (isRedoingFirstStep()) {
		incrementTry();
		orderNew = 1;
		selectFirstStepSize();
		changeTime();
		predictFirstStep();
		correctFirstStep();
		reportTrialStepStats();
	}
	postFirstStep();
	reportStepStats();
}

bool MbD::BasicDAEIntegrator::isRedoingFirstStep()
{
	if (iTry > 100) throw TooManyTriesError("");
	if (!corOK) return true;
	if (truncError > 1.0) return true;
	//"Look at the next step size."
	//"Aim for first step size and second step size to be similar in size."
	//"Huge disparity causes poor accuracy for subsequent steps."
	hnew = selectBasicStepSize();
	hnew = system->suggestSmallerOrAcceptFirstStepSize(hnew);
	if ((hnew > (4.0 * h)) && (hnew < system->hmax)) return true;
	return false;
}

void MbD::BasicDAEIntegrator::nextStep()
{
	preStep();
	iTry = 1;
	selectOrder();
	selectStepSize();
	incrementTime();
	predict();
	correct();
	reportTrialStepStats();
	while (isRedoingStep()) {
		incrementTry();
		selectOrder();
		selectStepSize();
		changeTime();
		predict();
		correct();
		reportTrialStepStats();
	}
	postStep();
	reportStepStats();
}

void MbD::BasicDAEIntegrator::reportStepStats()
{
	system->useDAEStepStats(statistics);
}

void MbD::BasicDAEIntegrator::reportTrialStepStats()
{
	statistics->istep = istep;
	statistics->t = t;
	statistics->h = direction * h;
	statistics->order = order;
	statistics->truncError = truncError;
	system->useTrialStepStats(statistics);
}

void MbD::BasicDAEIntegrator::runInitialConditionTypeSolution()
{
	assert(false);
}

void MbD::BasicDAEIntegrator::selectFirstStepSize()
{
	if (iTry == 1) {
		auto hout1000 = system->hout / 1000.0;
		auto ydotNorm = std::max(integErrorNormFromwrt(ydot, y), 1.0e-15);
		auto hydot = 0.5 / ydotNorm;
		hnew = std::min(hout1000, hydot);
		hnew = std::max(hnew, 1.0e-6);
	}
	else {
		if (corOK) {
			hnew = selectBasicStepSize();
		}
		else {
			hnew = 0.25 * h;
		}
	}
	hnew = system->suggestSmallerOrAcceptFirstStepSize(hnew);
}

void MbD::BasicDAEIntegrator::selectStepSize()
{
	if (corOK) {
		selectStepSizeNormal();
	}
	else {
		hnew = 0.25 * h;
	}
	hnew = system->suggestSmallerOrAcceptStepSize(hnew);
}

void MbD::BasicDAEIntegrator::predictFirstStep()
{
	auto dynInt = static_cast<DynIntegrator*>(system);
	dynInt->preDAEPredictor();
	predictValuesAtFirstStep();
	dynInt->y(y);
	dynInt->ydot(ydot);
	dynInt->postDAEPredictor();
}

void MbD::BasicDAEIntegrator::correctFirstStep()
{
	auto dynInt = static_cast<DynIntegrator*>(system);
	try {
		try {
			dynInt->preDAECorrector();
			correctValuesAtFirstStep();
			dynInt->postDAECorrector();
		}
		catch (SingularMatrixError ex) {
			//"Step size is probably too small, causing an ill conditioned matrix."
			//"Increase step size. Multiply by 4.0d to offset reduction in selectFirstStepSize."
			corOK = false;
			truncError = 999999.0;
			auto hout1000 = dynInt->hout / 1000.0;
			auto ydotNorm = std::max(integErrorNormFromwrt(ydot, y), 1.0e-15);
			auto hydot = 0.5 / ydotNorm;
			h = 4.0 * std::max(hout1000, hydot);
			return;
		}
	}
	catch (MaximumIterationError ex) {
		corOK = false;
		truncError = 888888.0;
		return;
	}
}

void MbD::BasicDAEIntegrator::changeTime()
{
	setorder(orderNew);
	h = hnew;
	settnew(tpast->at(0) + (direction * h));
	system->changeTime(tnew);
	calcOperatorMatrix();
}

double MbD::BasicDAEIntegrator::selectBasicStepSize()
{
	//"Shampine's book pp 337-8."
	//"Brenan's book pp 128."
	//"Using first term of Taylor series remainder."

	double conservativeFactor, coeff, yndotNorm, dum, hdum;
	FColDsptr yndot;
	conservativeFactor = 0.5;
	if (orderNew < order) {
		coeff = DifferenceOperator::OneOverFactorials->at(order);
		yndot = yDeriv(order);
		yndotNorm = std::max(integErrorNormFromwrt(yndot, y), 1.0e-15);
		dum = conservativeFactor / (coeff * yndotNorm);
		hdum = std::pow(dum, 1.0 / order);
	}
	else {
		coeff = DifferenceOperator::OneOverFactorials->at(order + 1);
		yndot = dyOrderPlusOnedt();
		yndotNorm = std::max(integErrorNormFromwrt(yndot, y), 1.0e-15);
		dum = conservativeFactor / (coeff * yndotNorm);
		hdum = std::pow(dum, 1.0 / (order + 1));
	}
	return hdum;
}

double MbD::BasicDAEIntegrator::integErrorNormFromwrt(FColDsptr err, FColDsptr ref)
{
	return rmswrtrelativeTolabsoluteTol(err, ref, integRelTol, integAbsTol);
}

double MbD::BasicDAEIntegrator::rmswrtrelativeTolabsoluteTol(FColDsptr vector, FColDsptr baseVector, FColDsptr relativeTol, FColDsptr absoluteTol)
{
	//"Answer a weighted rms norm."
	//"Elements with relativeTol == nil are not included in norm."
	//"For m significant digits set relToli = 1.0e-m."
	//"Set absToli to value where vectori abs is insignificant."

	auto n = baseVector->size();
	auto count = 0;
	auto sumOfSquares = 0.0;
	for (size_t i = 0; i < n; i++)
	{
		auto relToli = relativeTol->at(i);
		if (relToli != std::numeric_limits<double>::min()) {
			count++;
			auto weighti = relToli * std::abs(baseVector->at(i)) + absoluteTol->at(i);
			auto vectori = vector->at(i);
			auto vectoriOverWeighti = vectori / weighti;
			sumOfSquares += (vectoriOverWeighti * vectoriOverWeighti);
		}

	}
	return std::sqrt(sumOfSquares / count);
}

void MbD::BasicDAEIntegrator::predictValuesAtFirstStep()
{
	y = ypast->at(0)->plusFullColumntimes(ydotpast->at(0), direction * h);
	ydot = ydotpast->at(0)->copy();
}

void MbD::BasicDAEIntegrator::predictValuesAtNextStep()
{
	//"ydot := extrapolator valueWith: ydotpast."
	//"Poor prediction. Extra iteration of the corrector is needed."

	y = extrapolator->valueWith(ypast);
	ydot = yDeriv(1);
}

void MbD::BasicDAEIntegrator::incrementTime()
{
	BasicIntegrator::incrementTime();
	ypast->insert(ypast->begin(), y);
	ydotpast->insert(ydotpast->begin(), ydot);
	if (ypast->size() > (orderMax + 1)) {
		ypast->pop_back();
		ydotpast->pop_back();
	}
}

void MbD::BasicDAEIntegrator::correctValuesAtFirstStep() const
{
	newtonRaphson->run();
}

void MbD::BasicDAEIntegrator::correctValuesAtNextStep() const
{
	newtonRaphson->run();
}

void MbD::BasicDAEIntegrator::preDAECorrector()
{
	corOK = false;
	truncError = -1.0;
}

void MbD::BasicDAEIntegrator::postDAECorrector()
{
	corOK = true;
	calcTruncError();
}

FColDsptr MbD::BasicDAEIntegrator::fillF()
{
	aF->zeroSelf();
	system->fillF(aF);
	return aF;
}

size_t MbD::BasicDAEIntegrator::iterMax()
{
	return system->iterMax();
}

SpMatDsptr MbD::BasicDAEIntegrator::calcG()
{
	//"It is ok to modify pFpydot since its values are not reused."
	pFpy->zeroSelf();
	system->fillpFpy(pFpy);
	pFpydot->zeroSelf();
	system->fillpFpydot(pFpydot);
	alp = correctorBDF()->pvdotpv();
	pFpydot->magnifySelf(alp);
	matG = pFpy->plusSparseMatrix(pFpydot);
	return matG;
}

std::shared_ptr<LinearMultiStepMethod> MbD::BasicDAEIntegrator::correctorBDF()
{
	assert(false);
	return std::shared_ptr<LinearMultiStepMethod>();
}

void MbD::BasicDAEIntegrator::calcOperatorMatrix()
{
	BasicIntegrator::calcOperatorMatrix();
	extrapolator->calcOperatorMatrix();
}

void MbD::BasicDAEIntegrator::setorder(size_t o)
{
	BasicIntegrator::setorder(o);
	extrapolator->setorder(o - 1);
}

void MbD::BasicDAEIntegrator::settime(double t)
{
	BasicIntegrator::settime(t);
	extrapolator->settime(t);
}

void MbD::BasicDAEIntegrator::iStep(size_t i)
{
	BasicIntegrator::iStep(i);
	extrapolator->setiStep(i);
}

double MbD::BasicDAEIntegrator::corErrorNormFromwrt(FColDsptr error, FColDsptr ref)
{
	return rmswrtrelativeTolabsoluteTol(error, ref, corRelTol, corAbsTol);
}

void MbD::BasicDAEIntegrator::updateForDAECorrector()
{
	ydot = yDeriv(1);
	system->y(y);
	system->ydot(ydot);
	system->updateForDAECorrector();
}

FColDsptr MbD::BasicDAEIntegrator::yDeriv(size_t order)
{
	assert(false);
	return FColDsptr();
}

void MbD::BasicDAEIntegrator::calcTruncError()
{
	//"Calculate the leading term of truncation error in Taylor series."

	auto factor = DifferenceOperator::OneOverFactorials->at(order + 1);
	auto yndot = dyOrderPlusOnedt();
	auto yndotNorm = integErrorNormFromwrt(yndot, y);
	auto hpower = std::pow(h, order + 1);
	truncError = factor * yndotNorm * hpower;
}

FColDsptr MbD::BasicDAEIntegrator::dyOrderPlusOnedt()
{
	assert(false);
	return FColDsptr();
}

bool MbD::BasicDAEIntegrator::isConvergedForand(size_t iterNo, std::shared_ptr<std::vector<double>> dyNorms) const
{
	auto dyNormIterNo = dyNorms->at(iterNo);
	auto smallEnoughTol = 4 * std::numeric_limits<double>::epsilon() / corAbsTol->at(0);
	auto smallEnough = dyNormIterNo < smallEnoughTol;
	if (iterNo == 0) return smallEnough;
	auto rho = dyNormIterNo / dyNorms->at(iterNo - 1);
	return smallEnough || (rho < 1.0 && (rho * dyNormIterNo / (1.0 - rho) < 0.33));
}

void MbD::BasicDAEIntegrator::postFirstStep()
{
	t = tnew;
	static_cast<DynIntegrator*>(system)->postDAEFirstStep();
}

void MbD::BasicDAEIntegrator::postStep()
{
	t = tnew;
	auto daeSystem = static_cast<DynIntegrator*>(system);
	daeSystem->postDAEStep();
}

void MbD::BasicDAEIntegrator::predict()
{
	auto daeSystem = static_cast<DynIntegrator*>(system);
	daeSystem->preDAEPredictor();
	predictValuesAtNextStep();
	daeSystem->y(y);
	daeSystem->ydot(ydot);
	daeSystem->postDAEPredictor();
}

void MbD::BasicDAEIntegrator::correct()
{
	auto dynInt = static_cast<DynIntegrator*>(system);
	try {
		try {
			dynInt->preDAECorrector();
			correctValuesAtNextStep();
			dynInt->postDAECorrector();
		}
		catch (SingularMatrixError ex) {
			newtonRaphson->matrixSolver->throwSingularMatrixError("");
		}
	}
	catch (MaximumIterationError ex) {
		corOK = false;
		truncError = 888888.0;
		return;
	}
}

bool MbD::BasicDAEIntegrator::isRedoingStep() const
{
	if (iTry > 100) {
		throw TooManyTriesError("");
	}
	return !corOK || (truncError > 1.0);
}

void MbD::BasicDAEIntegrator::selectStepSizeNormal()
{
	//"Shampine's book pp 337-8."
	//"Brenan's book pp 128."
	//"Using first term of Taylor series remainder."

	double hdum, twoH, pt9H, pt5H, pt25H;
	hdum = selectBasicStepSize();
	if (iTry == 1) {
		if (hdum >= h) {
			twoH = 2.0 * h;
			if (hdum > twoH) {
				hnew = twoH;
			}
			else {
				hnew = h;
			}
		}
		else {
			pt9H = 0.9 * h;
			if (hdum > pt9H) {
				hnew = pt9H;
			}
			else {
				pt5H = 0.5 * h;
				if (hdum < pt5H) {
					hnew = pt5H;
				}
				else {
					hnew = hdum;
				}
			}
		}
	}
	else {
		if (iTry == 2) {
			pt9H = 0.9 * h;
			hdum = 0.9 * hdum;
			if (hdum > pt9H) {
				hnew = pt9H;
			}
			else {
				pt25H = 0.25 * h;
				if (hdum < pt25H) {
					hnew = pt25H;
				}
				else {
					hnew = hdum;
				}
			}
		}
		else {
			hnew = 0.25 * h;
		}
	}
}

void MbD::BasicDAEIntegrator::useDAECorrectorStats(std::shared_ptr<SolverStatistics> stats) const
{
	statistics->corIterNo = stats->iterNo;
}
