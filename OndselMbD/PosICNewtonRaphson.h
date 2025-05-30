/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "AnyPosICNewtonRaphson.h"

namespace MbD {
	class PosICNewtonRaphson : public AnyPosICNewtonRaphson
	{
	  //IC with over, fully or under constrained system
	  //Perform redundant constraint removal for over constrained system
	  //pivotRowLimits
	public:
		PosICNewtonRaphson(){}
		static std::shared_ptr<PosICNewtonRaphson> With();

		void run() override;
		void iterate() override;
		void preRun() override;
		void assignEquationNumbers() override;
		bool isConverged() override;
		void handleSingularMatrix() override;
		void lookForRedundantConstraints();

		std::shared_ptr<std::vector<size_t>> pivotRowLimits;
	};
}

