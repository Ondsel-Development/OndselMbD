/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DistanceConstraintIqcJqc.h"
#include "EndFrameqc.h"
#include "DistIeqcJeqc.h"

using namespace MbD;

MbD::DistanceConstraintIqcJqc::DistanceConstraintIqcJqc(EndFrmsptr frmi, EndFrmsptr frmj) : DistanceConstraintIqcJc(frmi, frmj)
{
	assert(false);
}

std::shared_ptr<DistanceConstraintIqcJqc> MbD::DistanceConstraintIqcJqc::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
	auto inst = std::make_shared<DistanceConstraintIqcJqc>(frmi, frmj);
	inst->initialize();
	return inst;
}

void MbD::DistanceConstraintIqcJqc::calcPostDynCorrectorIteration()
{
	DistanceConstraintIqcJc::calcPostDynCorrectorIteration();
	pGpXJ = distIeJe->pvaluepXJ();
	pGpEJ = distIeJe->pvaluepEJ();
	ppGpXIpXJ = distIeJe->ppvaluepXIpXJ();
	ppGpEIpXJ = distIeJe->ppvaluepEIpXJ();
	ppGpXJpXJ = distIeJe->ppvaluepXJpXJ();
	ppGpXIpEJ = distIeJe->ppvaluepXIpEJ();
	ppGpEIpEJ = distIeJe->ppvaluepEIpEJ();
	ppGpXJpEJ = distIeJe->ppvaluepXJpEJ();
	ppGpEJpEJ = distIeJe->ppvaluepEJpEJ();
}

void MbD::DistanceConstraintIqcJqc::fillAccICIterError(FColDsptr col)
{
	DistanceConstraintIqcJc::fillAccICIterError(col);
	col->atplusFullVectortimes(iqXJ, pGpXJ, lam);
	col->atplusFullVectortimes(iqEJ, pGpEJ, lam);
	auto frmIeqc = std::static_pointer_cast<EndFrameqc>(frmI);
	auto frmJeqc = std::static_pointer_cast<EndFrameqc>(frmJ);
	auto qXdotI = frmIeqc->qXdot();
	auto qEdotI = frmIeqc->qEdot();
	auto qXdotJ = frmJeqc->qXdot();
	auto qEdotJ = frmJeqc->qEdot();
	double sum = 0.0;
	sum += pGpXJ->timesFullColumn(frmJeqc->qXddot());
	sum += pGpEJ->timesFullColumn(frmJeqc->qEddot());
	sum += 2.0 * (qXdotI->transposeTimesFullColumn(ppGpXIpXJ->timesFullColumn(qXdotJ)));
	sum += 2.0 * (qEdotI->transposeTimesFullColumn(ppGpEIpXJ->timesFullColumn(qXdotJ)));
	sum += qXdotJ->transposeTimesFullColumn(ppGpXJpXJ->timesFullColumn(qXdotJ));
	sum += 2.0 * (qXdotI->transposeTimesFullColumn(ppGpXIpEJ->timesFullColumn(qEdotJ)));
	sum += 2.0 * (qEdotI->transposeTimesFullColumn(ppGpEIpEJ->timesFullColumn(qEdotJ)));
	sum += 2.0 * (qXdotJ->transposeTimesFullColumn(ppGpXJpEJ->timesFullColumn(qEdotJ)));
	sum += qEdotJ->transposeTimesFullColumn(ppGpEJpEJ->timesFullColumn(qEdotJ));
	col->atplusNumber(iG, sum);
}

void MbD::DistanceConstraintIqcJqc::fillPosICError(FColDsptr col)
{
	DistanceConstraintIqcJc::fillPosICError(col);
	col->atplusFullVectortimes(iqXJ, pGpXJ, lam);
	col->atplusFullVectortimes(iqEJ, pGpEJ, lam);
}

