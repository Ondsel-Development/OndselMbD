/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <regex>

#include "MBDynJoint.h"
#include "ASMTMarker.h"
#include "ASMTPart.h"
#include "ASMTJoint.h"
#include "ASMTAssembly.h"
#include "ASMTRevoluteJoint.h"
#include "ASMTRotationalMotion.h"
#include "ASMTPointInLineJoint.h"
#include "ASMTNoRotationJoint.h"
#include "ASMTFixedJoint.h"
#include "ASMTSphericalJoint.h"
#include "MBDynTotalJoint.h"
#include "MBDynClampJoint.h"
#include "MBDynAxialRotationJoint.h"
#include "MBDynDriveHingeJoint.h"
#include "MBDynInLineJoint.h"
#include "MBDynInPlaneJoint.h"
#include "MBDynPrismaticJoint.h"
#include "MBDynRevoluteHingeJoint.h"
#include "MBDynRevolutePinJoint.h"
#include "MBDynSphericalHingeJoint.h"
#include "MBDynRodJoint.h"

using namespace MbD;

std::shared_ptr<MBDynJoint> MbD::MBDynJoint::newJoint(std::string statement)
{
	std::vector<std::string> tokens;
	tokens = { "axial ", "rotation," };
	if (lineHasTokens(statement, tokens)) {
		return std::make_shared<MBDynAxialRotationJoint>();
	}
	tokens = { "clamp," };
	if (lineHasTokens(statement, tokens)) {
		return std::make_shared<MBDynClampJoint>();
	}
	tokens = { "drive ", "hinge," };
	if (lineHasTokens(statement, tokens)) {
		return std::make_shared<MBDynDriveHingeJoint>();
	}
	tokens = { "in ", "line," };
	if (lineHasTokens(statement, tokens)) {
		return std::make_shared<MBDynInLineJoint>();
	}
	tokens = { "in ", "plane," };
	if (lineHasTokens(statement, tokens)) {
		return std::make_shared<MBDynInPlaneJoint>();
	}
	tokens = { "prismatic," };
	if (lineHasTokens(statement, tokens)) {
		return std::make_shared<MBDynPrismaticJoint>();
	}
	tokens = { "revolute ", "hinge," };
	if (lineHasTokens(statement, tokens)) {
		return std::make_shared<MBDynRevoluteHingeJoint>();
	}
	tokens = { "revolute ", "pin," };
	if (lineHasTokens(statement, tokens)) {
		return std::make_shared<MBDynRevolutePinJoint>();
	}
	tokens = { "spherical ", "hinge," };
	if (lineHasTokens(statement, tokens)) {
		return std::make_shared<MBDynSphericalHingeJoint>();
	}
	tokens = { "total ", "joint," };
	if (lineHasTokens(statement, tokens)) {
		return std::make_shared<MBDynTotalJoint>();
	}
	tokens = { "rod," };
	if (lineHasTokens(statement, tokens)) {
		return std::make_shared<MBDynRodJoint>();
	}
	assert(false);
	return std::make_shared<MBDynJoint>();
}

void MbD::MBDynJoint::initialize()
{
	assert(false);
}

void MbD::MBDynJoint::parseMBDyn(std::string line)
{
	jointString = line;
	arguments = collectArgumentsFor("joint", line);
	readLabel(arguments);
	readJointType(arguments);
	readMarkerI(arguments);
	readMarkerJ(arguments);

}

void MbD::MBDynJoint::readJointType(std::vector<std::string>& args)
{
	joint_type = readJointTypeOffTop(args);
}

void MbD::MBDynJoint::readMarkerI(std::vector<std::string>& args)
{
	mkr1 = std::make_shared<MBDynMarker>();
	mkr1->owner = this;
	mkr1->nodeStr = readStringOffTop(args);
	auto _nodeNames = nodeNames();
	std::string nodeName;
	auto it = std::find_if(args.begin(), args.end(), [&](const std::string& s) {
		auto iss = std::istringstream(s);
		iss >> nodeName;
		if (std::find(_nodeNames.begin(), _nodeNames.end(), nodeName) != _nodeNames.end()) return true;
		return false;
		});
	auto markerArgs = std::vector<std::string>(args.begin(), it);
	args.erase(args.begin(), it);
	mkr1->parseMBDyn(markerArgs);
}

void MbD::MBDynJoint::readMarkerJ(std::vector<std::string>& args)
{
	if (args.empty()) return;
	mkr2 = std::make_shared<MBDynMarker>();
	mkr2->owner = this;
	mkr2->nodeStr = readStringOffTop(args);
	mkr2->parseMBDyn(args);
}

