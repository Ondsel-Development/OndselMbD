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

std::shared_ptr<Sine> MbD::Sine::With()
{
	auto inst = std::make_shared<Sine>();
	inst->initialize();
	return inst;
}

std::shared_ptr<Sine> MbD::Sine::With(Symsptr arg)
{
	auto inst = std::make_shared<Sine>(arg);
	inst->initialize();
	return inst;
}

double MbD::Sine::getValue()
{
	return std::sin(xx->getValue());
}

Symsptr MbD::Sine::differentiateWRTx()
{
	return Cosine::With(xx);
}

Symsptr MbD::Sine::copyWith(Symsptr arg)
{
	return Sine::With(arg);
}

Symsptr MbD::Sine::clonesptr()
{
	return std::make_shared<Sine>(*this);
}

Symsptr MbD::Sine::integrateWRTx()
{
	return Cosine::With(xx);
}

std::ostream& MbD::Sine::printOn(std::ostream& s) const
{
	s << "sin(" << *xx << ")";
	return s;
}
