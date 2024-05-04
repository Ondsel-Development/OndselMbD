/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "ASMTJoint.h"

namespace MbD {
	class ASMTScrewJoint : public ASMTJoint
	{
		//
	public:
		static std::shared_ptr<ASMTScrewJoint> With();

		std::shared_ptr<JointIJ> mbdClassNew() override;
		void parseASMT(std::vector<std::string>& lines) override;
		void readPitch(std::vector<std::string>& lines);
		void createMbD() override;
		void storeOnLevel(std::ofstream& os, size_t level) override;

		double pitch = 0.0, aConstant = 0.0;
	};
}
