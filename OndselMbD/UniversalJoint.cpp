/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "UniversalJoint.h"
#include "System.h"

using namespace MbD;

MbD::UniversalJoint::UniversalJoint(const char* str) : AtPointJoint(str)
{
	assert(false);
}

std::shared_ptr<UniversalJoint> MbD::UniversalJoint::With()
{
	auto inst = std::make_shared<UniversalJoint>();
	inst->initialize();
	return inst;
}

std::shared_ptr<UniversalJoint> MbD::UniversalJoint::With(const char* str)
{
	auto inst = std::make_shared<UniversalJoint>(str);
	inst->initialize();
	return inst;
}

void MbD::UniversalJoint::initializeGlobally()
{
	if (constraints->empty())
	{
		createAtPointConstraints();
		addConstraint(DirectionCosineConstraintIJ::With(frmI, frmJ, 2, 2));
		this->root()->hasChanged = true;
	}
	else {
		Joint::initializeGlobally();
	}
}
