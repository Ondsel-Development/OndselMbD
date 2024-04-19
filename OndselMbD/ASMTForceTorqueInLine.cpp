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
	assert(readStringOffTop(lines) == "tension");
	tensionFunc = popOffTop(lines);
}

void MbD::ASMTForceTorqueInLine::readTwist(std::vector<std::string>& lines)
{
	assert(readStringOffTop(lines) == "twist");
	twistFunc = popOffTop(lines);
}

void MbD::ASMTForceTorqueInLine::createMbD(std::shared_ptr<System> mbdSys, std::shared_ptr<Units> mbdUnits)
{
	ASMTForceTorque::createMbD(mbdSys, mbdUnits);
	auto mrkI = std::static_pointer_cast<EndFramec>(markerI->mbdObject);
	auto mrkJ = std::static_pointer_cast<EndFramec>(markerJ->mbdObject);
	auto mbdForceTorqueInLine = ForceTorqueInLine::With(mrkI, mrkJ);
	mbdForceTorqueInLine->name = this->fullName("");
	Symsptr tension, twist;

	auto parser = functionParser();
	auto userFunc = std::make_shared<BasicUserFunction>(tensionFunc, 1.0);
	parser->parseUserFunction(userFunc);
	tension = parser->stack->top();
	tension = Symbolic::times(tension, sptrConstant(1.0 / mbdUnits->angle));
	tension->createMbD(mbdSys, mbdUnits);
	//std::cout << *tension << std::endl;
	auto simple = tension->simplified(tension);
	//std::cout << *simple << std::endl;
	mbdForceTorqueInLine->tension(simple);

	parser = functionParser();
	userFunc = std::make_shared<BasicUserFunction>(twistFunc, 1.0);
	parser->parseUserFunction(userFunc);
	twist = parser->stack->top();
	twist = Symbolic::times(twist, sptrConstant(1.0 / mbdUnits->angle));
	twist->createMbD(mbdSys, mbdUnits);
	//std::cout << *twist << std::endl;
	simple = twist->simplified(twist);
	//std::cout << *simple << std::endl;
	mbdForceTorqueInLine->twist(simple);
	mbdObject = mbdForceTorqueInLine;
	mbdSys->addForceTorque(mbdForceTorqueInLine);
}

std::shared_ptr<ForceFunctionParser> MbD::ASMTForceTorqueInLine::functionParser()
{
	auto parser = ForceFunctionParser::With();
	parser->container = this;
	parser->initVariables();
	parser->initgeoIJs();
	return parser;
}
