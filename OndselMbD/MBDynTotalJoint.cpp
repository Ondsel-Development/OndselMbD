/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <regex>

#include "MBDynTotalJoint.h"
#include "ASMTAssembly.h"
#include "ASMTJoint.h"
#include "ASMTGeneralMotion.h"
#include "ASMTRevoluteJoint.h"
#include "ASMTCylindricalJoint.h"
#include "ASMTSphericalJoint.h"
#include "ASMTFixedJoint.h"
#include "ASMTTranslationalJoint.h"
#include "ASMTPointInLineJoint.h"
#include "ASMTPointInPlaneJoint.h"
#include "ASMTNoRotationJoint.h"

using namespace MbD;

void MbD::MBDynTotalJoint::parseMBDyn(std::string statement)
{
	MBDynJoint::parseMBDyn(statement);
	readPositionConstraints(arguments);
	readOrientationConstraints(arguments);
	return;
}

void MbD::MBDynTotalJoint::readMarkerI(std::vector<std::string>& args)
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

void MbD::MBDynTotalJoint::readMarkerJ(std::vector<std::string>& args)
{
	if (args.empty()) return;
	mkr2 = std::make_shared<MBDynMarker>();
	mkr2->owner = this;
	mkr2->nodeStr = readStringOffTop(args);
	mkr2->parseMBDynTotalJointMarker(args);
}

void MbD::MBDynTotalJoint::readPositionConstraints(std::vector<std::string>& args)
{
	std::vector<std::string> tokens{ "position", "constraint" };
	assert(lineHasTokens(popOffTop(args), tokens));
	positionConstraints = std::vector<std::string>();
	positionConstraints.push_back(readStringOffTop(args));
	positionConstraints.push_back(readStringOffTop(args));
	positionConstraints.push_back(readStringOffTop(args));
	readPositionFormulas(args);
}

void MbD::MBDynTotalJoint::readOrientationConstraints(std::vector<std::string>& args)
{
	std::vector<std::string> tokens{ "orientation", "constraint" };
	assert(lineHasTokens(popOffTop(args), tokens));
	orientationConstraints = std::vector<std::string>();
	orientationConstraints.push_back(readStringOffTop(args));
	orientationConstraints.push_back(readStringOffTop(args));
	orientationConstraints.push_back(readStringOffTop(args));
	readOrientationFormulas(args);
}

void MbD::MBDynTotalJoint::readPositionFormulas(std::vector<std::string>& args)
{
	std::string str = readStringOffTop(args);
	if (str == "null") return;
	assert(false);
}

void MbD::MBDynTotalJoint::readOrientationFormulas(std::vector<std::string>& args)
{
	std::string str = readStringOffTop(args);
	if (str == "null") { return; }
	else if (str == "single") {
		auto vec3 = readVector3(args);
		assert(vec3->at(0) == 0 && vec3->at(1) == 0 && vec3->at(2) == 1);
		assert(readStringOffTop(args) == "string");
		formula = popOffTop(args);
		formula = std::regex_replace(formula, std::regex("\""), "");
		orientationFormulas = std::vector<std::string>();
		for (auto& status : orientationConstraints) {
			if (status == "active") {
				orientationFormulas.push_back("");
			}
			else if (status == "rotation") {
				orientationFormulas.push_back(formula);
			}
			else { assert(false); }
		}
		return;
	}
	assert(false);
}

void MbD::MBDynTotalJoint::createASMT()
{
	if (hasDOF() && !hasFormulas()) {
		MBDynJoint::createASMT();
	}
	else if (!hasDOF() && hasFormulas()) {
		mkr1->createASMT();
		if (mkr2) mkr2->createASMT();
		auto asmtAsm = asmtAssembly();
		auto asmtMotion = std::make_shared<ASMTGeneralMotion>();
		asmtItem = asmtMotion;
		asmtMotion->setName(name);
		asmtMotion->setMarkerI(mkr1->asmtItem->fullName(""));
		asmtMotion->setMarkerJ(mkr2->asmtItem->fullName(""));
		asmtAsm->addMotion(asmtMotion);
		for (size_t i = 0; i < 3; i++)
		{
			asmtMotion->rIJI->atiput(i, asmtFormula(positionFormulas.at(i)));
			asmtMotion->angIJJ->atiput(i, asmtFormula(orientationFormulas.at(i)));
		}
	}
	else {
		assert(false);
	}
}

