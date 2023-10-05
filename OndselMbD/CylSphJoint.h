/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselMbD.                                       *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "CompoundJoint.h"

namespace MbD {
	class CylSphJoint : public CompoundJoint
	{
		//
	public:
		CylSphJoint();
		CylSphJoint(const char* str);
		void initializeGlobally() override;


	};
}