/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "AtPointConstraintIcJqc.h"
#include "DispCompIecJeqcO.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<AtPointConstraintIcJqc> MbD::AtPointConstraintIcJqc::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisO)
{
	auto inst = std::make_shared<AtPointConstraintIcJqc>(frmi, frmj, axisO);
	inst->initialize();
	return inst;
}

void AtPointConstraintIcJqc::initializeGlobally()
{
	AtPointConstraintIJ::initializeGlobally();
	ppGpEJpEJ = (std::static_pointer_cast<DispCompIecJeqcO>(riIeJeO))->ppriIeJeOpEJpEJ;
}

void AtPointConstraintIcJqc::initriIeJeO()
{
	riIeJeO = DispCompIecJeqcO::With(efrmI, efrmJ, axis);
}

void AtPointConstraintIcJqc::calcPostDynCorrectorIteration()
{
	AtPointConstraintIJ::calcPostDynCorrectorIteration();
	pGpEJ = std::static_pointer_cast<DispCompIecJeqcO>(riIeJeO)->priIeJeOpEJ;
}

void AtPointConstraintIcJqc::useEquationNumbers()
{
	AtPointConstraintIJ::useEquationNumbers();
	auto frmJeqc = std::static_pointer_cast<EndFrameqc>(efrmJ);
	iqXJminusOnePlusAxis = frmJeqc->iqX() + axis;
	iqEJ = frmJeqc->iqE();
}

void MbD::AtPointConstraintIcJqc::fillpFpy(SpMatDsptr mat)
{
	AtPointConstraintIJ::fillpFpy(mat);
	mat->atandplusNumber(iG, iqXJminusOnePlusAxis, 1.0);
	mat->atandplusFullRow(iG, iqEJ, pGpEJ);
	mat->atandplusFullMatrixtimes(iqEJ, iqEJ, ppGpEJpEJ, lam);
}

void MbD::AtPointConstraintIcJqc::fillpFpydot(SpMatDsptr mat)
{
	AtPointConstraintIJ::fillpFpydot(mat);
	mat->atandplusNumber(iqXJminusOnePlusAxis, iG, 1.0);
	mat->atandplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}

void AtPointConstraintIcJqc::fillPosICError(FColDsptr col)
{
	AtPointConstraintIJ::fillPosICError(col);
	col->atplusNumber(iqXJminusOnePlusAxis, lam);
	col->atplusFullVectortimes(iqEJ, pGpEJ, lam);
}

void AtPointConstraintIcJqc::fillPosICJacob(SpMatDsptr mat)
{
	AtPointConstraintIJ::fillPosICJacob(mat);
	mat->atandplusNumber(iG, iqXJminusOnePlusAxis, 1.0);
	mat->atandplusNumber(iqXJminusOnePlusAxis, iG, 1.0);
	mat->atandplusFullRow(iG, iqEJ, pGpEJ);
	mat->atandplusFullColumn(iqEJ, iG, pGpEJ->transpose());
	mat->atandplusFullMatrixtimes(iqEJ, iqEJ, ppGpEJpEJ, lam);
}

void AtPointConstraintIcJqc::fillPosKineJacob(SpMatDsptr mat)
{
	AtPointConstraintIJ::fillPosKineJacob(mat);
	mat->atandplusNumber(iG, iqXJminusOnePlusAxis, 1.0);
	mat->atandplusFullRow(iG, iqEJ, pGpEJ);
}

void AtPointConstraintIcJqc::fillVelICJacob(SpMatDsptr mat)
{
	AtPointConstraintIJ::fillVelICJacob(mat);
	mat->atandplusNumber(iG, iqXJminusOnePlusAxis, 1.0);
	mat->atandplusNumber(iqXJminusOnePlusAxis, iG, 1.0);
	mat->atandplusFullRow(iG, iqEJ, pGpEJ);
	mat->atandplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}

void AtPointConstraintIcJqc::fillAccICIterError(FColDsptr col)
{
	AtPointConstraintIJ::fillAccICIterError(col);
	col->atplusNumber(iqXJminusOnePlusAxis, lam);
	col->atplusFullVectortimes(iqEJ, pGpEJ, lam);
	auto efrmJqc = std::static_pointer_cast<EndFrameqc>(efrmJ);
	auto qEdotJ = efrmJqc->qEdot();
	auto sum = efrmJqc->qXddot()->at(axis);
	sum += pGpEJ->timesFullColumn(efrmJqc->qEddot());
	sum += qEdotJ->transposeTimesFullColumn(ppGpEJpEJ->timesFullColumn(qEdotJ));
	col->atplusNumber(iG, sum);
}
