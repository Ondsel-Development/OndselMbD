/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "Function.h"
#include <cassert>

using namespace MbD;

void MbD::Function::arguments(Symsptr args)
{
	//Subclasses must implement.
	assert(false);
}
