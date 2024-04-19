/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "RackPinConstraintIqcJqc.h"
#include "EndFrameqc.h"
#include "DispCompIeqcJeqcIe.h"
#include "AngleZIeqcJeqc.h"

using namespace MbD;

MbD::RackPinConstraintIqcJqc::RackPinConstraintIqcJqc(EndFrmsptr frmi, EndFrmsptr frmj) : RackPinConstraintIqcJc(frmi, frmj)
{
	pGpXJ = FullRow<double>::With(3);
	pGpEJ = FullRow<double>::With(4);
	ppGpEIpXJ = FullMatrix<double>::With(4, 3);
	ppGpEIpEJ = FullMatrix<double>::With(4, 4);
	ppGpEJpEJ = FullMatrix<double>::With(4, 4);
}

std::shared_ptr<RackPinConstraintIqcJqc> MbD::RackPinConstraintIqcJqc::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
	auto inst = std::make_shared<RackPinConstraintIqcJqc>(frmi, frmj);
	inst->initialize();
	return inst;
}

void MbD::RackPinConstraintIqcJqc::initxIeJeIe()
{
	xIeJeIe = std::make_shared<DispCompIeqcJeqcIe>(frmI, frmJ, 0);
}

void MbD::RackPinConstraintIqcJqc::initthezIeJe()
{
	thezIeJe = std::make_shared<AngleZIeqcJeqc>(frmI, frmJ);
}

void MbD::RackPinConstraintIqcJqc::calc_pGpEJ()
{
	pGpEJ = xIeJeIe->pvaluepEJ()->plusFullRow(thezIeJe->pvaluepEJ()->times(pitchRadius));
}

void MbD::RackPinConstraintIqcJqc::calc_pGpXJ()
{
	pGpXJ = xIeJeIe->pvaluepXJ();
}

void MbD::RackPinConstraintIqcJqc::calc_ppGpEIpEJ()
{
	ppGpEIpEJ = xIeJeIe->ppvaluepEIpEJ()
			->plusFullMatrix(thezIeJe->ppvaluepEIpEJ()->times(pitchRadius));
}

void MbD::RackPinConstraintIqcJqc::calc_ppGpEIpXJ()
{
	ppGpEIpXJ = xIeJeIe->ppvaluepEIpXJ();
}

void MbD::RackPinConstraintIqcJqc::calc_ppGpEJpEJ()
{
	ppGpEJpEJ = xIeJeIe->ppvaluepEJpEJ()
			->plusFullMatrix(thezIeJe->ppvaluepEJpEJ()->times(pitchRadius));
}

void MbD::RackPinConstraintIqcJqc::calcPostDynCorrectorIteration()
{
	RackPinConstraintIqcJc::calcPostDynCorrectorIteration();
	calc_pGpXJ();
	calc_pGpEJ();
	calc_ppGpEIpXJ();
	calc_ppGpEIpEJ();
	calc_ppGpEJpEJ();
}

void MbD::RackPinConstraintIqcJqc::fillAccICIterError(FColDsptr col)
{
	RackPinConstraintIqcJc::fillAccICIterError(col);
	col->atplusFullVectortimes(iqXJ, pGpXJ, lam);
	col->atplusFullVectortimes(iqEJ, pGpEJ, lam);
	auto frmIeqc = std::static_pointer_cast<EndFrameqc>(frmI);
	auto frmJeqc = std::static_pointer_cast<EndFrameqc>(frmJ);
	auto qEdotI = frmIeqc->qEdot();
	auto qXdotJ = frmJeqc->qXdot();
	auto qEdotJ = frmJeqc->qEdot();
	double sum = 0.0;
	sum += pGpXJ->timesFullColumn(frmJeqc->qXddot());
	sum += pGpEJ->timesFullColumn(frmJeqc->qEddot());
	sum += 2.0 * (qEdotI->transposeTimesFullColumn(ppGpEIpXJ->timesFullColumn(qXdotJ)));
	sum += 2.0 * (qEdotI->transposeTimesFullColumn(ppGpEIpEJ->timesFullColumn(qEdotJ)));
	sum += qEdotJ->transposeTimesFullColumn(ppGpEJpEJ->timesFullColumn(qEdotJ));
	col->atplusNumber(iG, sum);
}

void MbD::RackPinConstraintIqcJqc::fillPosICError(FColDsptr col)
{
	RackPinConstraintIqcJc::fillPosICError(col);
	col->atplusFullVectortimes(iqXJ, pGpXJ, lam);
	col->atplusFullVectortimes(iqEJ, pGpEJ, lam);
}

void MbD::RackPinConstraintIqcJqc::fillPosICJacob(SpMatDsptr mat)
{
	RackPinConstraintIqcJc::fillPosICJacob(mat);
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

void MbD::RackPinConstraintIqcJqc::fillPosKineJacob(SpMatDsptr mat)
{
	RackPinConstraintIqcJc::fillPosKineJacob(mat);
	mat->atandplusFullRow(iG, iqXJ, pGpXJ);
	mat->atandplusFullRow(iG, iqEJ, pGpEJ);
}

void MbD::RackPinConstraintIqcJqc::fillVelICJacob(SpMatDsptr mat)
{
	RackPinConstraintIqcJc::fillVelICJacob(mat);
	mat->atandplusFullRow(iG, iqXJ, pGpXJ);
	mat->atandplusFullColumn(iqXJ, iG, pGpXJ->transpose());
	mat->atandplusFullRow(iG, iqEJ, pGpEJ);
	mat->atandplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}

void MbD::RackPinConstraintIqcJqc::init_xthez()
{
	xIeJeIe = DispCompIeqcJeqcIe::With(frmI, frmJ, 0);
	thezIeJe = AngleZIeqcJeqc::With(frmJ, frmI);
}

void MbD::RackPinConstraintIqcJqc::useEquationNumbers()
{
	RackPinConstraintIqcJc::useEquationNumbers();
	auto frmJeqc = std::static_pointer_cast<EndFrameqc>(frmJ);
	iqXJ = frmJeqc->iqX();
	iqEJ = frmJeqc->iqE();
}

void MbD::RackPinConstraintIqcJqc::fillpFpy(SpMatDsptr mat)
{
	RackPinConstraintIqcJc::fillpFpy(mat);
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

void MbD::RackPinConstraintIqcJqc::fillpFpydot(SpMatDsptr mat)
{
	RackPinConstraintIqcJc::fillpFpydot(mat);
	mat->atandplusFullColumn(iqXJ, iG, pGpXJ->transpose());
	mat->atandplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}
