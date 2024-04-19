/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <cassert>

#include "Sine.h"
#include "Cosine.h"

using namespace MbD;

MbD::Sine::Sine(Symsptr arg) : FunctionX(arg)
{
	assert(false);
}

std::shared_ptr<Sine> MbD::Sine::With()
{
	auto inst = std::make_shared<Sine>();
	inst->initialize();
	return inst;
}

double MbD::Sine::getValue()
{
	return std::sin(xx->getValue());
}

Symsptr MbD::Sine::differentiateWRTx()
{
	return std::make_shared<Cosine>(xx);
}

Symsptr MbD::Sine::copyWith(Symsptr arg)
{
	return std::make_shared<Sine>(arg);
}

Symsptr MbD::Sine::clonesptr()
{
	return std::make_shared<Sine>(*this);
}

Symsptr MbD::Sine::integrateWRTx()
{
	return std::make_shared<Cosine>(xx);
}

std::ostream& MbD::Sine::printOn(std::ostream& s) const
{
	s << "sin(" << *xx << ")";
	return s;
}
