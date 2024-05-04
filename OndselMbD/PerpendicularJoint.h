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
	class PerpendicularJoint : public JointIJ
	{
		//
	public:
		PerpendicularJoint() {}
		PerpendicularJoint(const char* str) : JointIJ(str) {}
		static std::shared_ptr<PerpendicularJoint> With();
		static std::shared_ptr<PerpendicularJoint> With(const char* str);

		void initializeGlobally() override;

	};
}

