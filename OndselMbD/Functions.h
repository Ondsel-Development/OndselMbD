/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "Arguments.h"

namespace MbD {
	class Functions : public Arguments
	{
	public:
		static std::shared_ptr<Functions> With();

	};
}
