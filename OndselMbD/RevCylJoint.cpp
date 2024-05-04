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
		auto distxyIJ = DistancexyConstraintIJ::With(efrmI, efrmJ);
		distxyIJ->setConstant(distanceIJ);
		addConstraint(distxyIJ);
		addConstraint(DirectionCosineConstraintIJ::With(efrmI, efrmJ, 2, 0));
		addConstraint(DirectionCosineConstraintIJ::With(efrmI, efrmJ, 2, 1));
		root()->hasChanged = true;
	}
	else {
		CompoundJoint::initializeGlobally();
	}
}
