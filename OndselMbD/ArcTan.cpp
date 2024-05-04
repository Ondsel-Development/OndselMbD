/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

//#include <cassert>

#include "ArcTan.h"

using namespace MbD;

MbD::ArcTan::ArcTan(Symsptr arg) : FunctionX(arg)
{
	assert(false);
}

std::shared_ptr<ArcTan> MbD::ArcTan::With()
{
	auto inst = std::make_shared<ArcTan>();
	inst->initialize();
	return inst;
}

std::shared_ptr<ArcTan> MbD::ArcTan::With(Symsptr arg)
{
	auto inst = std::make_shared<ArcTan>(arg);
	inst->initialize();
	return inst;
}

double MbD::ArcTan::getValue()
{
	return std::atan(xx->getValue());
}

Symsptr MbD::ArcTan::copyWith(Symsptr arg)
{
	return ArcTan::With(arg);
}

std::ostream& MbD::ArcTan::printOn(std::ostream& s) const
{
	s << "arctan(" << *xx << ")";
	return s;
}
