/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <cassert>

#include <cassert>

#include "FunctionFromData.h"

using namespace MbD;

MbD::FunctionFromData::FunctionFromData(Symsptr arg) : FunctionXcParameter(arg)
{
	assert(false);
}

std::shared_ptr<FunctionFromData> MbD::FunctionFromData::With()
{
	auto inst = std::make_shared<FunctionFromData>();
	inst->initialize();
	return inst;
}
