/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "InLineJoint.h"

namespace MbD {
	class TranslationalJoint : public InLineJoint
	{
		//
	public:
		TranslationalJoint() {}
		TranslationalJoint(const char* str) : InLineJoint(str) {}
		static std::shared_ptr<TranslationalJoint> With();
		static std::shared_ptr<TranslationalJoint> With(const char* str);

		void initializeGlobally() override;

	};
}

