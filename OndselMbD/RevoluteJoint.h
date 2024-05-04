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
	class RevoluteJoint : public AtPointJoint
	{
		//
	public:
		RevoluteJoint() {}
		RevoluteJoint(const char* str) : AtPointJoint(str) {}
		static std::shared_ptr<RevoluteJoint> With();
		static std::shared_ptr<RevoluteJoint> With(const char* str);

		void initializeGlobally() override;
	};
}

