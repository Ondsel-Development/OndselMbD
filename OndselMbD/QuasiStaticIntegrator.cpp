/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <cassert>
#include <memory>

#include "QuasiStaticIntegrator.h"
#include "SystemSolver.h"

using namespace MbD;

void MbD::QuasiStaticIntegrator::useTrialStepStats(std::shared_ptr<SolverStatistics> stats)
{
	system->useDynTrialStepStats(stats);
}
