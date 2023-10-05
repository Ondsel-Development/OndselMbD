/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselMbD.                                       *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <cassert>
 
#include "ICKineIntegrator.h"
#include "SystemSolver.h"

using namespace MbD;

void ICKineIntegrator::runInitialConditionTypeSolution()
{
	system->runPosICKine();
	system->runVelICKine();
	system->runAccICKine();
}

void ICKineIntegrator::iStep(int i)
{
	assert(false);
}

void ICKineIntegrator::selectOrder()
{
	assert(false);
}

void ICKineIntegrator::preRun()
{
	system->Solver::logString("MbD: Starting quasi kinematic analysis.");
	QuasiIntegrator::preRun();
}
