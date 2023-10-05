/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselMbD.                                       *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "Integrator.h"
#include "FullColumn.h"
#include "SparseMatrix.h"

namespace MbD {
    class BasicIntegrator;
    class StartingBasicDAEIntegrator;
    class NormalBasicDAEIntegrator;

    class IntegratorInterface : public Integrator
    {
        //tout hout hmin hmax tstart tend integrator 
    public:

        void initializeGlobally() override;
        virtual void preRun() = 0;
        virtual void checkForDiscontinuity() = 0;
        
        void setSystem(Solver* sys) override;
        void logString(std::string& str) override;
        void run() override;
        int orderMax();
        virtual void incrementTime(double tnew);

        virtual double suggestSmallerOrAcceptFirstStepSize(double hnew) = 0;
        virtual double suggestSmallerOrAcceptStepSize(double hnew) = 0;
        virtual void checkForOutputThrough(double t) = 0;
        virtual void interpolateAt(double t);
        virtual void fillF(FColDsptr vecF);
        virtual void fillpFpy(SpMatDsptr mat);
        virtual void fillpFpydot(SpMatDsptr mat);
        void changeTime(double t);
        virtual void y(FColDsptr col);
        virtual void ydot(FColDsptr col);
        virtual void updateForDAECorrector();

        SystemSolver* system;
        double tout = 0, hout = 0, hmin = 0, hmax = 0, tstart = 0, tend = 0;
        std::shared_ptr<BasicIntegrator> integrator;
    };
}

