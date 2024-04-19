/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "PerpendicularJoint.h"
#include "System.h"

using namespace MbD;

MbD::PerpendicularJoint::PerpendicularJoint(const char*)
{
	assert(false);
}

std::shared_ptr<PerpendicularJoint> MbD::PerpendicularJoint::With()
{
	auto inst = std::make_shared<PerpendicularJoint>();
	inst->initialize();
	return inst;
}

std::shared_ptr<PerpendicularJoint> MbD::PerpendicularJoint::With(const char* str)
{
	auto inst = std::make_shared<PerpendicularJoint>(str);
	inst->initialize();
	return inst;
}

void MbD::PerpendicularJoint::initializeGlobally()
{
	if (constraints->empty())
	{
		addConstraint(DirectionCosineConstraintIJ::With(frmI, frmJ, 2, 2));
		this->root()->hasChanged = true;
	}
	else {
		Joint::initializeGlobally();
	}
}
