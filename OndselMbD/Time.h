/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselMbD.                                       *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "IndependentVariable.h"

namespace MbD {
    class Time : public IndependentVariable
    {
    public:
        Time();
        void initialize() override;
    };
}

