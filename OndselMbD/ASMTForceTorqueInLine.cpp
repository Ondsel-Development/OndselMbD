/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "ASMTForceTorqueInLine.h"
#include "ASMTAssembly.h"
#include "ASMTMarker.h"
#include "ForceTorqueInLine.h"
#include "SymbolicParser.h"
#include "BasicUserFunction.h"
#include "Constant.h"

using namespace MbD;

std::shared_ptr<ASMTForceTorqueInLine> MbD::ASMTForceTorqueInLine::With()
{
	auto inst = std::make_shared<ASMTForceTorqueInLine>();
	inst->initialize();
	return inst;
}

void MbD::ASMTForceTorqueInLine::parseASMT(std::vector<std::string>& lines)
{
	ASMTForceTorque::parseASMT(lines);
	readTension(lines);
	readTwist(lines);
}

void MbD::ASMTForceTorqueInLine::readTension(std::vector<std::string>& lines)
{
	assert(readStringNoSpacesOffTop(lines) == "tension");
	tensionFunc = popOffTop(lines);
}

void MbD::ASMTForceTorqueInLine::readTwist(std::vector<std::string>& lines)
{
	assert(readStringNoSpacesOffTop(lines) == "twist");
	twistFunc = popOffTop(lines);
}

void MbD::ASMTForceTorqueInLine::storeOnLevel(std::ofstream& os, size_t level)
{
	storeOnLevelString(os, level, "InLineForceTorque");
	storeOnLevelString(os, level + 1, "Name");
	storeOnLevelString(os, level + 2, name);
	ASMTItemIJ::storeOnLevel(os, level);
	storeOnLevelString(os, level + 1, "tension");
	storeOnLevelString(os, level + 2, tensionFunc);
	storeOnLevelString(os, level + 1, "twist");
	storeOnLevelString(os, level + 2, twistFunc);
}

void MbD::ASMTForceTorqueInLine::storeOnTimeSeries(std::ofstream& os)
{
	os << "InLineForceTorqueSeries\t" << fullName("") << std::endl;
	ASMTItemIJ::storeOnTimeSeries(os);
}

void MbD::ASMTForceTorqueInLine::createMbD()
{
	ASMTForceTorque::createMbD();
	auto mrkI = std::static_pointer_cast<EndFramec>(markerI->mbdObject);
	auto mrkJ = std::static_pointer_cast<EndFramec>(markerJ->mbdObject);
	auto mbdForceTorqueInLine = ForceTorqueInLine::With(mrkI, mrkJ);
	mbdForceTorqueInLine->name = fullName("");
	Symsptr tension, twist;

	auto parser = functionParser();
	auto userFunc = std::make_shared<BasicUserFunction>(tensionFunc, 1.0);
	parser->parseUserFunction(userFunc);
	tension = parser->stack->top();
	tension = Symbolic::times(tension, sptrConstant(asmtUnits()->force));
	tension->createMbD();
	//std::cout << *tension << std::endl;
	auto simple = tension->simplified(tension);
	//std::cout << *simple << std::endl;
	mbdForceTorqueInLine->tension(simple);

	parser = functionParser();
	userFunc = std::make_shared<BasicUserFunction>(twistFunc, 1.0);
	parser->parseUserFunction(userFunc);
	twist = parser->stack->top();
	twist = Symbolic::times(twist, sptrConstant(asmtUnits()->torque));
	twist->createMbD();
	//std::cout << *twist << std::endl;
	simple = twist->simplified(twist);
	//std::cout << *simple << std::endl;
	mbdForceTorqueInLine->twist(simple);
	mbdObject = mbdForceTorqueInLine;
	mbdSys()->addForceTorque(mbdForceTorqueInLine);
}
