/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "ASMTForceTorque.h"
#include "ASMTAssembly.h"
#include "ForceFunctionParser.h"
#include "ForceTorqueItem.h"

using namespace MbD;

std::shared_ptr<ASMTForceTorque> MbD::ASMTForceTorque::With()
{
	auto inst = std::make_shared<ASMTForceTorque>();
	inst->initialize();
	return inst;
}

void MbD::ASMTForceTorque::updateFromMbD()
{
	//"
	//MbD returns aFIeO and aTIeO.
	//GEO needs aFImO and aTImO.
	//For Motion rImIeO is not zero and is changing.
	//aFImO = aFIeO.
	//aTImO = aTIeO + (rImIeO cross : aFIeO).
	//"
	auto mbdUnts = mbdUnits();
	auto forTor = std::static_pointer_cast<ForceTorqueItem>(mbdObject);
	auto aFIeO = forTor->aFX()->times(mbdUnts->force);
	auto aTIeO = forTor->aTX()->times(mbdUnts->torque);
	auto rImIeO = forTor->frmI->rmeO()->times(mbdUnts->length);
	auto aFIO = aFIeO;
	auto aTIO = aTIeO->plusFullColumn(rImIeO->cross(aFIeO));
	cFIO->push_back(aFIO);
	cTIO->push_back(aTIO);
}

void MbD::ASMTForceTorque::compareResults(AnalysisType)
{
	if (infxs == nullptr || infxs->empty()) return;
	auto mbdUnts = mbdUnits();
	//auto factor = 1.0e-6;
	//auto forceTol = mbdUnts->force * factor;
	//auto torqueTol = mbdUnts->torque * factor;
	//auto i = fxs->size() - 1;
	//assert(Numeric::equaltol(fxs->at(i), infxs->at(i), forceTol));
	//assert(Numeric::equaltol(fys->at(i), infys->at(i), forceTol));
	//assert(Numeric::equaltol(fzs->at(i), infzs->at(i), forceTol));
	//assert(Numeric::equaltol(txs->at(i), intxs->at(i), torqueTol));
	//assert(Numeric::equaltol(tys->at(i), intys->at(i), torqueTol));
	//assert(Numeric::equaltol(tzs->at(i), intzs->at(i), torqueTol));
}

void MbD::ASMTForceTorque::outputResults(AnalysisType)
{
	assert(false);
}

void MbD::ASMTForceTorque::readForceTorqueSeries(std::vector<std::string>& lines)
{
	std::string str = lines[0];
	std::string substr = "ForceTorqueSeries";
	auto pos = str.find(substr);
	assert(pos != std::string::npos);
	str.erase(0, pos + substr.length());
	auto seriesName = readString(str);
	assert(fullName("") == seriesName);
	lines.erase(lines.begin());
	readFXonIs(lines);
	readFYonIs(lines);
	readFZonIs(lines);
	readTXonIs(lines);
	readTYonIs(lines);
	readTZonIs(lines);
}

void MbD::ASMTForceTorque::createMbD(std::shared_ptr<System> mbdSys, std::shared_ptr<Units> mbdUnits)
{
	//self dataSeries : OrderedCollection new.
	//self discontinuities : OrderedCollection new
}

std::shared_ptr<ForceFunctionParser> MbD::ASMTForceTorque::functionParser()
{
	auto parser = std::make_shared<ForceFunctionParser>();
	parser->container = this;
	parser->initVariables();
	parser->initgeoIJs();
	return parser;

}
