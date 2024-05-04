/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DispCompIecJecO.h"
#include "EndFramec.h"

using namespace MbD;

std::shared_ptr<DispCompIecJecO> MbD::DispCompIecJecO::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axis)
{
	auto inst = std::make_shared<DispCompIecJecO>(frmi, frmj, axis);
	inst->initialize();
	return inst;
}

void MbD::DispCompIecJecO::withFrmIfrmJaxis(EndFrmsptr frmi, EndFrmsptr frmj, size_t axs)
{
	efrmI = frmi;
	efrmJ = frmj;
	axis = axs;
}

void DispCompIecJecO::calcPostDynCorrectorIteration()
{
	riIeJeO = efrmJ->riOeO(axis) - efrmI->riOeO(axis);
}

double MbD::DispCompIecJecO::value()
{
	return riIeJeO;
}
