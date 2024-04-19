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
	class MBDynStructuralDummy : public MBDynStructural
	{
	public:
		MBDynStructuralDummy() {}
		static std::shared_ptr<MBDynStructuralDummy> With();

		void parseMBDyn(std::string line) override;
		void readPosition(std::vector<std::string>& args) override;
		void readOrientation(std::vector<std::string>& args) override;

	};
};

