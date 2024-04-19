/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <cassert>

#include "Reciprocal.h"
#include "Negative.h"
#include "Power.h"
#include "Constant.h"
#include "Ln.h"

using namespace MbD;

MbD::Reciprocal::Reciprocal(Symsptr arg) : FunctionX(arg)
{
	assert(false);
}

std::shared_ptr<Reciprocal> MbD::Reciprocal::With()
{
	auto inst = std::make_shared<Reciprocal>();
	inst->initialize();
	return inst;
}

double MbD::Reciprocal::getValue()
{
	return 1.0 / xx->getValue();
}

Symsptr MbD::Reciprocal::differentiateWRTx()
{
	auto two = sptrConstant(2);
	auto sq = std::make_shared<Power>(xx, two);
	return std::make_shared<Negative>(sq);
}

Symsptr MbD::Reciprocal::integrateWRTx()
{
	return std::make_shared<Ln>(xx);
}

Symsptr MbD::Reciprocal::copyWith(Symsptr arg)
{
	return std::make_shared<Reciprocal>(arg);
}

std::ostream& MbD::Reciprocal::printOn(std::ostream& s) const
{
	s << "/(" << *xx << ")";
	return s;
}
