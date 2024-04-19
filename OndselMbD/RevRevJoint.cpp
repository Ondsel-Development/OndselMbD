/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "RevRevJoint.h"
#include "DistancexyConstraintIJ.h"
#include "System.h"

using namespace MbD;

MbD::RevRevJoint::RevRevJoint(const char* str) : CompoundJoint(str)
{
	assert(false);
}

std::shared_ptr<RevRevJoint> MbD::RevRevJoint::With()
{
	auto inst = std::make_shared<RevRevJoint>();
	inst->initialize();
	return inst;
}

std::shared_ptr<RevRevJoint> MbD::RevRevJoint::With(const char* str)
{
	auto inst = std::make_shared<RevRevJoint>(str);
	inst->initialize();
	return inst;
}

void MbD::RevRevJoint::initializeGlobally()
{
	if (constraints->empty())
	{
		auto distxyIJ = DistancexyConstraintIJ::With(frmI, frmJ);
		distxyIJ->setConstant(distanceIJ);
		addConstraint(distxyIJ);
		addConstraint(TranslationConstraintIJ::With(frmI, frmJ, 2));
		addConstraint(DirectionCosineConstraintIJ::With(frmI, frmJ, 2, 0));
		addConstraint(DirectionCosineConstraintIJ::With(frmI, frmJ, 2, 1));
		this->root()->hasChanged = true;
	}
	else {
		CompoundJoint::initializeGlobally();
	}
}
