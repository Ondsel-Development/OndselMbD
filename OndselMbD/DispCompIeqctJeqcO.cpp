/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DispCompIeqctJeqcO.h"
#include "EndFrameqct.h"

using namespace MbD;

std::shared_ptr<DispCompIeqctJeqcO> MbD::DispCompIeqctJeqcO::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axis)
{
	auto inst = std::make_shared<DispCompIeqctJeqcO>(frmi, frmj, axis);
	inst->initialize();
	return inst;
}

void DispCompIeqctJeqcO::initializeGlobally()
{
	//ToDo: Check why not using super classes.
	ppriIeJeOpEJpEJ = std::static_pointer_cast<EndFrameqct>(efrmJ)->ppriOeOpEpE(axis);
}

FRowDsptr MbD::DispCompIeqctJeqcO::ppvaluepEIpt()
{
	return ppriIeJeOpEIpt;
}

double MbD::DispCompIeqctJeqcO::ppvalueptpt()
{
	return ppriIeJeOptpt;
}

void DispCompIeqctJeqcO::calcPostDynCorrectorIteration()
{
	//"ppriIeJeOpEIpEI is not a constant now."
	DispCompIeqcJeqcO::calcPostDynCorrectorIteration();
	ppriIeJeOpEIpEI = std::static_pointer_cast<EndFrameqct>(efrmI)->ppriOeOpEpE(axis)->negated();
}

void DispCompIeqctJeqcO::preVelIC()
{
	Item::preVelIC();
	priIeJeOpt = -(std::static_pointer_cast<EndFrameqct>(efrmI)->priOeOpt(axis));
}

double DispCompIeqctJeqcO::pvaluept()
{
	return priIeJeOpt;
}

void DispCompIeqctJeqcO::preAccIC()
{
	Item::preAccIC();
	ppriIeJeOpEIpt = (std::static_pointer_cast<EndFrameqct>(efrmI)->ppriOeOpEpt(axis))->negated();
	ppriIeJeOptpt = -(std::static_pointer_cast<EndFrameqct>(efrmI)->ppriOeOptpt(axis));
}
