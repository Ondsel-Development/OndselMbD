/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <cassert>

#include "Cosine.h"
#include "Sine.h"
#include "Negative.h"

using namespace MbD;

std::shared_ptr<Cosine> MbD::Cosine::With()
{
	auto inst = std::make_shared<Cosine>();
	inst->initialize();
	return inst;
}

std::shared_ptr<Cosine> MbD::Cosine::With(Symsptr arg)
{
	auto inst = std::make_shared<Cosine>(arg);
	inst->initialize();
	return inst;
}

double MbD::Cosine::getValue()
{
	return std::cos(xx->getValue());
}

Symsptr MbD::Cosine::differentiateWRTx()
{
	return Negative::With(std::make_shared<Sine>(xx));
}

Symsptr MbD::Cosine::copyWith(Symsptr arg)
{
	return Cosine::With(arg);
}

Symsptr MbD::Cosine::clonesptr()
{
	return std::make_shared<Cosine>(*this);
}

Symsptr MbD::Cosine::integrateWRTx()
{
	auto sine = std::make_shared<Sine>(xx);
	return Negative::With(sine);

}

std::ostream& MbD::Cosine::printOn(std::ostream& s) const
{
	s << "cos(" << *xx << ")";
	return s;
}
