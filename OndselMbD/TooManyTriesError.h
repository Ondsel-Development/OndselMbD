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
	class TooManyTriesError : virtual public std::runtime_error
	{

	public:
		explicit TooManyTriesError(const std::string& msg) : std::runtime_error(msg) {}
	};
}
