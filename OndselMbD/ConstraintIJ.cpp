/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "ConstraintIJ.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<ConstraintIJ> MbD::ConstraintIJ::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
	//Should not create abstract class.
	assert(false);
	return std::shared_ptr<ConstraintIJ>();
}

void ConstraintIJ::initialize()
{
	Constraint::initialize();
	aConstant = 0.0;
}
