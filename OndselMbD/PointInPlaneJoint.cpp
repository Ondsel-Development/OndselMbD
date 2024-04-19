/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "PointInPlaneJoint.h"
#include "System.h"

using namespace MbD;

MbD::PointInPlaneJoint::PointInPlaneJoint(const char*)
{
	assert(false);
}

std::shared_ptr<PointInPlaneJoint> MbD::PointInPlaneJoint::With()
{
	auto inst = std::make_shared<PointInPlaneJoint>();
	inst->initialize();
	return inst;
}

std::shared_ptr<PointInPlaneJoint> MbD::PointInPlaneJoint::With(const char* str)
{
	auto inst = std::make_shared<PointInPlaneJoint>(str);
	inst->initialize();
	return inst;
}

void MbD::PointInPlaneJoint::initializeGlobally()
{
	if (constraints->empty())
	{
		this->createInPlaneConstraint();
		this->root()->hasChanged = true;
	}
	else {
		Joint::initializeGlobally();
	}
}
