/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "MatrixGaussElimination.h"

using namespace MbD;

std::shared_ptr<MatrixGaussElimination> MbD::MatrixGaussElimination::With()
{
	auto inst = std::make_shared<MatrixGaussElimination>();
	inst->initialize();
	return inst;
}

void MbD::MatrixGaussElimination::forwardEliminateWithPivot(size_t p)
{
	//Subclasses must implement.
	assert(false);
}
