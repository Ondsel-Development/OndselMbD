/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "CompoundJoint.h"

using namespace MbD;

MbD::CompoundJoint::CompoundJoint(const char* str) : Joint(str)
{
	assert(false);
}

std::shared_ptr<CompoundJoint> MbD::CompoundJoint::With()
{
	auto inst = std::make_shared<CompoundJoint>();
	inst->initialize();
	return inst;
}

std::shared_ptr<CompoundJoint> MbD::CompoundJoint::With(const char* str)
{
	auto inst = std::make_shared<CompoundJoint>(str);
	inst->initialize();
	return inst;
}
