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
	class ConstantVelocityJoint : public AtPointJoint
	{
		//
	public:
		ConstantVelocityJoint() {}
		ConstantVelocityJoint(const char* str) : AtPointJoint(str) {}
		static std::shared_ptr<ConstantVelocityJoint> With();
		static std::shared_ptr<ConstantVelocityJoint> With(const char* str);
		
		void initializeGlobally() override;
		void connectsItoJ(EndFrmsptr frmi, EndFrmsptr frmj) override;


	};
}

