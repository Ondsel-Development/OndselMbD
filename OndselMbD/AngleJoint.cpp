/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "AngleJoint.h"
#include "System.h"
#include "DirectionCosineConstraintIJ.h"

using namespace MbD;

std::shared_ptr<AngleJoint> MbD::AngleJoint::With()
{
	auto inst = std::make_shared<AngleJoint>();
	inst->initialize();
	return inst;
}

std::shared_ptr<AngleJoint> MbD::AngleJoint::With(const char* str)
{
	auto inst = std::make_shared<AngleJoint>(str);
	inst->initialize();
	return inst;
}

void MbD::AngleJoint::initializeGlobally()
{
	if (constraints->empty())
	{
		auto dirCosIzJz = DirectionCosineConstraintIJ::With(efrmI, efrmJ, 2, 2);
		dirCosIzJz->setConstant(std::cos(theIzJz));
		addConstraint(dirCosIzJz);
		root()->hasChanged = true;
	}
	else {
		JointIJ::initializeGlobally();
	}
}
