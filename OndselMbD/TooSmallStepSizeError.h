/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include <stdexcept>

namespace MbD {
	class TooSmallStepSizeError : virtual public std::runtime_error
	{

	public:
		explicit TooSmallStepSizeError(const std::string& msg);
	};
}
