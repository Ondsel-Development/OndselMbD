/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <memory>

#include "StartingBasicDAEIntegrator.h"
#include "CREATE.h"

using namespace MbD;


void MbD::StartingBasicDAEIntegrator::initialize()
{
	BasicDAEIntegrator::initialize();
	startingBDF = CREATE<StableStartingBDF>::With();
	startingBDF->timeNodes = tpast;
}

void MbD::StartingBasicDAEIntegrator::initializeLocally()
{
	BasicDAEIntegrator::initializeLocally();
	startingBDF->initializeLocally();
}

FColDsptr MbD::StartingBasicDAEIntegrator::yDerivat(int n, double time)
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

void MbD::StartingBasicDAEIntegrator::setorder(int o)
{
	BasicDAEIntegrator::setorder(o);
	startingBDF->setorder(o + 1);
}

void MbD::StartingBasicDAEIntegrator::settime(double t)
{
	BasicDAEIntegrator::settime(t);
	startingBDF->settime(t);
}

void MbD::StartingBasicDAEIntegrator::iStep(int i)
{
	BasicDAEIntegrator::iStep(i);
	startingBDF->setiStep(i);
}

FColDsptr MbD::StartingBasicDAEIntegrator::yDeriv(int order)
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
			this->nextStep();
		}
		else {
			break;
		}
	}
}
