/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "CADSymbolicFunction.h"

namespace MbD {
	class ASMTSymbolicFunction : public CADSymbolicFunction
	{
		//
	public:
		static std::shared_ptr<ASMTSymbolicFunction> With();

	};
}

