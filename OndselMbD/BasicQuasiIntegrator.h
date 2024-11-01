/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "BasicIntegrator.h"

namespace MbD {
	class BasicQuasiIntegrator : public BasicIntegrator
	{
		//
	public:
		static std::shared_ptr<BasicQuasiIntegrator> With();
		
		void firstStep() override;
		bool isRedoingFirstStep();
		void nextStep() override;
		void reportStepStats();
		void reportTrialStepStats();
		void runInitialConditionTypeSolution() override;
		void selectFirstStepSize();
		void selectStepSize() override;
		void postFirstStep();
		void postStep();
	
	};
}

