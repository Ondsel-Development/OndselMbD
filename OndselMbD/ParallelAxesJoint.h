/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselMbD.                                       *
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
		ParallelAxesJoint();
		ParallelAxesJoint(const char* str);
		void initializeGlobally() override;

	};
}

