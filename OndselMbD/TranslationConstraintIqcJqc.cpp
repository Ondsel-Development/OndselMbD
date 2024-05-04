/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "TranslationConstraintIqcJqc.h"
#include "DispCompIeqcJeqcKeqc.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<TranslationConstraintIqcJqc> MbD::TranslationConstraintIqcJqc::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi)
{
	auto inst = std::make_shared<TranslationConstraintIqcJqc>(frmi, frmj, axisi);
	inst->initialize();
	return inst;
}

void TranslationConstraintIqcJqc::initriIeJeIe()
{
	riIeJeIe = DispCompIeqcJeqcKeqc::With(efrmI, efrmJ, efrmI, axisI);
}

void TranslationConstraintIqcJqc::calcPostDynCorrectorIteration()
{
	TranslationConstraintIqcJc::calcPostDynCorrectorIteration();
	pGpXJ = riIeJeIe->pvaluepXJ();
	pGpEJ = riIeJeIe->pvaluepEJ();
	ppGpEIpXJ = riIeJeIe->ppvaluepXJpEK()->transpose();
	ppGpEIpEJ = riIeJeIe->ppvaluepEJpEK()->transpose();
	ppGpEJpEJ = riIeJeIe->ppvaluepEJpEJ();
}

void TranslationConstraintIqcJqc::useEquationNumbers()
{
	TranslationConstraintIqcJc::useEquationNumbers();
	auto frmJeqc = std::static_pointer_cast<EndFrameqc>(efrmJ);
	iqXJ = frmJeqc->iqX();
	iqEJ = frmJeqc->iqE();
}

void MbD::TranslationConstraintIqcJqc::fillpFpy(SpMatDsptr mat)
{
	TranslationConstraintIqcJc::fillpFpy(mat);
	mat->atandplusFullRow(iG, iqXJ, pGpXJ);
	mat->atandplusFullRow(iG, iqEJ, pGpEJ);
	auto ppGpEIpXJlam = ppGpEIpXJ->times(lam);
	mat->atandplusFullMatrix(iqEI, iqXJ, ppGpEIpXJlam);
	mat->atandplusTransposeFullMatrix(iqXJ, iqEI, ppGpEIpXJlam);
	auto ppGpEIpEJlam = ppGpEIpEJ->times(lam);
	mat->atandplusFullMatrix(iqEI, iqEJ, ppGpEIpEJlam);
	mat->atandplusTransposeFullMatrix(iqEJ, iqEI, ppGpEIpEJlam);
	mat->atandplusFullMatrixtimes(iqEJ, iqEJ, ppGpEJpEJ, lam);
}

void MbD::TranslationConstraintIqcJqc::fillpFpydot(SpMatDsptr mat)
{
	TranslationConstraintIqcJc::fillpFpydot(mat);
	mat->atandplusFullColumn(iqXJ, iG, pGpXJ->transpose());
	mat->atandplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}

void TranslationConstraintIqcJqc::fillPosICError(FColDsptr col)
{
	TranslationConstraintIqcJc::fillPosICError(col);
	col->atplusFullVectortimes(iqXJ, pGpXJ, lam);
	col->atplusFullVectortimes(iqEJ, pGpEJ, lam);
}

void TranslationConstraintIqcJqc::fillPosICJacob(SpMatDsptr mat)
{
	TranslationConstraintIqcJc::fillPosICJacob(mat);
	mat->atandplusFullRow(iG, iqXJ, pGpXJ);
	mat->atandplusFullColumn(iqXJ, iG, pGpXJ->transpose());
	mat->atandplusFullRow(iG, iqEJ, pGpEJ);
	mat->atandplusFullColumn(iqEJ, iG, pGpEJ->transpose());
	auto ppGpEIpXJlam = ppGpEIpXJ->times(lam);
	mat->atandplusFullMatrix(iqEI, iqXJ, ppGpEIpXJlam);
	mat->atandplusTransposeFullMatrix(iqXJ, iqEI, ppGpEIpXJlam);
	auto ppGpEIpEJlam = ppGpEIpEJ->times(lam);
	mat->atandplusFullMatrix(iqEI, iqEJ, ppGpEIpEJlam);
	mat->atandplusTransposeFullMatrix(iqEJ, iqEI, ppGpEIpEJlam);
	mat->atandplusFullMatrixtimes(iqEJ, iqEJ, ppGpEJpEJ, lam);
}

void TranslationConstraintIqcJqc::fillPosKineJacob(SpMatDsptr mat)
{
	TranslationConstraintIqcJc::fillPosKineJacob(mat);
	mat->atandplusFullRow(iG, iqXJ, pGpXJ);
	mat->atandplusFullRow(iG, iqEJ, pGpEJ);
}

void TranslationConstraintIqcJqc::fillVelICJacob(SpMatDsptr mat)
{
	TranslationConstraintIqcJc::fillVelICJacob(mat);
	mat->atandplusFullRow(iG, iqXJ, pGpXJ);
	mat->atandplusFullColumn(iqXJ, iG, pGpXJ->transpose());
	mat->atandplusFullRow(iG, iqEJ, pGpEJ);
	mat->atandplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}

void TranslationConstraintIqcJqc::fillAccICIterError(FColDsptr col)
{
	TranslationConstraintIqcJc::fillAccICIterError(col);
	col->atplusFullVectortimes(iqXJ, pGpXJ, lam);
	col->atplusFullVectortimes(iqEJ, pGpEJ, lam);
	auto efrmIqc = std::static_pointer_cast<EndFrameqc>(efrmI);
	auto efrmJqc = std::static_pointer_cast<EndFrameqc>(efrmJ);
	auto qEdotI = efrmIqc->qEdot();
	auto qXdotJ = efrmJqc->qXdot();
	auto qEdotJ = efrmJqc->qEdot();
	double sum = pGpXJ->timesFullColumn(efrmJqc->qXddot());
	sum += pGpEJ->timesFullColumn(efrmJqc->qEddot());
	sum += 2.0 * (qEdotI->transposeTimesFullColumn(ppGpEIpXJ->timesFullColumn(qXdotJ)));
	sum += 2.0 * (qEdotI->transposeTimesFullColumn(ppGpEIpEJ->timesFullColumn(qEdotJ)));
	sum += qEdotJ->transposeTimesFullColumn(ppGpEJpEJ->timesFullColumn(qEdotJ));
	col->atplusNumber(iG, sum);
}
