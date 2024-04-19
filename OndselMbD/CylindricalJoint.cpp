/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "CylindricalJoint.h"
#include "System.h"
#include "DirectionCosineConstraintIJ.h"
#include "TranslationConstraintIJ.h"

using namespace MbD;

CylindricalJoint::CylindricalJoint(const char* str) : InLineJoint(str) 
{
	assert(false);
}

std::shared_ptr<CylindricalJoint> MbD::CylindricalJoint::With()
{
	auto inst = std::make_shared<CylindricalJoint>();
	inst->initialize();
	return inst;
}

std::shared_ptr<CylindricalJoint> MbD::CylindricalJoint::With(const char* str)
{
	auto inst = std::make_shared<CylindricalJoint>(str);
	inst->initialize();
	return inst;
}

void CylindricalJoint::initializeGlobally()
{
	if (constraints->empty())
	{
		createInLineConstraints();
		addConstraint(DirectionCosineConstraintIJ::With(frmI, frmJ, 2, 0));
		addConstraint(DirectionCosineConstraintIJ::With(frmI, frmJ, 2, 1));
		this->root()->hasChanged = true;
	}
	else {
		Joint::initializeGlobally();
	}
}
