/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselMbD.                                       *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include <stdexcept>
#include <memory>
#include <vector>

namespace MbD {
	class NotKinematicError : virtual public std::runtime_error
	{

	public:
		//NotKinematicError();
		explicit NotKinematicError(const std::string& msg);
		virtual ~NotKinematicError() noexcept {}
	};
}
