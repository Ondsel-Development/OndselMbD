/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include <vector>

#include "IntegratorInterface.h"
#include "enum.h"
#include "FullColumn.h"

namespace MbD {
    class DAEIntegrator : public IntegratorInterface
    {
        //neqn ncon 
    public:
        void initializeGlobally() override;
        void preFirstStep() override;
        void checkForOutputThrough(double t) override;
        void preRun() override;
        void initialize() override;
        void preStep() override;
        double suggestSmallerOrAcceptStepSize(double hnew) override;
        //void incrementTime(double tnew) override;
        //void throwDiscontinuityError(const char* chars, std::shared_ptr<std::vector<DiscontinuityType>> discontinuityTypes);
        //void interpolateAt(double t) override;
        void postRun() override;
        void runInitialConditionTypeSolution() override;
        void iStep(int i) override;
        void selectOrder() override;
        void checkForDiscontinuity() override;
        double suggestSmallerOrAcceptFirstStepSize(double hnew) override;
        FColDsptr integrationRelativeTolerance();
        FColDsptr integrationAbsoluteTolerance();
        FColDsptr correctorRelativeTolerance();
        FColDsptr correctorAbsoluteTolerance();
        void y(FColDsptr col) override;
        void ydot(FColDsptr col) override;
        virtual void preDAEOutput();
        virtual void postDAEOutput();

        int neqn, ncon;

    };
}

