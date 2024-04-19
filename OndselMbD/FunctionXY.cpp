/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "FunctionXY.h"
#include "Sum.h"

using namespace MbD;

MbD::FunctionXY::FunctionXY(Symsptr base, Symsptr exp) : x(base), y(exp)
{
	assert(false);
}

void MbD::FunctionXY::arguments(Symsptr args)
{
	//args is a Sum with "terms" containing the actual arguments
	auto sum = std::static_pointer_cast<Sum>(args);
	assert(sum->terms->size() == 2);
	x = sum->terms->at(0);
	y = sum->terms->at(1);
}

bool MbD::FunctionXY::isConstant()
{
	return x->isConstant() && y->isConstant();
}

Symsptr MbD::FunctionXY::differentiateWRTx()
{
	//Subclasses must implement.
	assert(false);
	return Symsptr();
}

Symsptr MbD::FunctionXY::differentiateWRTy()
{
	//Subclasses must implement.
	assert(false);
	return Symsptr();
}
