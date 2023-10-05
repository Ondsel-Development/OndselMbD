/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselMbD.                                       *
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
        virtual void preFirstStep() = 0;
        virtual void preStep() = 0;
        virtual void runInitialConditionTypeSolution() = 0;
        virtual void iStep(int i) = 0;
        virtual void selectOrder() = 0;
        virtual int iterMax();

        double direction = 1;
    };
}

