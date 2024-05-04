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

std::shared_ptr<MBDynTotalJoint> MbD::MBDynTotalJoint::With()
{
	auto inst = std::make_shared<MBDynTotalJoint>();
	inst->initialize();
	return inst;
}

void MbD::MBDynTotalJoint::parseMBDyn(std::string statement)
{
	MBDynJoint::parseMBDyn(statement);
	readPositionConstraints(arguments);
	readOrientationConstraints(arguments);
	return;
}

void MbD::MBDynTotalJoint::readMarkerI(std::vector<std::string>& args)
{
	mkr1 = MBDynMarker::With();
	mkr1->container = this;
	mkr1->nodeStr = readStringNoSpacesOffTop(args);
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
	mkr2 = MBDynMarker::With();
	mkr2->container = this;
	mkr2->nodeStr = readStringNoSpacesOffTop(args);
	mkr2->parseMBDynTotalJointMarker(args);
}

void MbD::MBDynTotalJoint::readPositionConstraints(std::vector<std::string>& args)
{
	std::vector<std::string> tokens{ "position", "constraint" };
	assert(lineHasTokens(popOffTop(args), tokens));
	positionConstraints = std::vector<std::string>();
	positionConstraints.push_back(readStringNoSpacesOffTop(args));
	positionConstraints.push_back(readStringNoSpacesOffTop(args));
	positionConstraints.push_back(readStringNoSpacesOffTop(args));
	readPositionFormulas(args);
}

void MbD::MBDynTotalJoint::readOrientationConstraints(std::vector<std::string>& args)
{
	std::vector<std::string> tokens{ "orientation", "constraint" };
	assert(lineHasTokens(popOffTop(args), tokens));
	orientationConstraints = std::vector<std::string>();
	orientationConstraints.push_back(readStringNoSpacesOffTop(args));
	orientationConstraints.push_back(readStringNoSpacesOffTop(args));
	orientationConstraints.push_back(readStringNoSpacesOffTop(args));
	readOrientationFormulas(args);
}

void MbD::MBDynTotalJoint::readPositionFormulas(std::vector<std::string>& args)
{
	std::string str = readStringNoSpacesOffTop(args);
	if (str == "null") return;
	assert(false);
}

void MbD::MBDynTotalJoint::readOrientationFormulas(std::vector<std::string>& args)
{
	std::string str = readStringNoSpacesOffTop(args);
	if (str == "null") { return; }
	else if (str == "single") {
		auto vec3 = readVector3(args);
		assert(vec3->at(0) == 0 && vec3->at(1) == 0 && vec3->at(2) == 1);
		assert(readStringNoSpacesOffTop(args) == "string");
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
		auto asmtJoint = asmtJointNew();
		asmtAssembly()->addJoint(asmtJoint);
		asmtItem = asmtJoint;
		MBDynJoint::createASMT();
	}
	else if (!hasDOF() && hasFormulas()) {
		mkr1->createASMT();
		if (mkr2) mkr2->createASMT();
		auto asmtAsm = asmtAssembly();
		auto asmtMotion = ASMTGeneralMotion::With();
		asmtItem = asmtMotion;
		asmtMotion->setName(label);
		asmtMotion->setMarkerI(std::static_pointer_cast<ASMTMarker>(mkr1->asmtItem));
		asmtMotion->setMarkerJ(std::static_pointer_cast<ASMTMarker>(mkr2->asmtItem));
		asmtAsm->addMotion(asmtMotion);
		for (size_t i = 0; i < 3; i++)
		{
			asmtMotion->rIJI->atput(i, asmtFormula(positionFormulas.at(i)));
			asmtMotion->angIJJ->atput(i, asmtFormula(orientationFormulas.at(i)));
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

std::shared_ptr<ASMTJoint> MbD::MBDynTotalJoint::asmtJointNew()
{
	if (
		positionConstraints[0] == "active" &&
		positionConstraints[1] == "active" &&
		positionConstraints[2] == "active" &&
		orientationConstraints[0] == "active" &&
		orientationConstraints[1] == "active" &&
		orientationConstraints[2] == "active"
		)	return ASMTFixedJoint::With();
	if (
		positionConstraints[0] == "active" &&
		positionConstraints[1] == "active" &&
		positionConstraints[2] == "inactive" &&
		orientationConstraints[0] == "active" &&
		orientationConstraints[1] == "active" &&
		orientationConstraints[2] == "active"
		)	return ASMTTranslationalJoint::With();
	if (
		positionConstraints[0] == "active" &&
		positionConstraints[1] == "active" &&
		positionConstraints[2] == "active" &&
		orientationConstraints[0] == "active" &&
		orientationConstraints[1] == "active" &&
		orientationConstraints[2] == "inactive"
		)	return ASMTRevoluteJoint::With();
	if (
		positionConstraints[0] == "active" &&
		positionConstraints[1] == "active" &&
		positionConstraints[2] == "inactive" &&
		orientationConstraints[0] == "active" &&
		orientationConstraints[1] == "active" &&
		orientationConstraints[2] == "inactive"
		)	return ASMTCylindricalJoint::With();
	if (
		positionConstraints[0] == "active" &&
		positionConstraints[1] == "active" &&
		positionConstraints[2] == "active" &&
		orientationConstraints[0] == "inactive" &&
		orientationConstraints[1] == "inactive" &&
		orientationConstraints[2] == "inactive"
		)	return ASMTSphericalJoint::With();
	if (
		positionConstraints[0] == "inactive" &&
		positionConstraints[1] == "inactive" &&
		positionConstraints[2] == "inactive" &&
		orientationConstraints[0] == "active" &&
		orientationConstraints[1] == "active" &&
		orientationConstraints[2] == "active"
		)	return ASMTNoRotationJoint::With();
	if (
		positionConstraints[0] == "active" &&
		positionConstraints[1] == "active" &&
		positionConstraints[2] == "inactive" &&
		orientationConstraints[0] == "inactive" &&
		orientationConstraints[1] == "inactive" &&
		orientationConstraints[2] == "inactive"
		)	return ASMTPointInLineJoint::With();
	if (
		positionConstraints[0] == "inactive" &&
		positionConstraints[1] == "inactive" &&
		positionConstraints[2] == "active" &&
		orientationConstraints[0] == "inactive" &&
		orientationConstraints[1] == "inactive" &&
		orientationConstraints[2] == "inactive"
		)	return ASMTPointInPlaneJoint::With();
	assert(false);
	return ASMTJoint::With();
}
