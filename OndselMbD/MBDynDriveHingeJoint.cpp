/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "MBDynDriveHingeJoint.h"
#include "ASMTMarker.h"
#include "ASMTJoint.h"
#include "ASMTRotationalMotion.h"
#include "ASMTAssembly.h"

using namespace MbD;

std::shared_ptr<MBDynDriveHingeJoint> MbD::MBDynDriveHingeJoint::With()
{
	auto inst = std::make_shared<MBDynDriveHingeJoint>();
	inst->initialize();
	return inst;
}

void MbD::MBDynDriveHingeJoint::parseMBDyn(std::string line)
{
	MBDynJoint::parseMBDyn(line);
	readFunction(arguments);
}

void MbD::MBDynDriveHingeJoint::createASMT()
{
	mkr1->createASMT();
	if (mkr2) mkr2->createASMT();
	auto asmtAsm = asmtAssembly();
	auto asmtMotion = std::make_shared<ASMTRotationalMotion>();
	asmtItem = asmtMotion;
	asmtMotion->setName(label);
	asmtMotion->setMarkerI(std::static_pointer_cast<ASMTMarker>(mkr1->asmtItem));
	asmtMotion->setMarkerJ(std::static_pointer_cast<ASMTMarker>(mkr2->asmtItem));
	asmtMotion->setRotationZ(formula);
	asmtAsm->addMotion(asmtMotion);
	return;
}

std::shared_ptr<ASMTJoint> MbD::MBDynDriveHingeJoint::asmtClassNew()
{
	assert(false);
	return std::make_shared<ASMTJoint>();
}
