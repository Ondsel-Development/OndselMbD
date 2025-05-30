/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "AtPointJoint.h"

namespace MbD {
	class FixedJoint : public AtPointJoint
	{
		//
	public:
		FixedJoint() {}
		FixedJoint(const char* str) : AtPointJoint(str) {}
		static std::shared_ptr<FixedJoint> With();
		static std::shared_ptr<FixedJoint> With(const char* str);
		
		void initializeGlobally() override;


	};
}
