/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include <memory>
#include "Solver.h"

namespace MbD {
    class SystemSolver;

    class Integrator : public Solver
    {
        //system direction 
    public:
        void setSystem(Solver* sys) override;
        virtual void firstStep();
        virtual void preFirstStep();
        virtual void postFirstStep();
        virtual void subsequentSteps();
        virtual void nextStep();
        virtual void preStep();
        virtual void postStep();
        virtual void runInitialConditionTypeSolution();
        virtual void iStep(int i);
        virtual void selectOrder();
        virtual void selectStepSize();
        virtual int iterMax();

        double direction = 1;
    };
}

