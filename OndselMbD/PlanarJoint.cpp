/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "PlanarJoint.h"
#include "System.h"

using namespace MbD;

MbD::PlanarJoint::PlanarJoint(const char*)
{
	assert(false);
}

std::shared_ptr<PlanarJoint> MbD::PlanarJoint::With()
{
	auto inst = std::make_shared<PlanarJoint>();
	inst->initialize();
	return inst;
}

std::shared_ptr<PlanarJoint> MbD::PlanarJoint::With(const char* str)
{
	auto inst = std::make_shared<PlanarJoint>(str);
	inst->initialize();
	return inst;
}

void MbD::PlanarJoint::initializeGlobally()
{
	if (constraints->empty())
	{
		this->createInPlaneConstraint();
		addConstraint(DirectionCosineConstraintIJ::With(frmI, frmJ, 2, 0));
		addConstraint(DirectionCosineConstraintIJ::With(frmI, frmJ, 2, 1));
		this->root()->hasChanged = true;
	}
	else {
		Joint::initializeGlobally();
	}
}
