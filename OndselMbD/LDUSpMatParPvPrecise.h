/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "LDUSpMatParPv.h"

namespace MbD {
	class LDUSpMatParPvPrecise : public LDUSpMatParPv
	{
		//
	public:
		static std::shared_ptr<LDUSpMatParPvPrecise> With();
		
		void doPivoting(size_t p) override;

	};
}

