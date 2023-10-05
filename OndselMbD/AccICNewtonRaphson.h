/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselMbD.                                       *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "AccNewtonRaphson.h"

namespace MbD {
    class AccICNewtonRaphson : public AccNewtonRaphson
    {
        //IC acceleration with fully or under constrained system
    public:
        bool isConverged() override;
        void preRun() override;


    };
}

