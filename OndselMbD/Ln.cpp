/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselMbD.                                       *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "Ln.h"

using namespace MbD;

MbD::Ln::Ln(Symsptr arg) : FunctionX(arg)
{
}

double MbD::Ln::getValue()
{
    return std::log(xx->getValue());
}
