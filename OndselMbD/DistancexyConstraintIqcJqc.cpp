/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DistancexyConstraintIqcJqc.h"
#include "EndFrameqc.h"
#include "DispCompIeqcJeqcIe.h"

using namespace MbD;

std::shared_ptr<DistancexyConstraintIqcJqc> MbD::DistancexyConstraintIqcJqc::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
	auto inst = std::make_shared<DistancexyConstraintIqcJqc>(frmi, frmj);
	inst->initialize();
	return inst;
}

void MbD::DistancexyConstraintIqcJqc::calc_pGpXJ()
{
	pGpXJ = (xIeJeIe->pvaluepXJ()->times(xIeJeIe->value())->plusFullRow(yIeJeIe->pvaluepXJ()->times(yIeJeIe->value())));
	pGpXJ->magnifySelf(2.0);
}

void MbD::DistancexyConstraintIqcJqc::calc_pGpEJ()
{
	pGpEJ = (xIeJeIe->pvaluepEJ()->times(xIeJeIe->value())->plusFullRow(yIeJeIe->pvaluepEJ()->times(yIeJeIe->value())));
	pGpEJ->magnifySelf(2.0);
}

void MbD::DistancexyConstraintIqcJqc::calc_ppGpXIpXJ()
{
	//xIeJeIe ppvaluepXIpXJ = 0
	//yIeJeIe ppvaluepXIpXJ = 0
	ppGpXIpXJ = (xIeJeIe->pvaluepXI()->transposeTimesFullRow(xIeJeIe->pvaluepXJ()));
	ppGpXIpXJ = ppGpXIpXJ->plusFullMatrix(yIeJeIe->pvaluepXI()->transposeTimesFullRow(yIeJeIe->pvaluepXJ()));
	ppGpXIpXJ->magnifySelf(2.0);
}

void MbD::DistancexyConstraintIqcJqc::calc_ppGpEIpXJ()
{
	ppGpEIpXJ = (xIeJeIe->pvaluepEI()->transposeTimesFullRow(xIeJeIe->pvaluepXJ()));
	ppGpEIpXJ = ppGpEIpXJ->plusFullMatrix(xIeJeIe->ppvaluepEIpXJ()->times(xIeJeIe->value()));
	ppGpEIpXJ = ppGpEIpXJ->plusFullMatrix(yIeJeIe->pvaluepEI()->transposeTimesFullRow(yIeJeIe->pvaluepXJ()));
	ppGpEIpXJ = ppGpEIpXJ->plusFullMatrix(yIeJeIe->ppvaluepEIpXJ()->times(yIeJeIe->value()));
	ppGpEIpXJ->magnifySelf(2.0);
}

void MbD::DistancexyConstraintIqcJqc::calc_ppGpXJpXJ()
{
	//xIeJeIe ppvaluepXJpXJ = 0
	//yIeJeIe ppvaluepXJpXJ = 0
	ppGpXJpXJ = (xIeJeIe->pvaluepXJ()->transposeTimesFullRow(xIeJeIe->pvaluepXJ()));
	ppGpXJpXJ = ppGpXJpXJ->plusFullMatrix(yIeJeIe->pvaluepXJ()->transposeTimesFullRow(yIeJeIe->pvaluepXJ()));
	ppGpXJpXJ->magnifySelf(2.0);
}

void MbD::DistancexyConstraintIqcJqc::calc_ppGpXIpEJ()
{
	//xIeJeIe ppvaluepXIpEJ = 0
	//yIeJeIe ppvaluepXIpEJ = 0
	ppGpXIpEJ = (xIeJeIe->pvaluepXI()->transposeTimesFullRow(xIeJeIe->pvaluepEJ()));
	ppGpXIpEJ = ppGpXIpEJ->plusFullMatrix(yIeJeIe->pvaluepXI()->transposeTimesFullRow(yIeJeIe->pvaluepEJ()));
	ppGpXIpEJ->magnifySelf(2.0);
}

void MbD::DistancexyConstraintIqcJqc::calc_ppGpEIpEJ()
{
	ppGpEIpEJ = (xIeJeIe->pvaluepEI()->transposeTimesFullRow(xIeJeIe->pvaluepEJ()));
	ppGpEIpEJ = ppGpEIpEJ->plusFullMatrix(xIeJeIe->ppvaluepEIpEJ()->times(xIeJeIe->value()));
	ppGpEIpEJ = ppGpEIpEJ->plusFullMatrix(yIeJeIe->pvaluepEI()->transposeTimesFullRow(yIeJeIe->pvaluepEJ()));
	ppGpEIpEJ = ppGpEIpEJ->plusFullMatrix(yIeJeIe->ppvaluepEIpEJ()->times(yIeJeIe->value()));
	ppGpEIpEJ->magnifySelf(2.0);
}

