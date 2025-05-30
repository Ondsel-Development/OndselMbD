/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once
#include "MBDynStructural.h"

namespace MbD {
	class MBDynStructuralDynamic : public MBDynStructural
	{
	public:
		MBDynStructuralDynamic() {}
		static std::shared_ptr<MBDynStructuralDynamic> With();

		void parseMBDyn(std::string line) override;

	};
};
