/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "Constant.h"
#include "System.h"
#include "Units.h"
#include "Polynomial.h"
#include "Integral.h"

using namespace MbD;

std::shared_ptr<Constant> MbD::Constant::With(double arg)
{
	return std::make_shared<Constant>(arg);
}

Symsptr MbD::Constant::differentiateWRT(Symsptr)
{
	return sptrConstant(0.0);
}

Symsptr MbD::Constant::integrateWRT(Symsptr var)
{
	auto simple = simplified();
	auto answer = std::make_shared<Integral>();
	answer->xx = var;
	answer->integrand = simple;
	if (value == 0.0) answer->expression = clonesptr();
	auto slope = sptrConstant(value);
	auto intercept = sptrConstant(0.0);
	auto coeffs = std::make_shared<std::vector<Symsptr>>();
	coeffs->push_back(intercept);
	coeffs->push_back(slope);
	answer->expression = std::make_shared<Polynomial>(var, coeffs);
	return answer;
}

Symsptr MbD::Constant::expandUntil(Symsptr sptr, std::shared_ptr<std::unordered_set<Symsptr>>)
{
	return sptr;
}

bool Constant::isConstant()
{
	return true;
}

Symsptr MbD::Constant::clonesptr()
{
	return std::make_shared<Constant>(*this);
}

bool MbD::Constant::isZero()
{
	return value == 0.0;
}

bool MbD::Constant::isOne()
{
	return value == 1.0;
}

void MbD::Constant::createMbD()
{
	return;
}

double MbD::Constant::getValue()
{
	return value;
}

std::ostream& Constant::printOn(std::ostream& s) const
{
	return s << value;
}
