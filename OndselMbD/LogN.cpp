/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <cassert>

#include "LogN.h"

using namespace MbD;

MbD::LogN::LogN(Symsptr arg) : FunctionX(arg)
{
	assert(false);
}

std::shared_ptr<LogN> MbD::LogN::With()
{
	auto inst = std::make_shared<LogN>();
	inst->initialize();
	return inst;
}

std::shared_ptr<LogN> MbD::LogN::With(Symsptr arg)
{
	auto inst = std::make_shared<LogN>(arg);
	inst->initialize();
	return inst;
}

double MbD::LogN::getValue()
{
	return std::log(xx->getValue());
}

Symsptr MbD::LogN::copyWith(Symsptr arg)
{
	return LogN::With(arg);
}

std::ostream& MbD::LogN::printOn(std::ostream& s) const
{
	s << "ln(" << *xx << ")";
	return s;
}
