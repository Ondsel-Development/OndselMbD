/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselMbD.                                       *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DispCompIecJecO.h"
#include "EndFramec.h"

using namespace MbD;

DispCompIecJecO::DispCompIecJecO()
{
}

DispCompIecJecO::DispCompIecJecO(EndFrmsptr frmi, EndFrmsptr frmj, int axis) : KinematicIeJe(frmi, frmj), axis(axis)
{
}

void DispCompIecJecO::calcPostDynCorrectorIteration()
{
	riIeJeO = frmJ->riOeO(axis) - frmI->riOeO(axis);
}

double MbD::DispCompIecJecO::value()
{
	return riIeJeO;
}
