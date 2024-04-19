/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "ASMTForceTorqueGeneral.h"

using namespace MbD;

std::shared_ptr<ASMTForceTorqueGeneral> MbD::ASMTForceTorqueGeneral::With()
{
	auto inst = std::make_shared<ASMTForceTorqueGeneral>();
	inst->initialize();
	return inst;
}

void MbD::ASMTForceTorqueGeneral::createMbD(std::shared_ptr<System> mbdSys, std::shared_ptr<Units> mbdUnits)
{
	assert(false);
}
