/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "RevCylJoint.h"
#include "DistancexyConstraintIJ.h"
#include "System.h"

using namespace MbD;

MbD::RevCylJoint::RevCylJoint(const char* str) : CompoundJoint(str)
{
	assert(false);
}

std::shared_ptr<RevCylJoint> MbD::RevCylJoint::With()
{
	auto inst = std::make_shared<RevCylJoint>();
	inst->initialize();
	return inst;
}

std::shared_ptr<RevCylJoint> MbD::RevCylJoint::With(const char* str)
{
	auto inst = std::make_shared<RevCylJoint>(str);
	inst->initialize();
	return inst;
}

void MbD::RevCylJoint::initializeGlobally()
{
	if (constraints->empty())
	{
		auto distxyIJ = DistancexyConstraintIJ::With(frmI, frmJ);
		distxyIJ->setConstant(distanceIJ);
		addConstraint(distxyIJ);
		addConstraint(DirectionCosineConstraintIJ::With(frmI, frmJ, 2, 0));
		addConstraint(DirectionCosineConstraintIJ::With(frmI, frmJ, 2, 1));
		this->root()->hasChanged = true;
	}
	else {
		CompoundJoint::initializeGlobally();
	}
}
