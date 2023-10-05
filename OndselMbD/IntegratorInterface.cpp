/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselMbD.                                       *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include <string>
#include <cassert>

#include "IntegratorInterface.h"
#include "SystemSolver.h"
#include "BasicQuasiIntegrator.h"
#include "CREATE.h"
#include "NormalBasicDAEIntegrator.h"
#include "StartingBasicDAEIntegrator.h"

using namespace MbD;

void IntegratorInterface::initializeGlobally()
{
	tstart = system->startTime();
	hout = system->outputStepSize();
	hmax = system->maxStepSize();
	hmin = system->minStepSize();
	tout = system->firstOutputTime();
	tend = system->endTime();
	direction = (tstart < tend) ? 1.0 : -1.0;
}

void IntegratorInterface::setSystem(Solver* sys)
{
	system = static_cast<SystemSolver*>(sys);
}

void IntegratorInterface::logString(std::string& str)
{
	system->logString(str);
}

void IntegratorInterface::run()
{
	this->preRun();
	this->initializeLocally();
	this->initializeGlobally();
	if (hout > (4 * std::numeric_limits<double>::epsilon()) && (direction * tout < (direction * (tend + (0.1 * direction * hout))))) {
		integrator->run();
		auto startingintegrator = std::dynamic_pointer_cast<StartingBasicDAEIntegrator>(integrator);
		auto normalIntegrator = std::make_shared<NormalBasicDAEIntegrator>(startingintegrator);
		integrator = normalIntegrator;
		integrator->run();
	}
	this->finalize();
	this->reportStats();
	this->postRun();
}

int IntegratorInterface::orderMax()
{
	return system->orderMax;
}

void IntegratorInterface::incrementTime(double tnew)
{
	system->settime(tnew);
}

void IntegratorInterface::interpolateAt(double tArg)
{
	//"Interpolate for system state at tArg and leave system in that state."
	assert(false);
	//auto yout = integrator->yDerivat(0, tArg);
	//auto ydotout = integrator->yDerivat(1, tArg);
	//auto yddotout = integrator->yDerivat(2, tArg);
	//system->time(tArg);
	//system->y(yout);
	//system->ydot(ydotout);
	//system->yddot(yddotout);
	//system->simUpdateAll();
}

void MbD::IntegratorInterface::fillF(FColDsptr vecF)
{
	assert(false);
}

void MbD::IntegratorInterface::fillpFpy(SpMatDsptr mat)
{
	assert(false);
}

void MbD::IntegratorInterface::fillpFpydot(SpMatDsptr mat)
{
	assert(false);
}

void MbD::IntegratorInterface::changeTime(double t)
{
	system->settime(t);
}

void MbD::IntegratorInterface::y(FColDsptr col)
{
	assert(false);
}

void MbD::IntegratorInterface::ydot(FColDsptr col)
{
	assert(false);
}

void MbD::IntegratorInterface::updateForDAECorrector()
{
	assert(false);
}
