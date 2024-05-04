/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <cassert>

#include "Time.h"

using namespace MbD;

Time::Time()
{
	std::string str = "t";
	setName(str);
}

std::shared_ptr<Time> MbD::Time::With()
{
	auto inst = std::make_shared<Time>();
	inst->initialize();
	return inst;
}

void Time::initialize()
{
	assert(false);
}
