/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "ForTorAction.h"

namespace MbD {
	class ForTorActionComp : public ForTorAction
	{
		//
	public:
		static std::shared_ptr<ForTorActionComp> With();

		size_t axis;
	};
}
