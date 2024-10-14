/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "DispCompIectJeqcO.h"
#include "EndFramect.h"

using namespace MbD;

std::shared_ptr<DispCompIectJeqcO> MbD::DispCompIectJeqcO::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axis)
{
	auto inst = std::make_shared<DispCompIectJeqcO>(frmi, frmj, axis);
	inst->initialize();
	return inst;
}

double MbD::DispCompIectJeqcO::ppvalueptpt()
{
	return ppriIeJeOptpt;
}

void DispCompIectJeqcO::preVelIC()
{
	Item::preVelIC();
	priIeJeOpt = -(std::static_pointer_cast<EndFramect>(efrmI)->priOeOpt(axis));
}

double DispCompIectJeqcO::pvaluept()
{
	return priIeJeOpt;
}

void DispCompIectJeqcO::preAccIC()
{
	Item::preAccIC();
	ppriIeJeOptpt = -(std::static_pointer_cast<EndFramect>(efrmI)->ppriOeOptpt(axis));
}
