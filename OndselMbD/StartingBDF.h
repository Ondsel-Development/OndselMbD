/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "BackwardDifference.h"

namespace MbD {


#pragma once
    class StartingBDF : public BackwardDifference
    {
        //
    public:
        void initialize() override;
        void initializeLocally() override;
        void formTaylorMatrix() override;
        void setorder(int o) override;
        FColDsptr derivativepresentpastpresentDerivativepastDerivative(int n,
            FColDsptr y, std::shared_ptr<std::vector<FColDsptr>> ypast,
            FColDsptr ydot, std::shared_ptr<std::vector<FColDsptr>> ydotpast);


    };
}
