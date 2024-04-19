/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "ForceTorqueItem.h"

using namespace MbD;

std::shared_ptr<ForceTorqueItem> MbD::ForceTorqueItem::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
	auto inst = std::make_shared<ForceTorqueItem>(frmi, frmj);
	inst->initialize();
	return inst;
}

void MbD::ForceTorqueItem::fillStaticError(FColDsptr col)
{
	assert(false);
}

void MbD::ForceTorqueItem::fillStaticJacob(SpMatDsptr mat)
{
	assert(false);
}

void MbD::ForceTorqueItem::postAccICIteration()
{
	calcPostDynCorrectorIteration();
}

void MbD::ForceTorqueItem::postCollisionCorrectorIteration()
{
	assert(false);
}

void MbD::ForceTorqueItem::postCollisionPredictor()
{
	assert(false);
}

FColDsptr MbD::ForceTorqueItem::aFX() const
{
	assert(false);
	return FColDsptr();
}

FColDsptr MbD::ForceTorqueItem::aTX() const
{
	assert(false);
	return FColDsptr();
}

FColDsptr MbD::ForceTorqueItem::getFTIeO() const
{
	assert(false);
	return FColDsptr();
}

void MbD::ForceTorqueItem::forceOnFrmIandFrmJ(EndFrmsptr eFrmI, EndFrmsptr eFrmJ)
{
	assert(false);
}

void MbD::ForceTorqueItem::torqueOnFrmIandFrmJ(EndFrmsptr eFrmI, EndFrmsptr eFrmJ)
{
	assert(false);
}
