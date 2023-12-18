/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "LDUFullMatParPv.h"

namespace MbD {
    class LDUFullMatParPvRobust : public LDUFullMatParPv
    {
        //
    public:
        void doPivoting(int p) override;

    };
}
