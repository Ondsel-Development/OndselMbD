/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselMbD.                                       *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "AccICNewtonRaphson.h"

namespace MbD {
    class AccICKineNewtonRaphson : public AccICNewtonRaphson
    {
        //Kinematics with under constrained system
    public:
        void initializeGlobally() override;
        void preRun() override;


    };
}

