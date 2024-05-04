/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <cassert>

#include "Exponential.h"

using namespace MbD;

MbD::Exponential::Exponential(Symsptr arg) : FunctionX(arg)
{
	assert(false);
}

std::shared_ptr<Exponential> MbD::Exponential::With()
{
	auto inst = std::make_shared<Exponential>();
	inst->initialize();
	return inst;
}

std::shared_ptr<Exponential> MbD::Exponential::With(Symsptr arg)
{
	auto inst = std::make_shared<Exponential>(arg);
	inst->initialize();
	return inst;
}

double MbD::Exponential::getValue()
{
	return std::log(xx->getValue());
}

Symsptr MbD::Exponential::copyWith(Symsptr arg)
{
	return Exponential::With(arg);
}

std::ostream& MbD::Exponential::printOn(std::ostream& s) const
{
	s << "exp(" << *xx << ")";
	return s;
}
