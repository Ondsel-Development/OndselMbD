/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
#include <fstream>	

#include "ASMTTranslationalMotion.h"
#include "ASMTAssembly.h"
#include "SymbolicParser.h"
#include "BasicUserFunction.h"
#include "Constant.h"
#include "ASMTJoint.h"
#include "ZTranslation.h"
#include "ASMTTime.h"

using namespace MbD;

std::shared_ptr<ASMTTranslationalMotion> MbD::ASMTTranslationalMotion::With()
{
	auto inst = std::make_shared<ASMTTranslationalMotion>();
	inst->initialize();
	return inst;
}

void MbD::ASMTTranslationalMotion::parseASMT(std::vector<std::string>& lines)
{
	readName(lines);
	readMotionJoint(lines);
	readTranslationZ(lines);
}

void MbD::ASMTTranslationalMotion::createMbD()
{
	ASMTMotion::createMbD();
	auto parser = std::make_shared<SymbolicParser>();
	parser->container = this;
	auto geoTime = container->root()->geoTime();
	parser->variables->insert(std::make_pair("time", geoTime));
	auto userFunc = std::make_shared<BasicUserFunction>(translationZ, 1.0);
	parser->parseUserFunction(userFunc);
	auto& zIJ = parser->stack->top();
	zIJ = Symbolic::times(zIJ, sptrConstant(asmtUnits()->length));
	zIJ->createMbD();
	std::static_pointer_cast<ZTranslation>(mbdObject)->zBlk = zIJ->simplified(zIJ);
}

std::shared_ptr<JointIJ> MbD::ASMTTranslationalMotion::mbdClassNew()
{
	return ZTranslation::With();
}

void MbD::ASMTTranslationalMotion::readMotionJoint(std::vector<std::string>& lines)
{
	assert(readStringNoSpacesOffTop(lines) == "MotionJoint");
	motionJoint = readStringNoSpacesOffTop(lines);
}

void MbD::ASMTTranslationalMotion::readTranslationZ(std::vector<std::string>& lines)
{
	assert(readStringNoSpacesOffTop(lines) == "TranslationZ");
	translationZ = readStringNoSpacesOffTop(lines);
}

void MbD::ASMTTranslationalMotion::storeOnLevel(std::ofstream& os, size_t level)
{
	storeOnLevelString(os, level, "TranslationalMotion");
	storeOnLevelString(os, level + 1, "Name");
	storeOnLevelString(os, level + 2, name);
	ASMTItemIJ::storeOnLevel(os, level);
}

void MbD::ASMTTranslationalMotion::storeOnTimeSeries(std::ofstream& os)
{
	os << "TranslationalMotionSeries\t" << fullName("") << std::endl;
	ASMTItemIJ::storeOnTimeSeries(os);
}
