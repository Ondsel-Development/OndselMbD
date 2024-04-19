/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <cassert>

#include "DifferentialAlgebraicEquationSolver.h"

using namespace MbD;

std::shared_ptr<DifferentialAlgebraicEquationSolver> MbD::DifferentialAlgebraicEquationSolver::With()
{
	auto inst = std::make_shared<DifferentialAlgebraicEquationSolver>();
	inst->initialize();
	return inst;
}

void MbD::DifferentialAlgebraicEquationSolver::setSystem(Solver* sys)
{
	assert(false);
}

void MbD::DifferentialAlgebraicEquationSolver::useDAETrialStepStats(std::shared_ptr<SolverStatistics> stats)
{
	assert(false);
}
