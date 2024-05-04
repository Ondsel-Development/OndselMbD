/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <cassert>

#include "Ln.h"

using namespace MbD;

MbD::Ln::Ln(Symsptr arg) : FunctionX(arg)
{
	assert(false);
}

std::shared_ptr<Ln> MbD::Ln::With()
{
	auto inst = std::make_shared<Ln>();
	inst->initialize();
	return inst;
}

std::shared_ptr<Ln> MbD::Ln::With(Symsptr arg)
{
	auto inst = std::make_shared<Ln>(arg);
	inst->initialize();
	return inst;
}

double MbD::Ln::getValue()
{
	return std::log(xx->getValue());
}

Symsptr MbD::Ln::copyWith(Symsptr arg)
{
	return Ln::With(arg);
}
