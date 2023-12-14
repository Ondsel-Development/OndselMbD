/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "ForceTorqueItem.h"

namespace MbD {
    class ConstantGravity : public ForceTorqueItem
    {
        //
    public:
        void fillAccICIterError(FColDsptr col) override;
        void fillDynError(FColDsptr col) override;
        void postDynPredictor() override;
        void fillpFpy(SpMatDsptr mat) override;
        void fillpFpydot(SpMatDsptr mat) override;
        void postDynCorrectorIteration() override;
        void preDynOutput() override;
		void postDynOutput() override;

        FColDsptr gXYZ;
    };
}

