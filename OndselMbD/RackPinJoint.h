/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "JointIJ.h"

namespace MbD {
	class RackPinJoint : public JointIJ
	{
		//pitchRadius aConstant 
	public:
		RackPinJoint() {}
		RackPinJoint(const char* str) : JointIJ(str) {}
		static std::shared_ptr<RackPinJoint> With();
		static std::shared_ptr<RackPinJoint> With(const char* str);

		void initializeGlobally() override;
		void connectsItoJ(EndFrmsptr frmi, EndFrmsptr frmj) override;

		double pitchRadius = 1.0, aConstant = 0.0;
	};
}

