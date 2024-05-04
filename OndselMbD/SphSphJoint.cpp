/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "SphSphJoint.h"
#include "DistanceConstraintIJ.h"
#include "System.h"

using namespace MbD;

std::shared_ptr<SphSphJoint> MbD::SphSphJoint::With()
{
	auto inst = std::make_shared<SphSphJoint>();
	inst->initialize();
	return inst;
}

std::shared_ptr<SphSphJoint> MbD::SphSphJoint::With(const char* str)
{
	auto inst = std::make_shared<SphSphJoint>(str);
	inst->initialize();
	return inst;
}

void MbD::SphSphJoint::initializeGlobally()
{
	if (constraints->empty())
	{
		auto distxyIJ = DistanceConstraintIJ::With(efrmI, efrmJ);
		distxyIJ->setConstant(distanceIJ);
		addConstraint(distxyIJ);
		root()->hasChanged = true;
	}
	else {
		CompoundJoint::initializeGlobally();
	}
}
