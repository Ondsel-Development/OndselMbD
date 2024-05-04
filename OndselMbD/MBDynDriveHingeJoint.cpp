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
	auto asmtMotion = ASMTRotationalMotion::With();
	asmtMotion->setRotationZ(formula);
	asmtAssembly()->addMotion(asmtMotion);
	asmtItem = asmtMotion;
	MBDynJoint::createASMT();
}
