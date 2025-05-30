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
	class PointInLineJoint : public InLineJoint
	{
		//
	public:
		PointInLineJoint() {}
		PointInLineJoint(const char* str) : InLineJoint(str) {}
		static std::shared_ptr<PointInLineJoint> With();
		static std::shared_ptr<PointInLineJoint> With(const char* str);

		void initializeGlobally() override;

	};
}

