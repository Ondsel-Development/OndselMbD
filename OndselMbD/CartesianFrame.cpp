/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "CartesianFrame.h"

using namespace MbD;

CartesianFrame::CartesianFrame(const char* str) : Item(str)
{
	//Do nothing.
}

std::shared_ptr<CartesianFrame> MbD::CartesianFrame::With(const char* str)
{
	auto inst = std::make_shared<CartesianFrame>(str);
	inst->initialize();
	return inst;
}

void CartesianFrame::initialize()
{
	assert(false);
}
