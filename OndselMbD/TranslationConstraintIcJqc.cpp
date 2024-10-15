/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "TranslationConstraintIcJqc.h"
#include "DispCompIeqcJeqcKeqc.h"
#include "DispCompIecJeqcKec.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<TranslationConstraintIcJqc> MbD::TranslationConstraintIcJqc::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi)
{
	auto inst = std::make_shared<TranslationConstraintIcJqc>(frmi, frmj, axisi);
	inst->initialize();
	return inst;
}

void TranslationConstraintIcJqc::initriIeJeIe()
{
	riIeJeIe = DispCompIecJeqcKec::With(efrmI, efrmJ, efrmI, axisI);
}

void TranslationConstraintIcJqc::calcPostDynCorrectorIteration()
{
	TranslationConstraintIJ::calcPostDynCorrectorIteration();
	pGpXJ = riIeJeIe->pvaluepXJ();
	pGpEJ = riIeJeIe->pvaluepEJ();
	ppGpEJpEJ = riIeJeIe->ppvaluepEJpEJ();
}

void TranslationConstraintIcJqc::useEquationNumbers()
{
	TranslationConstraintIJ::useEquationNumbers();
	auto frmJeqc = std::static_pointer_cast<EndFrameqc>(efrmJ);
	iqXJ = frmJeqc->iqX();
	iqEJ = frmJeqc->iqE();
}

void MbD::TranslationConstraintIcJqc::fillpFpy(SpMatDsptr mat)
{
	TranslationConstraintIJ::fillpFpy(mat);
	mat->atandplusFullRow(iG, iqXJ, pGpXJ);
	mat->atandplusFullRow(iG, iqEJ, pGpEJ);
	mat->atandplusFullMatrixtimes(iqEJ, iqEJ, ppGpEJpEJ, lam);
}

void MbD::TranslationConstraintIcJqc::fillpFpydot(SpMatDsptr mat)
{
	TranslationConstraintIJ::fillpFpydot(mat);
	mat->atandplusFullColumn(iqXJ, iG, pGpXJ->transpose());
	mat->atandplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}

void TranslationConstraintIcJqc::fillPosICError(FColDsptr col)
{
	TranslationConstraintIJ::fillPosICError(col);
	col->atplusFullVectortimes(iqXJ, pGpXJ, lam);
	col->atplusFullVectortimes(iqEJ, pGpEJ, lam);
}

void TranslationConstraintIcJqc::fillPosICJacob(SpMatDsptr mat)
{
	TranslationConstraintIJ::fillPosICJacob(mat);
	mat->atandplusFullRow(iG, iqXJ, pGpXJ);
	mat->atandplusFullColumn(iqXJ, iG, pGpXJ->transpose());
	mat->atandplusFullRow(iG, iqEJ, pGpEJ);
	mat->atandplusFullColumn(iqEJ, iG, pGpEJ->transpose());
	mat->atandplusFullMatrixtimes(iqEJ, iqEJ, ppGpEJpEJ, lam);
}

void TranslationConstraintIcJqc::fillPosKineJacob(SpMatDsptr mat)
{
	TranslationConstraintIJ::fillPosKineJacob(mat);
	mat->atandplusFullRow(iG, iqXJ, pGpXJ);
	mat->atandplusFullRow(iG, iqEJ, pGpEJ);
}

void TranslationConstraintIcJqc::fillVelICJacob(SpMatDsptr mat)
{
	TranslationConstraintIJ::fillVelICJacob(mat);
	mat->atandplusFullRow(iG, iqXJ, pGpXJ);
	mat->atandplusFullColumn(iqXJ, iG, pGpXJ->transpose());
	mat->atandplusFullRow(iG, iqEJ, pGpEJ);
	mat->atandplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}

void TranslationConstraintIcJqc::fillAccICIterError(FColDsptr col)
{
	TranslationConstraintIJ::fillAccICIterError(col);
	col->atplusFullVectortimes(iqXJ, pGpXJ, lam);
	col->atplusFullVectortimes(iqEJ, pGpEJ, lam);
	auto efrmJqc = std::static_pointer_cast<EndFrameqc>(efrmJ);
	auto qXdotJ = efrmJqc->qXdot();
	auto qEdotJ = efrmJqc->qEdot();
	double sum = pGpXJ->timesFullColumn(efrmJqc->qXddot());
	sum += pGpEJ->timesFullColumn(efrmJqc->qEddot());
	sum += qEdotJ->transposeTimesFullColumn(ppGpEJpEJ->timesFullColumn(qEdotJ));
	col->atplusNumber(iG, sum);
}
