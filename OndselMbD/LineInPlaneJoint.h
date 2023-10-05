/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselMbD.                                       *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "InPlaneJoint.h"

namespace MbD {
	class LineInPlaneJoint : public InPlaneJoint
	{
		//
	public:
		LineInPlaneJoint();
		LineInPlaneJoint(const char* str);
		void initializeGlobally() override;

	};
}

