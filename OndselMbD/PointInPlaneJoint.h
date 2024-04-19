/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "InPlaneJoint.h"

namespace MbD {
	class PointInPlaneJoint : public InPlaneJoint
	{
		//
	public:
		PointInPlaneJoint() {}
		PointInPlaneJoint(const char* str);
		static std::shared_ptr<PointInPlaneJoint> With();
		static std::shared_ptr<PointInPlaneJoint> With(const char* str);

		void initializeGlobally() override;

	};
}

