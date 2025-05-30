/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "FunctionXY.h"

namespace MbD {
	class ArcTan2 : public FunctionXY
	{
		//
	public:
		ArcTan2() = default;
		ArcTan2(Symsptr arg, Symsptr arg1);
		static std::shared_ptr<ArcTan2> With();
		
		double getValue() override;
		Symsptr differentiateWRTx() override;
		Symsptr differentiateWRTy() override;


	};
}

