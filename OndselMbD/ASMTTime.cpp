/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <cassert>

#include "ASMTTime.h"
#include "Units.h"
#include "Time.h"
#include "Constant.h"
#include "Product.h"

using namespace MbD;

std::shared_ptr<ASMTTime> MbD::ASMTTime::With()
{
	auto inst = std::make_shared<ASMTTime>();
	inst->initialize();
	return inst;
}

void MbD::ASMTTime::deleteMbD()
{
	xx = nullptr;
	expression = nullptr;
}

void MbD::ASMTTime::createMbD()
{
	//asmtTime * asmtUnits->time = SI Units seconds
	//mbdTime * mbdUnits->time = SI Units seconds. This will be done later by mbdSys nondimensionalization
	auto& mbdTime = mbdSys()->time;	//mbdTime is in SI seconds at this point
	if (xx == mbdTime) return;
	auto timeScale = sptrConstant(1.0 / asmtUnits()->time);
	auto geoTime = std::make_shared<Product>(timeScale, mbdTime);
	xexpression(mbdTime, geoTime->simplified(geoTime));
}

Symsptr MbD::ASMTTime::expandUntil(Symsptr sptr, std::shared_ptr<std::unordered_set<Symsptr>>)
{
	return sptr;
}

Symsptr MbD::ASMTTime::simplifyUntil(Symsptr sptr, std::shared_ptr<std::unordered_set<Symsptr>>)
{
	return sptr;
}

bool MbD::ASMTTime::isVariable()
{
	return true;
}

void MbD::ASMTTime::setValue(double val)
{
	std::string str = typeid(*xx).name();
	if (str == "class MbD::Time") {
		xx->setValue(val);
	}
	else {
		//ToDo: Handle when Units time is not unity
		assert(false);
	}
}

double MbD::ASMTTime::getValue()
{
	return ExpressionX::getValue();
}

const std::string& MbD::ASMTTime::getName() const
{
	return name;
}