void MbD::DistanceConstraintIqcJqc::fillPosICJacob(SpMatDsptr mat)
{
	DistanceConstraintIqcJc::fillPosICJacob(mat);
	mat->atandplusFullRow(iG, iqXJ, pGpXJ);
	mat->atandplusFullColumn(iqXJ, iG, pGpXJ->transpose());
	mat->atandplusFullRow(iG, iqEJ, pGpEJ);
	mat->atandplusFullColumn(iqEJ, iG, pGpEJ->transpose());
	auto ppGpXIpXJlam = ppGpXIpXJ->times(lam);
	mat->atandplusFullMatrix(iqXI, iqXJ, ppGpXIpXJlam);
	mat->atandplusTransposeFullMatrix(iqXJ, iqXI, ppGpXIpXJlam);
	auto ppGpEIpXJlam = ppGpEIpXJ->times(lam);
	mat->atandplusFullMatrix(iqEI, iqXJ, ppGpEIpXJlam);
	mat->atandplusTransposeFullMatrix(iqXJ, iqEI, ppGpEIpXJlam);
	mat->atandplusFullMatrixtimes(iqXJ, iqXJ, ppGpXJpXJ, lam);
	auto ppGpXIpEJlam = ppGpXIpEJ->times(lam);
	mat->atandplusFullMatrix(iqXI, iqEJ, ppGpXIpEJlam);
	mat->atandplusTransposeFullMatrix(iqEJ, iqXI, ppGpXIpEJlam);
	auto ppGpEIpEJlam = ppGpEIpEJ->times(lam);
	mat->atandplusFullMatrix(iqEI, iqEJ, ppGpEIpEJlam);
	mat->atandplusTransposeFullMatrix(iqEJ, iqEI, ppGpEIpEJlam);
	auto ppGpXJpEJlam = ppGpXJpEJ->times(lam);
	mat->atandplusFullMatrix(iqXJ, iqEJ, ppGpXJpEJlam);
	mat->atandplusTransposeFullMatrix(iqEJ, iqXJ, ppGpXJpEJlam);
	mat->atandplusFullMatrixtimes(iqEJ, iqEJ, ppGpEJpEJ, lam);
}

void MbD::DistanceConstraintIqcJqc::fillPosKineJacob(SpMatDsptr mat)
{
	DistanceConstraintIqcJc::fillPosKineJacob(mat);
	mat->atandplusFullRow(iG, iqXJ, pGpXJ);
	mat->atandplusFullRow(iG, iqEJ, pGpEJ);
}

void MbD::DistanceConstraintIqcJqc::fillVelICJacob(SpMatDsptr mat)
{
	DistanceConstraintIqcJc::fillVelICJacob(mat);
	mat->atandplusFullRow(iG, iqXJ, pGpXJ);
	mat->atandplusFullColumn(iqXJ, iG, pGpXJ->transpose());
	mat->atandplusFullRow(iG, iqEJ, pGpEJ);
	mat->atandplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}

void MbD::DistanceConstraintIqcJqc::init_distIeJe()
{
	distIeJe = DistIeqcJeqc::With(frmI, frmJ);
}

void MbD::DistanceConstraintIqcJqc::useEquationNumbers()
{
	DistanceConstraintIqcJc::useEquationNumbers();
	auto frmJeqc = std::static_pointer_cast<EndFrameqc>(frmJ);
	iqXJ = frmJeqc->iqX();
	iqEJ = frmJeqc->iqE();
}

void MbD::DistanceConstraintIqcJqc::fillpFpy(SpMatDsptr mat)
{
	DistanceConstraintIqcJc::fillpFpy(mat);
	mat->atandplusFullRow(iG, iqXJ, pGpXJ);
	mat->atandplusFullRow(iG, iqEJ, pGpEJ);
	auto ppGpXIpXJlam = ppGpXIpXJ->times(lam);
	mat->atandplusFullMatrix(iqXI, iqXJ, ppGpXIpXJlam);
	mat->atandplusTransposeFullMatrix(iqXJ, iqXI, ppGpXIpXJlam);
	auto ppGpEIpXJlam = ppGpEIpXJ->times(lam);
	mat->atandplusFullMatrix(iqEI, iqXJ, ppGpEIpXJlam);
	mat->atandplusTransposeFullMatrix(iqXJ, iqEI, ppGpEIpXJlam);
	mat->atandplusFullMatrixtimes(iqXJ, iqXJ, ppGpXJpXJ, lam);
	auto ppGpXIpEJlam = ppGpXIpEJ->times(lam);
	mat->atandplusFullMatrix(iqXI, iqEJ, ppGpXIpEJlam);
	mat->atandplusTransposeFullMatrix(iqEJ, iqXI, ppGpXIpEJlam);
	auto ppGpEIpEJlam = ppGpEIpEJ->times(lam);
	mat->atandplusFullMatrix(iqEI, iqEJ, ppGpEIpEJlam);
	mat->atandplusTransposeFullMatrix(iqEJ, iqEI, ppGpEIpEJlam);
	auto ppGpXJpEJlam = ppGpXJpEJ->times(lam);
	mat->atandplusFullMatrix(iqXJ, iqEJ, ppGpXJpEJlam);
	mat->atandplusTransposeFullMatrix(iqEJ, iqXJ, ppGpXJpEJlam);
	mat->atandplusFullMatrixtimes(iqEJ, iqEJ, ppGpEJpEJ, lam);
}

void MbD::DistanceConstraintIqcJqc::fillpFpydot(SpMatDsptr mat)
{
	DistanceConstraintIqcJc::fillpFpydot(mat);
	mat->atandplusFullColumn(iqXJ, iG, pGpXJ->transpose());
	mat->atandplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}
