/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "ASMTSymbolicFunctionIJ.h"

namespace MbD {
	class ASMTAngleIJ : public ASMTSymbolicFunctionIJ
	{
		//
	public:
		static std::shared_ptr<ASMTAngleIJ> With();
		double asmtUnit() override;

	};
}

