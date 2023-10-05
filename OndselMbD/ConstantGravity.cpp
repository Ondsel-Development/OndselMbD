/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselMbD.									   *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "ConstantGravity.h"
#include "System.h"
#include "Part.h"

using namespace MbD;

void MbD::ConstantGravity::fillAccICIterError(FColDsptr col)
{
	fillDynError(col);
}

void MbD::ConstantGravity::fillDynError(FColDsptr col)
{
	for (auto& part : *(root()->parts)) {
		col->atiplusFullColumntimes(part->iqX(), gXYZ, part->m);
	}
}

void MbD::ConstantGravity::postDynPredictor()
{
	//Do nothing.
}

void MbD::ConstantGravity::fillpFpy(SpMatDsptr mat)
{
	//Do nothing.
}

void MbD::ConstantGravity::fillpFpydot(SpMatDsptr mat)
{
	//Do nothing.
}

void MbD::ConstantGravity::postDynCorrectorIteration()
{
	//Do nothing.
}
