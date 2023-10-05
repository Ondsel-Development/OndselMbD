/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselMbD.                                       *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "ConstraintIJ.h"
#include "EndFramec.h"

using namespace MbD;

ConstraintIJ::ConstraintIJ(EndFrmsptr frmi, EndFrmsptr frmj) : frmI(frmi), frmJ(frmj)
{
}

void ConstraintIJ::initialize()
{
	Constraint::initialize();
	aConstant = 0.0;
}

void MbD::ConstraintIJ::setConstant(double value)
{
	aConstant = value;
}
