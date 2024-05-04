/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "NoRotationJoint.h"
#include "System.h"
#include "DirectionCosineConstraintIJ.h"

using namespace MbD;

std::shared_ptr<NoRotationJoint> MbD::NoRotationJoint::With()
{
	auto inst = std::make_shared<NoRotationJoint>();
	inst->initialize();
	return inst;
}

std::shared_ptr<NoRotationJoint> MbD::NoRotationJoint::With(const char* str)
{
	auto inst = std::make_shared<NoRotationJoint>(str);
	inst->initialize();
	return inst;
}

void MbD::NoRotationJoint::initializeGlobally()
{
	if (constraints->empty())
	{
		addConstraint(DirectionCosineConstraintIJ::With(efrmI, efrmJ, 1, 0));
		addConstraint(DirectionCosineConstraintIJ::With(efrmI, efrmJ, 2, 0));
		addConstraint(DirectionCosineConstraintIJ::With(efrmI, efrmJ, 2, 1));
		root()->hasChanged = true;
	}
	else {
		JointIJ::initializeGlobally();
	}
}
