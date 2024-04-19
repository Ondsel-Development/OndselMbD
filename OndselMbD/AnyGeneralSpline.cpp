/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

//#include <cassert>

#include "AnyGeneralSpline.h"

using namespace MbD;

MbD::AnyGeneralSpline::AnyGeneralSpline(Symsptr arg) : FunctionFromData(arg)
{
	assert(false);
}

std::shared_ptr<AnyGeneralSpline> MbD::AnyGeneralSpline::With()
{
	auto inst = std::make_shared<AnyGeneralSpline>();
	inst->initialize();
	return inst;
}
