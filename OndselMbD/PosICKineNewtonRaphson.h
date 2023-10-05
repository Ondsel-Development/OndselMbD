/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselMbD.                                       *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "AnyPosICNewtonRaphson.h"

namespace MbD {
    class PosICKineNewtonRaphson : public AnyPosICNewtonRaphson
    {
        //Kinematics with under constrained system
    public:
        void initializeGlobally() override;
        void assignEquationNumbers() override;
        void preRun() override;
        bool isConverged() override;

    };
}
