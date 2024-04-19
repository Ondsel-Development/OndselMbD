/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

//#include <cassert>

#include "ArcTan2.h"

using namespace MbD;

MbD::ArcTan2::ArcTan2(Symsptr arg, Symsptr arg1) : FunctionXY(arg, arg1)
{
	assert(false);
}

std::shared_ptr<ArcTan2> MbD::ArcTan2::With()
{
	auto inst = std::make_shared<ArcTan2>();
	inst->initialize();
	return inst;
}

double MbD::ArcTan2::getValue()
{
	return std::atan2(y->getValue(), x->getValue());
}

Symsptr MbD::ArcTan2::differentiateWRTx()
{
	return Symsptr();
}

Symsptr MbD::ArcTan2::differentiateWRTy()
{
	return Symsptr();
}
