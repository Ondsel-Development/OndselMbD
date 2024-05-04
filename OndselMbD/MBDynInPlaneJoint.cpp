/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "MBDynInPlaneJoint.h"
#include "ASMTPointInPlaneJoint.h"
#include "ASMTAssembly.h"

using namespace MbD;

std::shared_ptr<MBDynInPlaneJoint> MbD::MBDynInPlaneJoint::With()
{
	auto inst = std::make_shared<MBDynInPlaneJoint>();
	inst->initialize();
	return inst;
}

void MbD::MBDynInPlaneJoint::parseMBDyn(std::string line)
{
	MBDynJoint::parseMBDyn(line);
}

void MbD::MBDynInPlaneJoint::createASMT()
{
	auto asmtJoint = ASMTPointInPlaneJoint::With();
	asmtAssembly()->addJoint(asmtJoint);
	asmtItem = asmtJoint;
	MBDynJoint::createASMT();
}
