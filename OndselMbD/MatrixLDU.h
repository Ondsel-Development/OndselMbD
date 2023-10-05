/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselMbD.                                       *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "MatrixDecomposition.h"

namespace MbD {
    class MatrixLDU : public MatrixDecomposition
    {
        //
    public:
        FColDsptr forAndBackSubsaveOriginal(FColDsptr fullCol, bool saveOriginal) override;

    };
}
