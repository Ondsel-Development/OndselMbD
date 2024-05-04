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
	class ASMTOmegaIJ : public ASMTSymbolicFunctionIJ
	{
		//
	public:
		static std::shared_ptr<ASMTOmegaIJ> With();
		std::shared_ptr<KinematicIJ> mbdClassNew() override;
		void createMbD() override;
		double asmtUnit() override;

	};
}
