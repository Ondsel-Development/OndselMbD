/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
#include <fstream>	

#include "ASMTPerpendicularJoint.h"
#include "PerpendicularJoint.h"

using namespace MbD;

std::shared_ptr<ASMTPerpendicularJoint> MbD::ASMTPerpendicularJoint::With()
{
	auto inst = std::make_shared<ASMTPerpendicularJoint>();
	inst->initialize();
	return inst;
}

std::shared_ptr<JointIJ> MbD::ASMTPerpendicularJoint::mbdClassNew()
{
	return PerpendicularJoint::With();
}
