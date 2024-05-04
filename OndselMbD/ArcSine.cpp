/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

 //#include <cassert>

#include "ArcSine.h"

using namespace MbD;

MbD::ArcSine::ArcSine(Symsptr arg) : FunctionX(arg)
{
	assert(false);
}

std::shared_ptr<ArcSine> MbD::ArcSine::With()
{
	auto inst = std::make_shared<ArcSine>();
	inst->initialize();
	return inst;
}

std::shared_ptr<ArcSine> MbD::ArcSine::With(Symsptr arg)
{
	auto inst = std::make_shared<ArcSine>(arg);
	inst->initialize();
	return inst;
}

double MbD::ArcSine::getValue()
{
	return std::asin(xx->getValue());
}

Symsptr MbD::ArcSine::copyWith(Symsptr arg)
{
	return ArcSine::With(arg);
}

std::ostream& MbD::ArcSine::printOn(std::ostream& s) const
{
	s << "arcsin(" << *xx << ")";
	return s;
}
