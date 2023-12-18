/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <memory>

#include "NormalBasicDAEIntegrator.h"
#include "LinearMultiStepMethod.h"
#include "StableBackwardDifference.h"
#include "CREATE.h"
#include "StartingBasicDAEIntegrator.h"

using namespace MbD;

MbD::NormalBasicDAEIntegrator::NormalBasicDAEIntegrator()
{
}

MbD::NormalBasicDAEIntegrator::NormalBasicDAEIntegrator(std::shared_ptr<StartingBasicDAEIntegrator> startingBasicDAEIntegrator)
{
	//system direction 
	//istep iTry maxTry tpast t tnew h hnew order orderNew orderMax opBDF continue 
	//y ydot dy ypast ydotpast aF pFpy pFpydot alp aG extrapolator newtonRaphson corAbsTol corRelTol corOK integAbsTol integRelTol truncError 
	system = startingBasicDAEIntegrator->system;
	direction = startingBasicDAEIntegrator->direction;
	istep = startingBasicDAEIntegrator->istep;
	iTry = startingBasicDAEIntegrator->iTry;
	maxTry = startingBasicDAEIntegrator->maxTry;
	tpast = startingBasicDAEIntegrator->tpast;
	t = startingBasicDAEIntegrator->t;
	tnew = startingBasicDAEIntegrator->tnew;
	h = startingBasicDAEIntegrator->h;
	hnew = startingBasicDAEIntegrator->hnew;
	order = startingBasicDAEIntegrator->order;
	orderNew = startingBasicDAEIntegrator->orderNew;
	orderMax = startingBasicDAEIntegrator->orderMax;
	opBDF = startingBasicDAEIntegrator->opBDF;
	_continue = startingBasicDAEIntegrator->_continue;
	y = startingBasicDAEIntegrator->y;
	ydot = startingBasicDAEIntegrator->ydot;
	dy = startingBasicDAEIntegrator->dy;
	ypast = startingBasicDAEIntegrator->ypast;
	ydotpast = startingBasicDAEIntegrator->ydotpast;
	aF = startingBasicDAEIntegrator->aF;
	pFpy = startingBasicDAEIntegrator->pFpy;
	pFpydot = startingBasicDAEIntegrator->pFpydot;
	alp = startingBasicDAEIntegrator->alp;
	matG = startingBasicDAEIntegrator->matG;
	extrapolator = startingBasicDAEIntegrator->extrapolator;
	newtonRaphson = startingBasicDAEIntegrator->newtonRaphson;
	newtonRaphson->setSystem(this);
	corAbsTol = startingBasicDAEIntegrator->corAbsTol;
	corRelTol = startingBasicDAEIntegrator->corRelTol;
	corOK = startingBasicDAEIntegrator->corOK;
	integAbsTol = startingBasicDAEIntegrator->integAbsTol;
	integRelTol = startingBasicDAEIntegrator->integRelTol;
	truncError = startingBasicDAEIntegrator->truncError;
	opBDFhigher = CREATE<StableBackwardDifference>::With();
	opBDFhigher->timeNodes = tpast;
	opBDFhigher->time = t;
	opBDFhigher->iStep = istep;
	opBDFhigher->order = order + 1;
	//calcOperatorMatrix();
}

void MbD::NormalBasicDAEIntegrator::initialize()
{
	BasicDAEIntegrator::initialize();
	opBDFhigher = CREATE<StableBackwardDifference>::With();
	opBDFhigher->timeNodes = tpast;
}

void MbD::NormalBasicDAEIntegrator::initializeLocally()
{
	//"NormalBasicDAEIntegrator is not used for starting an integration."
	//"Change to StartingBasicDAEIntegrator."
	assert(false);
}

FColDsptr MbD::NormalBasicDAEIntegrator::yDerivat(int n, double time)
{
	return opBDF->derivativeatpresentpast(n, time, y, ypast);
}

std::shared_ptr<LinearMultiStepMethod> MbD::NormalBasicDAEIntegrator::correctorBDF()
{
	return opBDF;
}

void MbD::NormalBasicDAEIntegrator::calcOperatorMatrix()
{
	BasicDAEIntegrator::calcOperatorMatrix();
	opBDFhigher->calcOperatorMatrix();
}

void MbD::NormalBasicDAEIntegrator::settime(double t)
{
	BasicDAEIntegrator::settime(t);
	opBDFhigher->settime(t);
}

void MbD::NormalBasicDAEIntegrator::iStep(int i)
{
	BasicDAEIntegrator::iStep(i);
	opBDFhigher->setiStep(i);
}

void MbD::NormalBasicDAEIntegrator::setorder(int o)
{
	BasicDAEIntegrator::setorder(o);
	opBDFhigher->setorder(o + 1);
}

FColDsptr MbD::NormalBasicDAEIntegrator::yDeriv(int deriv)
{
	return opBDF->derivativepresentpast(deriv, y, ypast);
}

FColDsptr MbD::NormalBasicDAEIntegrator::dyOrderPlusOnedt()
{
	return opBDFhigher->derivativepresentpast(order + 1, y, ypast);
}

void MbD::NormalBasicDAEIntegrator::run()
{
	subsequentSteps();
	finalize();
	reportStats();
	postRun();
}

void MbD::NormalBasicDAEIntegrator::selectOrder()
{
	if (tpast->size() < order + 1) return;	//Needed to transition from Starting to Normal
	selectOrderNormal();
}

void MbD::NormalBasicDAEIntegrator::selectStepSize()
{
	if (tpast->size() < order + 1) return;	//Needed to transition from Starting to Normal
	BasicDAEIntegrator::selectStepSize();
}

void MbD::NormalBasicDAEIntegrator::selectOrderNormal()
{
	//"Brenan's book pp. 126-7"
	//"Check last nterm of Taylor series plus first term of remainder."

	auto errorTrunc = std::make_shared<FullVector<double>>();
	auto nterm = 3;
	int istart;
	FColDsptr yndot;
	double yndotNorm, hpower;
	if (order > nterm) {
		istart = order - nterm + 1;
	}
	else {
		istart = 1;
	}
	for (int i = istart; i < order; i++)
	{
		yndot = yDeriv(i);
		yndotNorm = integErrorNormFromwrt(yndot, y);
		hpower = std::pow(h, i);
		errorTrunc->push_back(yndotNorm * hpower);
	}


	yndot = dyOrderPlusOnedt();
	yndotNorm = integErrorNormFromwrt(yndot, y);
	hpower = std::pow(h, order + 1);
	errorTrunc->push_back(yndotNorm * hpower);
	orderNew = order;
	if (errorTrunc->isIncreasing()) {
		if (order > 1) orderNew = order - 1;
	}
	if (errorTrunc->isDecreasingIfExceptionsAreLessThan(0.01)) {
		if (order < orderMax) orderNew = order + 1;
	}
}
