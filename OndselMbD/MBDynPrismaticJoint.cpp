/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "MBDynPrismaticJoint.h"
#include "ASMTNoRotationJoint.h"
#include "ASMTAssembly.h"

using namespace MbD;

std::shared_ptr<MBDynPrismaticJoint> MbD::MBDynPrismaticJoint::With()
{
	auto inst = std::make_shared<MBDynPrismaticJoint>();
	inst->initialize();
	return inst;
}

void MbD::MBDynPrismaticJoint::parseMBDyn(std::string line)
{
	MBDynJoint::parseMBDyn(line);
}

void MbD::MBDynPrismaticJoint::createASMT()
{
	auto asmtJoint = ASMTNoRotationJoint::With();
	asmtAssembly()->addJoint(asmtJoint);
	asmtItem = asmtJoint;
	MBDynJoint::createASMT();
}
