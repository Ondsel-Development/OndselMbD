/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselMbD.                                       *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include <vector>

#include "IntegratorInterface.h"
#include "enum.h"

namespace MbD {
    class QuasiIntegrator : public IntegratorInterface
    {
        //
    public:
        void preFirstStep() override;
        void preRun() override;
        void initialize() override;
        void run() override;
        void preStep() override;
        void checkForDiscontinuity() override;
        double suggestSmallerOrAcceptFirstStepSize(double hnew) override;
        double suggestSmallerOrAcceptStepSize(double hnew) override;
        void incrementTime(double tnew) override;
        void throwDiscontinuityError(const char* chars, std::shared_ptr<std::vector<DiscontinuityType>> discontinuityTypes);
        void checkForOutputThrough(double t) override;
        void interpolateAt(double t) override;
        void postRun() override;

    };
}

