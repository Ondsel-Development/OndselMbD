/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselMbD.                                       *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "BasicDAEIntegrator.h"
#include "StableStartingBDF.h"

namespace MbD {
    class StartingBasicDAEIntegrator : public BasicDAEIntegrator
    {
        //
    public:
        void initialize() override;
        void initializeLocally() override;
        FColDsptr yDerivat(int order, double tout) override;
        std::shared_ptr<LinearMultiStepMethod> correctorBDF() override;
        void calcOperatorMatrix() override;
        void setorder(int o) override;
        void settime(double t) override;
        void iStep(int i) override;
        FColDsptr yDeriv(int order);
        FColDsptr dyOrderPlusOnedt() override;
        void run() override;
        void firstSteps();
        void earlySteps();

        std::shared_ptr<StableStartingBDF> startingBDF;
    };
}
