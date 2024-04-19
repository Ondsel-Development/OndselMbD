/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "AtPointConstraintIqcJqc.h"
#include "DispCompIeqcJeqcO.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<AtPointConstraintIqcJqc> MbD::AtPointConstraintIqcJqc::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisO)
{
	auto inst = std::make_shared<AtPointConstraintIqcJqc>(frmi, frmj, axisO);
	inst->initialize();
	return inst;
}

void AtPointConstraintIqcJqc::initializeGlobally()
{
	AtPointConstraintIqcJc::initializeGlobally();
	ppGpEJpEJ = (std::static_pointer_cast<DispCompIeqcJeqcO>(riIeJeO))->ppriIeJeOpEJpEJ;
}

void AtPointConstraintIqcJqc::initriIeJeO()
{
	riIeJeO = DispCompIeqcJeqcO::With(frmI, frmJ, axis);
}

void AtPointConstraintIqcJqc::calcPostDynCorrectorIteration()
{
	AtPointConstraintIqcJc::calcPostDynCorrectorIteration();
	pGpEJ = std::static_pointer_cast<DispCompIeqcJeqcO>(riIeJeO)->priIeJeOpEJ;
}

void AtPointConstraintIqcJqc::useEquationNumbers()
{
	AtPointConstraintIqcJc::useEquationNumbers();
	auto frmJeqc = std::static_pointer_cast<EndFrameqc>(frmJ);
	iqXJminusOnePlusAxis = frmJeqc->iqX() + axis;
	iqEJ = frmJeqc->iqE();
}

void MbD::AtPointConstraintIqcJqc::fillpFpy(SpMatDsptr mat)
{
	AtPointConstraintIqcJc::fillpFpy(mat);
	mat->atandplusNumber(iG, iqXJminusOnePlusAxis, 1.0);
	mat->atandplusFullRow(iG, iqEJ, pGpEJ);
	mat->atandplusFullMatrixtimes(iqEJ, iqEJ, ppGpEJpEJ, lam);
}

void MbD::AtPointConstraintIqcJqc::fillpFpydot(SpMatDsptr mat)
{
	AtPointConstraintIqcJc::fillpFpydot(mat);
	mat->atandplusNumber(iqXJminusOnePlusAxis, iG, 1.0);
	mat->atandplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}

void AtPointConstraintIqcJqc::fillPosICError(FColDsptr col)
{
	AtPointConstraintIqcJc::fillPosICError(col);
	col->atplusNumber(iqXJminusOnePlusAxis, lam);
	col->atplusFullVectortimes(iqEJ, pGpEJ, lam);
}

void AtPointConstraintIqcJqc::fillPosICJacob(SpMatDsptr mat)
{
	AtPointConstraintIqcJc::fillPosICJacob(mat);
	mat->atandplusNumber(iG, iqXJminusOnePlusAxis, 1.0);
	mat->atandplusNumber(iqXJminusOnePlusAxis, iG, 1.0);
	mat->atandplusFullRow(iG, iqEJ, pGpEJ);
	mat->atandplusFullColumn(iqEJ, iG, pGpEJ->transpose());
	mat->atandplusFullMatrixtimes(iqEJ, iqEJ, ppGpEJpEJ, lam);
}

void AtPointConstraintIqcJqc::fillPosKineJacob(SpMatDsptr mat)
{
	AtPointConstraintIqcJc::fillPosKineJacob(mat);
	mat->atandplusNumber(iG, iqXJminusOnePlusAxis, 1.0);
	mat->atandplusFullRow(iG, iqEJ, pGpEJ);
}

void AtPointConstraintIqcJqc::fillVelICJacob(SpMatDsptr mat)
{
	AtPointConstraintIqcJc::fillVelICJacob(mat);
	mat->atandplusNumber(iG, iqXJminusOnePlusAxis, 1.0);
	mat->atandplusNumber(iqXJminusOnePlusAxis, iG, 1.0);
	mat->atandplusFullRow(iG, iqEJ, pGpEJ);
	mat->atandplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}

void AtPointConstraintIqcJqc::fillAccICIterError(FColDsptr col)
{
	AtPointConstraintIqcJc::fillAccICIterError(col);
	col->atplusNumber(iqXJminusOnePlusAxis, lam);
	col->atplusFullVectortimes(iqEJ, pGpEJ, lam);
	auto efrmJqc = std::static_pointer_cast<EndFrameqc>(frmJ);
	auto qEdotJ = efrmJqc->qEdot();
	auto sum = efrmJqc->qXddot()->at(axis);
	sum += pGpEJ->timesFullColumn(efrmJqc->qEddot());
	sum += qEdotJ->transposeTimesFullColumn(ppGpEJpEJ->timesFullColumn(qEdotJ));
	col->atplusNumber(iG, sum);
}
