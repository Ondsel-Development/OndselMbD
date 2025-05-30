/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once
#include "MBDynItem.h"

namespace MbD {
	class MBDynElement : public MBDynItem
	{
	public:
		static std::shared_ptr<MBDynElement> With();
		void initialize() override;

		void parseMBDyn(std::vector<std::string>& lines) override;

	};
}
