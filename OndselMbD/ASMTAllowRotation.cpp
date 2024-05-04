/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "ASMTAllowRotation.h"
#include "ASMTAssembly.h"
#include "ASMTJoint.h"
#include "AllowZRotation.h"

using namespace MbD;

std::shared_ptr<ASMTAllowRotation> MbD::ASMTAllowRotation::With()
{
	auto inst = std::make_shared<ASMTAllowRotation>();
	inst->initialize();
	return inst;
}

void MbD::ASMTAllowRotation::parseASMT(std::vector<std::string>& lines)
{
	readName(lines);
	if (lines[0].find("MarkerI") != std::string::npos) {
		readMarkerI(lines);
		readMarkerJ(lines);
	}
	readMotionJoint(lines);
}

void MbD::ASMTAllowRotation::readMotionJoint(std::vector<std::string>& lines)
{
	assert(readStringNoSpacesOffTop(lines) == "MotionJoint");
	motionJoint = readStringNoSpacesOffTop(lines);
}

std::shared_ptr<JointIJ> MbD::ASMTAllowRotation::mbdClassNew()
{
	return AllowZRotation::With();
}

void MbD::ASMTAllowRotation::setMotionJoint(std::string motionJoint)
{
	assert(false);
}

void MbD::ASMTAllowRotation::storeOnLevel(std::ofstream& os, size_t level)
{
	storeOnLevelString(os, level, "AllowRotation");
	storeOnLevelString(os, level + 1, "Name");
	storeOnLevelString(os, level + 2, name);
	ASMTItemIJ::storeOnLevel(os, level);
	storeOnLevelString(os, level + 1, "MotionJoint");
	storeOnLevelString(os, level + 2, motionJoint);
}

void MbD::ASMTAllowRotation::storeOnTimeSeries(std::ofstream& os)
{
	os << "AllowRotationSeries\t" << fullName("") << std::endl;
	ASMTItemIJ::storeOnTimeSeries(os);
}
