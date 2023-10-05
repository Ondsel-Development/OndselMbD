/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselMbD.                                       *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include <string>
#include <cassert>

#include "KineIntegrator.h"
#include "SystemSolver.h"
#include "Solver.h"

using namespace MbD;

void KineIntegrator::preRun()
{
	system->Solver::logString("MbD: Starting kinematic analysis.");
	QuasiIntegrator::preRun();
}

void KineIntegrator::runInitialConditionTypeSolution()
{
	system->runPosKine();
	system->runVelKine();
	system->runAccKine();
}

void KineIntegrator::iStep(int i)
{
	assert(false);
}

void KineIntegrator::selectOrder()
{
	assert(false);
}
