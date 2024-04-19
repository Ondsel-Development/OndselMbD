/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <cassert>

#include "Negative.h"
#include "Constant.h"

using namespace MbD;

std::shared_ptr<Negative> MbD::Negative::With(Symsptr arg)
{
	auto sym = std::make_shared<Negative>(arg);
	sym->initialize();
	return sym;
}

double MbD::Negative::getValue()
{
	return -xx->getValue();
}

Symsptr MbD::Negative::differentiateWRTx()
{
	return sptrConstant(-1);
}

Symsptr MbD::Negative::integrateWRTx()
{
	return std::make_shared<Negative>(xx);
}

Symsptr MbD::Negative::expandUntil(Symsptr, std::shared_ptr<std::unordered_set<Symsptr>> set)
{
	auto expand = xx->expandUntil(xx, set);
	return std::make_shared<Negative>(expand);
}

Symsptr MbD::Negative::simplifyUntil(Symsptr, std::shared_ptr<std::unordered_set<Symsptr>> set)
{
	auto simple = xx->simplifyUntil(xx, set);
	if (simple->isConstant()) {
		return sptrConstant(-simple->getValue());
	}
	return std::make_shared<Negative>(simple);
}

Symsptr MbD::Negative::copyWith(Symsptr arg)
{
	return std::make_shared<Negative>(arg);
}

Symsptr MbD::Negative::clonesptr()
{
	return std::make_shared<Negative>(*this);
}

std::ostream& MbD::Negative::printOn(std::ostream& s) const
{
	s << "-(" << *xx << ")";
	return s;
}
