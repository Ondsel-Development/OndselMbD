/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DispCompIeqcJecO.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<DispCompIeqcJecO> MbD::DispCompIeqcJecO::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axis)
{
	auto inst = std::make_shared<DispCompIeqcJecO>(frmi, frmj, axis);
	inst->initialize();
	return inst;
}

void DispCompIeqcJecO::initializeGlobally()
{
	priIeJeOpXI = FullRow<double>::With(3, 0.0);
	priIeJeOpXI->at(axis) = -1.0;
	ppriIeJeOpEIpEI = std::static_pointer_cast<EndFrameqc>(efrmI)->ppriOeOpEpE(axis)->negated();
}

FMatDsptr MbD::DispCompIeqcJecO::ppvaluepEIpEI()
{
	return ppriIeJeOpEIpEI;
}

FRowDsptr MbD::DispCompIeqcJecO::pvaluepEI()
{
	return priIeJeOpEI;
}

FRowDsptr MbD::DispCompIeqcJecO::pvaluepXI()
{
	return priIeJeOpXI;
}

void DispCompIeqcJecO::calcPostDynCorrectorIteration()
{
	DispCompIecJecO::calcPostDynCorrectorIteration();
	priIeJeOpEI = std::static_pointer_cast<EndFrameqc>(efrmI)->priOeOpE(axis)->negated();
}
