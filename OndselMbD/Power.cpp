/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "Power.h"
#include "Constant.h"
#include "Ln.h"
#include <cassert>

using namespace MbD;

MbD::Power::Power(Symsptr bse, Symsptr ex) : FunctionXY(bse, ex)
{
	assert(false);
}

std::shared_ptr<Power> MbD::Power::With()
{
	auto inst = std::make_shared<Power>();
	inst->initialize();
	return inst;
}

Symsptr MbD::Power::differentiateWRTx()
{
	auto yminus1 = Symbolic::sum(y, sptrConstant(-1.0));
	auto power = Symbolic::raisedTo(x, yminus1);
	auto deriv = Symbolic::times(y, power);
	return deriv->simplified(deriv);
}

Symsptr MbD::Power::differentiateWRTy()
{
	auto lnterm = std::make_shared<Ln>(x);
	auto deriv = Symbolic::times(clonesptr(), lnterm);
	return deriv->simplified();
}

Symsptr MbD::Power::simplifyUntil(Symsptr, std::shared_ptr<std::unordered_set<Symsptr>>)
{
	assert(false);
	return Symsptr();
}

double MbD::Power::getValue()
{
	return std::pow(x->getValue(), y->getValue());
}
