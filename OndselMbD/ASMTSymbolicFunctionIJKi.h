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
	class ASMTSymbolicFunctionIJKi : public ASMTSymbolicFunctionIJ
	{
		//
	public:
		static std::shared_ptr<ASMTSymbolicFunctionIJKi> With();

		std::string markerK;
		size_t axisK;
	};
}

