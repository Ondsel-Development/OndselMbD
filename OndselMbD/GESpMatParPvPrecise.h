/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "GESpMatParPv.h"

namespace MbD {
	class GESpMatParPvPrecise : public GESpMatParPv
	{
		//
	public:
		static std::shared_ptr<GESpMatParPvPrecise> With();
		
		void doPivoting(size_t p) override;
		void preSolvewithsaveOriginal(SpMatDsptr spMat, FColDsptr fullCol, bool saveOriginal) override;

	};
}

