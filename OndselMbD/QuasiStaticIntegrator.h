/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include <vector>

#include "QuasiIntegrator.h"

namespace MbD {
    class SolverStatistics;

    class QuasiStaticIntegrator : public QuasiIntegrator
    {
        //
    public:
        void useTrialStepStats(std::shared_ptr<SolverStatistics> stats);


    };
}