bool MbD::MBDynTotalJoint::hasDOF()
{
	auto it = std::find_if(positionConstraints.begin(), positionConstraints.end(), [](std::string str) {return str == "inactive"; });
	if (it != positionConstraints.end()) return true;
	it = std::find_if(orientationConstraints.begin(), orientationConstraints.end(), [](std::string str) {return str == "inactive"; });
	if (it != orientationConstraints.end()) return true;
	return false;
}

bool MbD::MBDynTotalJoint::hasFormulas()
{
	auto it = std::find_if(positionFormulas.begin(), positionFormulas.end(), [](std::string str) {return str != ""; });
	if (it != positionFormulas.end()) return true;
	it = std::find_if(orientationFormulas.begin(), orientationFormulas.end(), [](std::string str) {return str != ""; });
	if (it != orientationFormulas.end()) return true;
	return false;
}

std::shared_ptr<ASMTJoint> MbD::MBDynTotalJoint::asmtClassNew()
{
	if (
		positionConstraints[0] == "active" &&
		positionConstraints[1] == "active" &&
		positionConstraints[2] == "active" &&
		orientationConstraints[0] == "active" &&
		orientationConstraints[1] == "active" &&
		orientationConstraints[2] == "active"
		)	return std::make_shared<ASMTFixedJoint>();
	if (
		positionConstraints[0] == "active" &&
		positionConstraints[1] == "active" &&
		positionConstraints[2] == "inactive" &&
		orientationConstraints[0] == "active" &&
		orientationConstraints[1] == "active" &&
		orientationConstraints[2] == "active"
		)	return std::make_shared<ASMTTranslationalJoint>();
	if (
		positionConstraints[0] == "active" &&
		positionConstraints[1] == "active" &&
		positionConstraints[2] == "active" &&
		orientationConstraints[0] == "active" &&
		orientationConstraints[1] == "active" &&
		orientationConstraints[2] == "inactive"
		)	return std::make_shared<ASMTRevoluteJoint>();
	if (
		positionConstraints[0] == "active" &&
		positionConstraints[1] == "active" &&
		positionConstraints[2] == "inactive" &&
		orientationConstraints[0] == "active" &&
		orientationConstraints[1] == "active" &&
		orientationConstraints[2] == "inactive"
		)	return std::make_shared<ASMTCylindricalJoint>();
	if (
		positionConstraints[0] == "active" &&
		positionConstraints[1] == "active" &&
		positionConstraints[2] == "active" &&
		orientationConstraints[0] == "inactive" &&
		orientationConstraints[1] == "inactive" &&
		orientationConstraints[2] == "inactive"
		)	return std::make_shared<ASMTSphericalJoint>();
	if (
		positionConstraints[0] == "inactive" &&
		positionConstraints[1] == "inactive" &&
		positionConstraints[2] == "inactive" &&
		orientationConstraints[0] == "active" &&
		orientationConstraints[1] == "active" &&
		orientationConstraints[2] == "active"
		)	return std::make_shared<ASMTNoRotationJoint>();
	if (
		positionConstraints[0] == "active" &&
		positionConstraints[1] == "active" &&
		positionConstraints[2] == "inactive" &&
		orientationConstraints[0] == "inactive" &&
		orientationConstraints[1] == "inactive" &&
		orientationConstraints[2] == "inactive"
		)	return std::make_shared<ASMTPointInLineJoint>();
	if (
		positionConstraints[0] == "inactive" &&
		positionConstraints[1] == "inactive" &&
		positionConstraints[2] == "active" &&
		orientationConstraints[0] == "inactive" &&
		orientationConstraints[1] == "inactive" &&
		orientationConstraints[2] == "inactive"
		)	return std::make_shared<ASMTPointInPlaneJoint>();
	assert(false);
}
