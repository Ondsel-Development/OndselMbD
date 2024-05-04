/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "ASMTAngleIJ.h"

namespace MbD {
	class ASMTAngleIJz : public ASMTAngleIJ
	{
		//
	public:
		static std::shared_ptr<ASMTAngleIJz> With();
		std::shared_ptr<KinematicIJ> mbdClassNew() override;

	};
}