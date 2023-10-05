/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselMbD.                                       *
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
        void firstStep() override;
        bool isRedoingFirstStep();
        void nextStep();
        //void reportStepStats();
        //void reportTrialStepStats();
        void runInitialConditionTypeSolution() override;
        void selectFirstStepSize();
        void selectStepSize();
        void postFirstStep();
        void postStep();
    
    };
}

