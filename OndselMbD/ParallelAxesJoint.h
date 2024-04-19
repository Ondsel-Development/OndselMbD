/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "Joint.h"

namespace MbD {
	class ParallelAxesJoint : public Joint
	{
		//
	public:
		ParallelAxesJoint() {}
		ParallelAxesJoint(const char* str);
		static std::shared_ptr<ParallelAxesJoint> With();
		static std::shared_ptr<ParallelAxesJoint> With(const char* str);

		void initializeGlobally() override;

	};
}

