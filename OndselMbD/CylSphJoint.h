/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
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
		CylSphJoint() {}
		CylSphJoint(const char* str);
		static std::shared_ptr<CylSphJoint> With();
		static std::shared_ptr<CylSphJoint> With(const char* str);
		
		void initializeGlobally() override;


	};
}
