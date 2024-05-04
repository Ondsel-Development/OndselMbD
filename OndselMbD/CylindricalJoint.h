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
	class CylindricalJoint : public InLineJoint
	{
		//efrmI efrmJ constraints friction 
	public:
		CylindricalJoint() {}
		CylindricalJoint(const char* str) : InLineJoint(str) {}
		static std::shared_ptr<CylindricalJoint> With();
		static std::shared_ptr<CylindricalJoint> With(const char* str);
		
		void initializeGlobally() override;
	};
}

