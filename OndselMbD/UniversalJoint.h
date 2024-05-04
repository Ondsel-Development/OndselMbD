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
	class UniversalJoint : public AtPointJoint
	{
		//
	public:
		UniversalJoint() {}
		UniversalJoint(const char* str) : AtPointJoint(str) {}
		static std::shared_ptr<UniversalJoint> With();
		static std::shared_ptr<UniversalJoint> With(const char* str);

		void initializeGlobally() override;

	};
}

