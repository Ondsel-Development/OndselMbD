/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <memory>

#include "StartingBasicDAEIntegrator.h"

using namespace MbD;


std::shared_ptr<StartingBasicDAEIntegrator> MbD::StartingBasicDAEIntegrator::With()
{
	auto inst = std::make_shared<StartingBasicDAEIntegrator>();
	inst->initialize();
	return inst;
}

void MbD::StartingBasicDAEIntegrator::initialize()
{
	BasicDAEIntegrator::initialize();
	startingBDF = StableStartingBDF::With();
	startingBDF->timeNodes = tpast;
}

void MbD::StartingBasicDAEIntegrator::initializeLocally()
{
	BasicDAEIntegrator::initializeLocally();
	startingBDF->initializeLocally();
}

FColDsptr MbD::StartingBasicDAEIntegrator::yDerivat(size_t n, double time)
{
	return startingBDF->derivativeatpresentpastpresentDerivativepastDerivative(n, time, y, ypast, ydot, ydotpast);
}

std::shared_ptr<LinearMultiStepMethod> MbD::StartingBasicDAEIntegrator::correctorBDF()
{
	return startingBDF;
}

void MbD::StartingBasicDAEIntegrator::calcOperatorMatrix()
{
	BasicDAEIntegrator::calcOperatorMatrix();
	startingBDF->calcOperatorMatrix();
}

void MbD::StartingBasicDAEIntegrator::setorder(size_t o)
{
	BasicDAEIntegrator::setorder(o);
	startingBDF->setorder(o + 1);
}

void MbD::StartingBasicDAEIntegrator::settime(double t)
{
	BasicDAEIntegrator::settime(t);
	startingBDF->settime(t);
}

void MbD::StartingBasicDAEIntegrator::iStep(size_t i)
{
	BasicDAEIntegrator::iStep(i);
	startingBDF->setiStep(i);
}

FColDsptr MbD::StartingBasicDAEIntegrator::yDeriv(size_t order)
{
	return startingBDF->derivativepresentpastpresentDerivativepastDerivative(order, y, ypast, ydot, ydotpast);
}

FColDsptr MbD::StartingBasicDAEIntegrator::dyOrderPlusOnedt()
{
	return startingBDF->derivativepresentpastpresentDerivativepastDerivative(order + 1, y, ypast, ydot, ydotpast);
}

void MbD::StartingBasicDAEIntegrator::run()
{
	preRun();
	initializeLocally();
	initializeGlobally();
	firstSteps();
}

void MbD::StartingBasicDAEIntegrator::firstSteps()
{
	firstStep();
	earlySteps();
}

void MbD::StartingBasicDAEIntegrator::earlySteps()
{
	while (_continue) {
		if (istep < orderMax) {
			nextStep();
		}
		else {
			break;
		}
	}
}
