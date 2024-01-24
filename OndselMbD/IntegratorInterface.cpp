/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
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

void MbD::IntegratorInterface::preRun()
{
	assert(false);
}

void MbD::IntegratorInterface::checkForDiscontinuity()
{
	assert(false);
}

void IntegratorInterface::setSystem(Solver* sys)
{
	system = static_cast<SystemSolver*>(sys);
}

void IntegratorInterface::logString(std::string& str)
{
	system->logString(str);
}

size_t IntegratorInterface::orderMax() const
{
	return system->orderMax;
}

void IntegratorInterface::incrementTime(double tnew)
{
	system->settime(tnew);
}

void MbD::IntegratorInterface::postFirstStep()
{
	assert(false);
}

double MbD::IntegratorInterface::suggestSmallerOrAcceptFirstStepSize(double hnew)
{
	assert(false);
	return 0.0;
}

double MbD::IntegratorInterface::suggestSmallerOrAcceptStepSize(double hnew)
{
	assert(false);
	return 0.0;
}

void MbD::IntegratorInterface::checkForOutputThrough(double t)
{
	assert(false);
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

void MbD::IntegratorInterface::useTrialStepStats(std::shared_ptr<SolverStatistics> stats)
{
	assert(false);
}

void MbD::IntegratorInterface::useDAEStepStats(std::shared_ptr<SolverStatistics> stats)
{
	assert(false);
}

void MbD::IntegratorInterface::useQuasiStepStats(std::shared_ptr<SolverStatistics> stats)
{
	assert(false);
}
