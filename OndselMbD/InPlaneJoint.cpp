/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "InPlaneJoint.h"
#include "TranslationConstraintIJ.h"

using namespace MbD;

MbD::InPlaneJoint::InPlaneJoint(const char*)
{
	assert(false);
}

void MbD::InPlaneJoint::initializeGlobally()
{
	//Subclasses must implement.
	assert(false);
}

void MbD::InPlaneJoint::createInPlaneConstraint()
{
	auto tranCon = TranslationConstraintIJ::With(frmI, frmJ, 2);
	tranCon->setConstant(offset);
	addConstraint(tranCon);
}
