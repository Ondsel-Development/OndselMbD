/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "DispCompIecJeqcO.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<DispCompIecJeqcO> MbD::DispCompIecJeqcO::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axis)
{
	auto inst = std::make_shared<DispCompIecJeqcO>(frmi, frmj, axis);
	inst->initialize();
	return inst;
}

void DispCompIecJeqcO::initializeGlobally()
{
	priIeJeOpXJ = FullRow<double>::With(3, 0.0);
	priIeJeOpXJ->at(axis) = 1.0;
	ppriIeJeOpEJpEJ = std::static_pointer_cast<EndFrameqc>(efrmJ)->ppriOeOpEpE(axis);
}

FMatDsptr MbD::DispCompIecJeqcO::ppvaluepEJpEJ()
{
	return ppriIeJeOpEJpEJ;
}

FRowDsptr MbD::DispCompIecJeqcO::pvaluepEJ()
{
	return priIeJeOpEJ;
}

FRowDsptr MbD::DispCompIecJeqcO::pvaluepXJ()
{
	return priIeJeOpXJ;
}

void DispCompIecJeqcO::calcPostDynCorrectorIteration()
{
	DispCompIecJecO::calcPostDynCorrectorIteration();
	priIeJeOpEJ = std::static_pointer_cast<EndFrameqc>(efrmJ)->priOeOpE(axis);
}
