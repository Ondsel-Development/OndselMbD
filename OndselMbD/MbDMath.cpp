/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "MbDMath.h"
#include <cassert>

using namespace MbD;

std::shared_ptr<MbDMath> MbD::MbDMath::With()
{
	auto inst = std::make_shared<MbDMath>();
	//inst->initialize();
	return inst;
}

void MbD::MbDMath::noop()
{
	//No Operations
}
