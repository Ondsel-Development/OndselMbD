/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <cmath>

#include "SingularMatrixError.h"

using namespace MbD;

#include "LDUFullMatParPvRobust.h"

void MbD::LDUFullMatParPvRobust::doPivoting(int p)
{
	try {
		LDUFullMatParPv::doPivoting(p);
	}
	catch (SingularMatrixError ex) {
		//Resume
	}
}
