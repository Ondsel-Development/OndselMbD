/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "MBDynClampJoint.h"
#include "ASMTAssembly.h"
#include "ASMTFixedJoint.h"

using namespace MbD;

std::shared_ptr<MBDynClampJoint> MbD::MBDynClampJoint::With()
{
	auto inst = std::make_shared<MBDynClampJoint>();
	inst->initialize();
	return inst;
}

void MbD::MBDynClampJoint::parseMBDyn(std::string statement)
{
	MBDynJoint::parseMBDyn(statement);
	assert(joint_type == "clamp");
	return;
}

void MbD::MBDynClampJoint::createASMT()
{
	auto asmtJoint = ASMTFixedJoint::With();
	asmtAssembly()->addJoint(asmtJoint);
	asmtItem = asmtJoint;
	MBDynJoint::createASMT();

}

void MbD::MBDynClampJoint::readMarkerI(std::vector<std::string>& args)
{
	//mkr1 should be on assembly which doesn't exist in MBDyn
	//mkr2 is on the node
	mkr1 = MBDynMarker::With();
	mkr1->container = this;
	mkr1->nodeStr = "Assembly";
	mkr1->rPmP = std::make_shared<FullColumn<double>>(3);
	mkr1->aAPm = FullMatrix<double>::identitysptr(3);
}

void MbD::MBDynClampJoint::readMarkerJ(std::vector<std::string>& args)
{
	if (args.empty()) return;
	mkr2 = MBDynMarker::With();
	mkr2->container = this;
	mkr2->nodeStr = readStringNoSpacesOffTop(args);
	mkr2->parseMBDynClamp(args);
}
