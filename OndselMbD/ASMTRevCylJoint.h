/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "ASMTCompoundJoint.h"

namespace MbD {
	class ASMTRevCylJoint : public ASMTCompoundJoint
	{
		//
	public:
		static std::shared_ptr<ASMTRevCylJoint> With();

		std::shared_ptr<JointIJ> mbdClassNew() override;

	};
}
