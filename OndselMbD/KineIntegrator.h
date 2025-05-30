/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "QuasiIntegrator.h"

namespace MbD {
	class KineIntegrator : public QuasiIntegrator
	{
		//
	public:
		static std::shared_ptr<KineIntegrator> With();
		
		void preRun() override;
		void firstStep() override;
		void subsequentSteps() override;
		void nextStep() override;
		void runInitialConditionTypeSolution() override;
		void iStep(size_t i) override;
		void selectOrder() override;
		void useTrialStepStats(std::shared_ptr<SolverStatistics> stats);
	};
}