void MbD::MBDynJoint::readTotalJointMarkerI(std::vector<std::string>& args)
{
	mkr1 = std::make_shared<MBDynMarker>();
	mkr1->owner = this;
	mkr1->nodeStr = readStringOffTop(args);
	auto _nodeNames = nodeNames();
	std::string nodeName;
	auto it = std::find_if(args.begin(), args.end(), [&](const std::string& s) {
		auto iss = std::istringstream(s);
		iss >> nodeName;
		if (std::find(_nodeNames.begin(), _nodeNames.end(), nodeName) != _nodeNames.end()) return true;
		return false;
		});
	auto markerArgs = std::vector<std::string>(args.begin(), it);
	args.erase(args.begin(), it);
	mkr1->parseMBDynTotalJointMarker(markerArgs);
}

void MbD::MBDynJoint::readTotalJointMarkerJ(std::vector<std::string>& args)
{
	if (args.empty()) return;
	mkr2 = std::make_shared<MBDynMarker>();
	mkr2->owner = this;
	mkr2->nodeStr = readStringOffTop(args);
	mkr2->parseMBDynTotalJointMarker(args);
}

void MbD::MBDynJoint::readClampMarkerJ(std::vector<std::string>& args)
{
	if (args.empty()) return;
	mkr2 = std::make_shared<MBDynMarker>();
	mkr2->owner = this;
	mkr2->nodeStr = readStringOffTop(args);
	mkr2->parseMBDynClamp(args);
}

void MbD::MBDynJoint::readFunction(std::vector<std::string>& args)
{
	if (args.empty()) return;
	std::string str;
	auto iss = std::istringstream(args.at(0));
	iss >> str;
	if (str.find("ramp") != std::string::npos) {
		args.erase(args.begin());
		std::string slope, initValue, initTime, finalTime;
		slope = popOffTop(args);
		initTime = popOffTop(args);
		finalTime = popOffTop(args);
		initValue = popOffTop(args);
		//f = slope*(time - t0) + f0
		auto ss = std::stringstream();
		ss << slope << "*(time - " << initTime << ") + " << initValue;
		formula = ss.str();
	}
	else if (str.find("single") != std::string::npos) {
		args.erase(args.begin());
		auto vec3 = readVector3(args);
		assert(vec3->at(0) == 0 && vec3->at(1) == 0 && vec3->at(2) == 1);
		assert(readStringOffTop(args) == "string");
		formula = popOffTop(args);
		formula = std::regex_replace(formula, std::regex("\""), "");
	}
	else if (str.find("string") != std::string::npos) {
		args.erase(args.begin());
		formula = popOffTop(args);
		formula = std::regex_replace(formula, std::regex("\""), "");
	}
	else {
		assert(false);
	}
}

void MbD::MBDynJoint::readTotalJointFunction(std::vector<std::string>& args)
{
	std::vector<std::string> tokens{ "position", "constraint" };
	assert(lineHasTokens(args[0], tokens));
	args.erase(args.begin());
	assert(readStringOffTop(args) == "active");
	assert(readStringOffTop(args) == "active");
	assert(readStringOffTop(args) == "active");
	assert(readStringOffTop(args) == "null");
	std::vector<std::string> tokens1{ "orientation", "constraint" };
	assert(lineHasTokens(args[0], tokens1));
	args.erase(args.begin());
	assert(readStringOffTop(args) == "active");
	assert(readStringOffTop(args) == "active");
	assert(readStringOffTop(args) == "rotation");
	readFunction(args);
}

void MbD::MBDynJoint::createASMT()
{
	mkr1->createASMT();
	if (mkr2) mkr2->createASMT();
	auto asmtAsm = asmtAssembly();
	auto asmtJoint = asmtClassNew();
	asmtItem = asmtJoint;
	asmtJoint->setName(label);
	asmtJoint->setMarkerI(std::static_pointer_cast<ASMTMarker>(mkr1->asmtItem));
	asmtJoint->setMarkerJ(std::static_pointer_cast<ASMTMarker>(mkr2->asmtItem));
	asmtAsm->addJoint(asmtJoint);
}

std::shared_ptr<ASMTJoint> MbD::MBDynJoint::asmtClassNew()
{
	assert(false);
	return std::make_shared<ASMTJoint>();
}

void MbD::MBDynJoint::outputLine(size_t i, std::ostream& os)
{
	auto id = labelIDat(label);
	auto asmtJoint = std::static_pointer_cast<ASMTJoint>(asmtItem);
	auto aFII = asmtJoint->aFII(i);
	auto aTII = asmtJoint->aTII(i);
	auto aFIO = asmtJoint->aFIO(i);
	auto aTIO = asmtJoint->aTIO(i);
	os << id << " ";
	os << aFII->at(0) << " " << aFII->at(1) << " " << aFII->at(2) << " ";
	os << aTII->at(0) << " " << aTII->at(1) << " " << aTII->at(2) << " ";
	os << aFIO->at(0) << " " << aFIO->at(1) << " " << aFIO->at(2) << " ";
	os << aTIO->at(0) << " " << aTIO->at(1) << " " << aTIO->at(2) << " ";
	os << std::endl;
}
