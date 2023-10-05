/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselMbD.                                       *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "ASMTJoint.h"

namespace MbD {
    class ASMTUniversalJoint : public ASMTJoint
    {
        //
    public:
        virtual std::shared_ptr<Joint> mbdClassNew() override;

    };
}

