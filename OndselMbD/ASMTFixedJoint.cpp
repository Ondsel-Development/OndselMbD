/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselMbD.                                       *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "ASMTFixedJoint.h"

using namespace MbD;

std::shared_ptr<Joint> MbD::ASMTFixedJoint::mbdClassNew()
{
    return CREATE<FixedJoint>::With();
}
