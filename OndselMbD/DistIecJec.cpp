/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DistIecJec.h"
#include "EndFramec.h"

using namespace MbD;

std::shared_ptr<DistIecJec> MbD::DistIecJec::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
	auto inst = std::make_shared<DistIecJec>(frmi, frmj);
	inst->initialize();
	return inst;
}

void MbD::DistIecJec::calcPostDynCorrectorIteration()
{
	rIeJeO = efrmJ->rOeO->minusFullColumn(efrmI->rOeO);
	rIeJe = rIeJeO->length();
	calcPrivate();
}

void MbD::DistIecJec::calcPrivate()
{
	if (rIeJe == 0.0) return;
	uIeJeO = rIeJeO->times(1.0 / rIeJe);
	muIeJeO = uIeJeO->negated();
}

double MbD::DistIecJec::value()
{
	return rIeJe;
}
