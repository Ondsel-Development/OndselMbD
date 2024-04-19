/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "FixedJoint.h"
#include "System.h"
#include "DirectionCosineConstraintIJ.h"

using namespace MbD;

MbD::FixedJoint::FixedJoint(const char* str) : AtPointJoint(str)
{
	assert(false);
}

std::shared_ptr<FixedJoint> MbD::FixedJoint::With()
{
	auto inst = std::make_shared<FixedJoint>();
	inst->initialize();
	return inst;
}

std::shared_ptr<FixedJoint> MbD::FixedJoint::With(const char* str)
{
	auto inst = std::make_shared<FixedJoint>(str);
	inst->initialize();
	return inst;
}

void MbD::FixedJoint::initializeGlobally()
{
	if (constraints->empty())
	{
		createAtPointConstraints();
		//addConstraint(DirectionCosineConstraintIJ::With(frmI, frmJ, 0, 1));
		//addConstraint(DirectionCosineConstraintIJ::With(frmI, frmJ, 1, 2));
		//addConstraint(DirectionCosineConstraintIJ::With(frmI, frmJ, 2, 0));
		addConstraint(DirectionCosineConstraintIJ::With(frmI, frmJ, 1, 0));
		addConstraint(DirectionCosineConstraintIJ::With(frmI, frmJ, 2, 0));
		addConstraint(DirectionCosineConstraintIJ::With(frmI, frmJ, 2, 1));
		this->root()->hasChanged = true;
	}
	else {
		Joint::initializeGlobally();
	}
}