void MbD::DistancexyConstraintIqcJqc::calc_ppGpXJpEJ()
{
	//xIeJeIe ppvaluepXJpEJ = 0
	//yIeJeIe ppvaluepXJpEJ = 0
	ppGpXJpEJ = (xIeJeIe->pvaluepXJ()->transposeTimesFullRow(xIeJeIe->pvaluepEJ()));
	ppGpXJpEJ = ppGpXJpEJ->plusFullMatrix(yIeJeIe->pvaluepXJ()->transposeTimesFullRow(yIeJeIe->pvaluepEJ()));
	ppGpXJpEJ->magnifySelf(2.0);
}

void MbD::DistancexyConstraintIqcJqc::calc_ppGpEJpEJ()
{
	ppGpEJpEJ = (xIeJeIe->pvaluepEJ()->transposeTimesFullRow(xIeJeIe->pvaluepEJ()));
	ppGpEJpEJ = ppGpEJpEJ->plusFullMatrix(xIeJeIe->ppvaluepEJpEJ()->times(xIeJeIe->value()));
	ppGpEJpEJ = ppGpEJpEJ->plusFullMatrix(yIeJeIe->pvaluepEJ()->transposeTimesFullRow(yIeJeIe->pvaluepEJ()));
	ppGpEJpEJ = ppGpEJpEJ->plusFullMatrix(yIeJeIe->ppvaluepEJpEJ()->times(yIeJeIe->value()));
	ppGpEJpEJ->magnifySelf(2.0);
}

void MbD::DistancexyConstraintIqcJqc::calcPostDynCorrectorIteration()
{
	DistancexyConstraintIqcJc::calcPostDynCorrectorIteration();
	calc_pGpXJ();
	calc_pGpEJ();
	calc_ppGpXIpXJ();
	calc_ppGpEIpXJ();
	calc_ppGpXJpXJ();
	calc_ppGpXIpEJ();
	calc_ppGpEIpEJ();
	calc_ppGpXJpEJ();
	calc_ppGpEJpEJ();
}

void MbD::DistancexyConstraintIqcJqc::fillAccICIterError(FColDsptr col)
{
	DistancexyConstraintIqcJc::fillAccICIterError(col);
	col->atplusFullVectortimes(iqXJ, pGpXJ, lam);
	col->atplusFullVectortimes(iqEJ, pGpEJ, lam);
	auto frmIeqc = std::static_pointer_cast<EndFrameqc>(efrmI);
	auto frmJeqc = std::static_pointer_cast<EndFrameqc>(efrmJ);
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

void MbD::DistancexyConstraintIqcJqc::fillPosICError(FColDsptr col)
{
	DistancexyConstraintIqcJc::fillPosICError(col);
	col->atplusFullVectortimes(iqXJ, pGpXJ, lam);
	col->atplusFullVectortimes(iqEJ, pGpEJ, lam);
}

void MbD::DistancexyConstraintIqcJqc::fillPosICJacob(SpMatDsptr mat)
{
	DistancexyConstraintIqcJc::fillPosICJacob(mat);
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

void MbD::DistancexyConstraintIqcJqc::fillPosKineJacob(SpMatDsptr mat)
{
	DistancexyConstraintIqcJc::fillPosKineJacob(mat);
	mat->atandplusFullRow(iG, iqXJ, pGpXJ);
	mat->atandplusFullRow(iG, iqEJ, pGpEJ);
}

void MbD::DistancexyConstraintIqcJqc::fillVelICJacob(SpMatDsptr mat)
{
	DistancexyConstraintIqcJc::fillVelICJacob(mat);
	mat->atandplusFullRow(iG, iqXJ, pGpXJ);
	mat->atandplusFullColumn(iqXJ, iG, pGpXJ->transpose());
	mat->atandplusFullRow(iG, iqEJ, pGpEJ);
	mat->atandplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}

void MbD::DistancexyConstraintIqcJqc::init_xyIeJeIe()
{
	xIeJeIe = DispCompIeqcJeqcIe::With(efrmI, efrmJ, 0);
	yIeJeIe = DispCompIeqcJeqcIe::With(efrmI, efrmJ, 1);
}

void MbD::DistancexyConstraintIqcJqc::useEquationNumbers()
{
	DistancexyConstraintIqcJc::useEquationNumbers();
	auto frmJeqc = std::static_pointer_cast<EndFrameqc>(efrmJ);
	iqXJ = frmJeqc->iqX();
	iqEJ = frmJeqc->iqE();
}

void MbD::DistancexyConstraintIqcJqc::fillpFpy(SpMatDsptr mat)
{
	DistancexyConstraintIqcJc::fillpFpy(mat);
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

void MbD::DistancexyConstraintIqcJqc::fillpFpydot(SpMatDsptr mat)
{
	DistancexyConstraintIqcJc::fillpFpydot(mat);
	mat->atandplusFullColumn(iqXJ, iG, pGpXJ->transpose());
	mat->atandplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}
