/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
#include <fstream>	

#include "ASMTPerpendicularJoint.h"
#include "PerpendicularJoint.h"

using namespace MbD;

std::shared_ptr<Joint> MbD::ASMTPerpendicularJoint::mbdClassNew()
{
    return CREATE<PerpendicularJoint>::With();
}

std::shared_ptr<ASMTPerpendicularJoint> MbD::ASMTPerpendicularJoint::With()
{
    return std::make_shared<ASMTPerpendicularJoint>();
}
