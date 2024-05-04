/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "NewtonRaphsonError.h"

namespace MbD {
	class MaximumIterationError : virtual public std::runtime_error
	{

	public:
		explicit MaximumIterationError(const std::string& msg) : std::runtime_error(msg) {}
	};
}

