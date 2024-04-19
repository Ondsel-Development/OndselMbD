/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <cassert>

#include <cassert>

#include "SyntaxError.h"

using namespace MbD;

SyntaxError::SyntaxError(const std::string& msg) : std::runtime_error(msg)
{
	assert(false);
}
