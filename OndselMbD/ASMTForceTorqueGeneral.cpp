/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "ASMTForceTorqueGeneral.h"
#include "ASMTAssembly.h"
#include "ASMTMarker.h"
#include "ForceTorqueGeneral.h"
#include "SymbolicParser.h"
#include "BasicUserFunction.h"
#include "Constant.h"

using namespace MbD;

std::shared_ptr<ASMTForceTorqueGeneral> MbD::ASMTForceTorqueGeneral::With()
{
	auto inst = std::make_shared<ASMTForceTorqueGeneral>();
	inst->initialize();
	return inst;
}

void MbD::ASMTForceTorqueGeneral::initialize()
{
	markerKSign = "I";
	aFIeKe = FullColumn<std::string>::With(3);
	aTIeKe = FullColumn<std::string>::With(3);
}

void MbD::ASMTForceTorqueGeneral::storeOnLevel(std::ofstream& os, size_t level)
{
	assert(false);
}

void MbD::ASMTForceTorqueGeneral::storeOnTimeSeries(std::ofstream& os)
{
	os << "GeneralForceTorqueSeries\t" << fullName("") << std::endl;
	ASMTItemIJ::storeOnTimeSeries(os);
}

void MbD::ASMTForceTorqueGeneral::createMbD()
{
		ASMTForceTorque::createMbD();
		auto eFrmI = std::static_pointer_cast<EndFrameqc>(markerI->mbdObject);
		auto eFrmJ = std::static_pointer_cast<EndFrameqc>(markerJ->mbdObject);
		std::shared_ptr<ForceTorqueGeneral> forceTorqueGeneral;
		if (markerKSign == "O") {
			forceTorqueGeneral = ForceTorqueGeneral::OnFrmIandFrmJ(eFrmI, eFrmJ);
		}
		else {
			std::shared_ptr<EndFrameqc> efrmK;
			if (markerKSign == "J") {
				efrmK = eFrmJ;
			}
			else {
				efrmK = eFrmI;
			}
			forceTorqueGeneral = ForceTorqueGeneral::OnFrmIandFrmJwrtFrmK(eFrmI, eFrmJ, efrmK);
		}
		forceTorqueGeneral->name = fullName("");		
		auto aFIeKeFunc = FullColumn<Symsptr>::With(3);
		for (size_t i = 0; i < 3; i++)
		{
			auto aFIeKei = aFIeKe->at(i);
			if (aFIeKei != "") {
				auto parser = functionParser();
				auto userFunc = std::make_shared<BasicUserFunction>(aFIeKei, 1.0);
				parser->parseUserFunction(userFunc);
				auto aFIeKeiFunc = parser->stack->top();
				aFIeKeiFunc = Symbolic::times(aFIeKeiFunc, sptrConstant(asmtUnits()->force));
				aFIeKeiFunc->createMbD();
				auto simple = aFIeKeiFunc->simplified(aFIeKeiFunc);
				aFIeKeFunc->atput(i, simple);
			}
		}
		forceTorqueGeneral->forceFunctions(aFIeKeFunc);
		auto aTIeKeFunc = FullColumn<Symsptr>::With(3);
		for (size_t i = 0; i < 3; i++)
		{
			auto aTIeKei = aTIeKe->at(i);
			if (aTIeKei != "") {
				auto parser = functionParser();
				auto userFunc = std::make_shared<BasicUserFunction>(aTIeKei, 1.0);
				parser->parseUserFunction(userFunc);
				auto aTIeKeiFunc = parser->stack->top();
				aTIeKeiFunc = Symbolic::times(aTIeKeiFunc, sptrConstant(asmtUnits()->torque));
				aTIeKeiFunc->createMbD();
				auto simple = aTIeKeiFunc->simplified(aTIeKeiFunc);
				aTIeKeFunc->atput(i, simple);
			}
		}
		forceTorqueGeneral->torqueFunctions(aTIeKeFunc);
		mbdObject = forceTorqueGeneral;
		mbdSys()->addForceTorque(forceTorqueGeneral);
		forceTorqueGeneral->initializeLocally();
}

void MbD::ASMTForceTorqueGeneral::parseASMT(std::vector<std::string>& lines)
{
	ASMTForceTorque::parseASMT(lines);
	readFxOnI(lines);
	readFyOnI(lines);
	readFzOnI(lines);
	readTxOnI(lines);
	readTyOnI(lines);
	readTzOnI(lines);
	readMarkerKSign(lines);
}

void MbD::ASMTForceTorqueGeneral::readFxOnI(std::vector<std::string>& lines)
{
	assert(readStringNoSpacesOffTop(lines) == "FxOnI");
	aFIeKe->atput(0, popOffTop(lines));
}

void MbD::ASMTForceTorqueGeneral::readFyOnI(std::vector<std::string>& lines)
{
	assert(readStringNoSpacesOffTop(lines) == "FyOnI");
	aFIeKe->atput(1, popOffTop(lines));
}

void MbD::ASMTForceTorqueGeneral::readFzOnI(std::vector<std::string>& lines)
{
	assert(readStringNoSpacesOffTop(lines) == "FzOnI");
	aFIeKe->atput(2, popOffTop(lines));
}

void MbD::ASMTForceTorqueGeneral::readTxOnI(std::vector<std::string>& lines)
{
	assert(readStringNoSpacesOffTop(lines) == "TxOnI");
	aTIeKe->atput(0, popOffTop(lines));
}

void MbD::ASMTForceTorqueGeneral::readTyOnI(std::vector<std::string>& lines)
{
	assert(readStringNoSpacesOffTop(lines) == "TyOnI");
	aTIeKe->atput(1, popOffTop(lines));
}

void MbD::ASMTForceTorqueGeneral::readTzOnI(std::vector<std::string>& lines)
{
	assert(readStringNoSpacesOffTop(lines) == "TzOnI");
	aTIeKe->atput(2, popOffTop(lines));
}

void MbD::ASMTForceTorqueGeneral::readMarkerKSign(std::vector<std::string>& lines)
{
	assert(readStringNoSpacesOffTop(lines) == "MarkerK");
	markerKSign = readStringNoSpacesOffTop(lines);
}
