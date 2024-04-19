/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <cassert>

#include "FunctionXcParameter.h"

using namespace MbD;

MbD::FunctionXcParameter::FunctionXcParameter(Symsptr arg) : FunctionX(arg)
{
	assert(false);
}

std::shared_ptr<FunctionXcParameter> MbD::FunctionXcParameter::With()
{
	auto inst = std::make_shared<FunctionXcParameter>();
	inst->initialize();
	return inst;
}
