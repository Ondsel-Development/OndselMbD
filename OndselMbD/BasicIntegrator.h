/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselMbD.                                       *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include <vector>

#include "Integrator.h"
#include "FullColumn.h"

namespace MbD {
    class IntegratorInterface;
    class LinearMultiStepMethod;

    class BasicIntegrator : public Integrator
    {
        //istep iTry maxTry tpast t tnew h hnew order orderNew orderMax opBDF continue 
    public:
        virtual void firstStep() = 0;
        void preFirstStep() override;
        virtual void nextStep() = 0;
        virtual void calcOperatorMatrix();
        virtual void incrementTime();
        virtual void incrementTry();
        void initialize() override;
        void initializeGlobally() override;
        void initializeLocally() override;
        void iStep(int i) override;
        void postRun() override;
        void preRun() override;
        void preStep() override;
        void reportStats() override;
        void run() override;
        void selectOrder() override;
        void subsequentSteps();
        void setSystem(Solver* sys) override;
        void logString(std::string& str) override;
        
        virtual void setorder(int o);
        virtual void settnew(double t);
        virtual void sett(double t);
        virtual void settime(double t);
        double tprevious();
        virtual FColDsptr yDerivat(int order, double tout);

        IntegratorInterface* system;
        int istep = 0, iTry = 0, maxTry = 0;
        std::shared_ptr<std::vector<double>> tpast;
        double t = 0, tnew = 0, h = 0, hnew = 0;
        int order = 0, orderNew = 0, orderMax = 0;
        std::shared_ptr<LinearMultiStepMethod> opBDF;
        bool _continue = false;
    };
}

