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

void MbD::InPlaneJoint::initializeGlobally()
{
	//Subclasses must implement.
	assert(false);
}

void MbD::InPlaneJoint::createInPlaneConstraint()
{
	auto tranCon = TranslationConstraintIJ::With(efrmI, efrmJ, 2);
	tranCon->setConstant(offset);
	addConstraint(tranCon);
}
