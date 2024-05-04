/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "MBDynRevolutePinJoint.h"
#include "ASMTJoint.h"
#include "ASMTAssembly.h"

using namespace MbD;

std::shared_ptr<MBDynRevolutePinJoint> MbD::MBDynRevolutePinJoint::With()
{
	auto inst = std::make_shared<MBDynRevolutePinJoint>();
	inst->initialize();
	return inst;
}

void MbD::MBDynRevolutePinJoint::parseMBDyn(std::string line)
{
	MBDynJoint::parseMBDyn(line);
}

void MbD::MBDynRevolutePinJoint::createASMT()
{
	assert(false);
	auto asmtJoint = ASMTJoint::With();
	asmtAssembly()->addJoint(asmtJoint);
	asmtItem = asmtJoint;
	MBDynJoint::createASMT();
}
