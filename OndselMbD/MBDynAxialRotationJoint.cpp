/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "MBDynAxialRotationJoint.h"
#include "ASMTAssembly.h"
#include "ASMTRevoluteJoint.h"
#include "ASMTRotationalMotion.h"

using namespace MbD;

void MbD::MBDynAxialRotationJoint::parseMBDyn(std::string line)
{
	MBDynJoint::parseMBDyn(line);
	readFunction(arguments);
}

void MbD::MBDynAxialRotationJoint::createASMT()
{
	MBDynJoint::createASMT();
	auto asmtAsm = asmtAssembly();
	asmtMotion = std::make_shared<ASMTRotationalMotion>();
	asmtMotion->setName(name + "Motion");
	asmtMotion->setMotionJoint(asmtItem->fullName(""));
	asmtMotion->setRotationZ(asmtFormulaIntegral(formula));
	asmtAsm->addMotion(asmtMotion);
	return;
}

std::shared_ptr<ASMTJoint> MbD::MBDynAxialRotationJoint::asmtClassNew()
{
	return std::make_shared<ASMTRevoluteJoint>();
}

void MbD::MBDynAxialRotationJoint::outputLine(int i, std::ostream& os)
{
	auto id = nodeidAt(name);
	auto asmtJoint = std::static_pointer_cast<ASMTJoint>(asmtItem);
	auto aFII = asmtJoint->aFII(i)->plusFullColumn(asmtMotion->aFII(i));
	auto aTII = asmtJoint->aTII(i)->plusFullColumn(asmtMotion->aTII(i));
	auto aFIO = asmtJoint->aFIO(i)->plusFullColumn(asmtMotion->aFIO(i));
	auto aTIO = asmtJoint->aTIO(i)->plusFullColumn(asmtMotion->aTIO(i));
	os << id << " ";
	os << aFII->at(0) << " " << aFII->at(1) << " " << aFII->at(2) << " ";
	os << aTII->at(0) << " " << aTII->at(1) << " " << aTII->at(2) << " ";
	os << aFIO->at(0) << " " << aFIO->at(1) << " " << aFIO->at(2) << " ";
	os << aTIO->at(0) << " " << aTIO->at(1) << " " << aTIO->at(2) << " ";
	os << std::endl;
}
