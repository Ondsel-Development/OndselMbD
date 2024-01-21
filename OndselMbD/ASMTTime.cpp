/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <cassert>

#include "ASMTTime.h"
#include "Time.h"
#include "Constant.h"
#include "Product.h"

using namespace MbD;

void MbD::ASMTTime::deleteMbD()
{
	xx = nullptr;
	expression = nullptr;
}

void MbD::ASMTTime::createMbD(std::shared_ptr<System> mbdSys, std::shared_ptr<Units> mbdUnits)
{
	auto& mbdTime = mbdSys->time;
	if (xx == mbdTime) return;
	auto timeScale = sptrConstant(mbdUnits->time);
	auto geoTime = std::make_shared<Product>(timeScale, mbdTime);
	this->xexpression(mbdTime, geoTime->simplified(geoTime));
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
