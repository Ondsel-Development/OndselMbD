/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "GearJoint.h"
#include "GearConstraintIJ.h"
#include "System.h"

using namespace MbD;

MbD::GearJoint::GearJoint(const char*)
{
	assert(false);
}

std::shared_ptr<GearJoint> MbD::GearJoint::With()
{
	auto inst = std::make_shared<GearJoint>();
	inst->initialize();
	return inst;
}

std::shared_ptr<GearJoint> MbD::GearJoint::With(const char* str)
{
	auto inst = std::make_shared<GearJoint>(str);
	inst->initialize();
	return inst;
}

void MbD::GearJoint::initializeGlobally()
{
	if (constraints->empty())
	{
		auto gearIJ = GearConstraintIJ::With(frmI, frmJ);
		gearIJ->radiusI = radiusI;
		gearIJ->radiusJ = radiusJ;
		gearIJ->setConstant(std::numeric_limits<double>::min());
		addConstraint(gearIJ);
		this->root()->hasChanged = true;
	}
	else {
		Joint::initializeGlobally();
	}
}
