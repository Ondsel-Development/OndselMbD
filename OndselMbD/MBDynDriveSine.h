/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once
#include "MBDynDrive.h"

namespace MbD {
	class MBDynDriveSine : public MBDynDrive
	{
	public:
		static std::shared_ptr<MBDynDriveSine> With();

		void readFunction(std::vector<std::string>& args) override;
		void createASMT() override;

	};
}

