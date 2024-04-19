/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "InLineJoint.h"

using namespace MbD;

MbD::InLineJoint::InLineJoint(const char*)
{
	assert(false);
}

void MbD::InLineJoint::initializeGlobally()
{
	//Subclasses must implement.
	assert(false);
}

void MbD::InLineJoint::createInLineConstraints()
{
	addConstraint(TranslationConstraintIJ::With(frmI, frmJ, 0));
	addConstraint(TranslationConstraintIJ::With(frmI, frmJ, 1));
}
