/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselMbD.                                       *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "InLineJoint.h"

namespace MbD {
	class PointInLineJoint : public InLineJoint
	{
		//
	public:
		PointInLineJoint();
		PointInLineJoint(const char* str);
		void initializeGlobally() override;

	};
}
