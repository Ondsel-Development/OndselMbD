/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <cassert>

#include "NewtonRaphsonError.h"

using namespace MbD;

NewtonRaphsonError::NewtonRaphsonError(const std::string& msg) : std::runtime_error(msg)
{
	assert(false);
}
