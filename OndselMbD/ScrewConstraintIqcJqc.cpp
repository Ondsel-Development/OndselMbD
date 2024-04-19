/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "corecrt_math_defines.h"

#include "ScrewConstraintIqcJqc.h"
#include "EndFrameqc.h"
#include "DispCompIeqcJeqcIe.h"
#include "AngleZIeqcJeqc.h"

using namespace MbD;

MbD::ScrewConstraintIqcJqc::ScrewConstraintIqcJqc(EndFrmsptr frmi, EndFrmsptr frmj) : ScrewConstraintIqcJc(frmi, frmj)
{
	pGpXJ = FullRow<double>::With(3);
	pGpEJ = FullRow<double>::With(4);
	ppGpEIpXJ = FullMatrix<double>::With(4, 3);
	ppGpEIpEJ = FullMatrix<double>::With(4, 4);
	ppGpEJpEJ = FullMatrix<double>::With(4, 4);
}

std::shared_ptr<ScrewConstraintIqcJqc> MbD::ScrewConstraintIqcJqc::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
	auto inst = std::make_shared<ScrewConstraintIqcJqc>(frmi, frmj);
	inst->initialize();
	return inst;
}

void MbD::ScrewConstraintIqcJqc::initzIeJeIe()
{
	zIeJeIe = std::make_shared<DispCompIeqcJeqcIe>(frmI, frmJ, 2);
}

void MbD::ScrewConstraintIqcJqc::initthezIeJe()
{
	thezIeJe = std::make_shared<AngleZIeqcJeqc>(frmI, frmJ);
}

void MbD::ScrewConstraintIqcJqc::calc_pGpEJ()
{
	pGpEJ = zIeJeIe->pvaluepEJ()->times(2.0 * OS_M_PI)->minusFullRow(thezIeJe->pvaluepEJ()->times(pitch));
}

void MbD::ScrewConstraintIqcJqc::calc_pGpXJ()
{
	pGpXJ = zIeJeIe->pvaluepXJ()->times(2.0 * OS_M_PI);
}

void MbD::ScrewConstraintIqcJqc::calc_ppGpEIpEJ()
{
	ppGpEIpEJ = zIeJeIe->ppvaluepEIpEJ()->times(2.0 * OS_M_PI)
		->minusFullMatrix(thezIeJe->ppvaluepEIpEJ()->times(pitch));
}

void MbD::ScrewConstraintIqcJqc::calc_ppGpEIpXJ()
{
	ppGpEIpXJ = zIeJeIe->ppvaluepEIpXJ()->times(2.0 * OS_M_PI);
}

void MbD::ScrewConstraintIqcJqc::calc_ppGpEJpEJ()
{
	ppGpEJpEJ = zIeJeIe->ppvaluepEJpEJ()->times(2.0 * OS_M_PI)
			->minusFullMatrix(thezIeJe->ppvaluepEJpEJ()->times(pitch));
}

void MbD::ScrewConstraintIqcJqc::calcPostDynCorrectorIteration()
{
	ScrewConstraintIqcJc::calcPostDynCorrectorIteration();
	calc_pGpXJ();
	calc_pGpEJ();
	calc_ppGpEIpXJ();
	calc_ppGpEIpEJ();
	calc_ppGpEJpEJ();
}

void MbD::ScrewConstraintIqcJqc::fillAccICIterError(FColDsptr col)
{
	ScrewConstraintIqcJc::fillAccICIterError(col);
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

void MbD::ScrewConstraintIqcJqc::fillPosICError(FColDsptr col)
{
	ScrewConstraintIqcJc::fillPosICError(col);
	col->atplusFullVectortimes(iqXJ, pGpXJ, lam);
	col->atplusFullVectortimes(iqEJ, pGpEJ, lam);
}

void MbD::ScrewConstraintIqcJqc::fillPosICJacob(SpMatDsptr mat)
{
	ScrewConstraintIqcJc::fillPosICJacob(mat);
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

void MbD::ScrewConstraintIqcJqc::fillPosKineJacob(SpMatDsptr mat)
{
	ScrewConstraintIqcJc::fillPosKineJacob(mat);
	mat->atandplusFullRow(iG, iqXJ, pGpXJ);
	mat->atandplusFullRow(iG, iqEJ, pGpEJ);
}

void MbD::ScrewConstraintIqcJqc::fillVelICJacob(SpMatDsptr mat)
{
	ScrewConstraintIqcJc::fillVelICJacob(mat);
	mat->atandplusFullRow(iG, iqXJ, pGpXJ);
	mat->atandplusFullColumn(iqXJ, iG, pGpXJ->transpose());
	mat->atandplusFullRow(iG, iqEJ, pGpEJ);
	mat->atandplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}

void MbD::ScrewConstraintIqcJqc::init_zthez()
{
	zIeJeIe = DispCompIeqcJeqcIe::With(frmI, frmJ, 2);
	thezIeJe = AngleZIeqcJeqc::With(frmJ, frmI);
}

void MbD::ScrewConstraintIqcJqc::useEquationNumbers()
{
	ScrewConstraintIqcJc::useEquationNumbers();
	auto frmJeqc = std::static_pointer_cast<EndFrameqc>(frmJ);
	iqXJ = frmJeqc->iqX();
	iqEJ = frmJeqc->iqE();
}

void MbD::ScrewConstraintIqcJqc::fillpFpy(SpMatDsptr mat)
{
	ScrewConstraintIqcJc::fillpFpy(mat);
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

void MbD::ScrewConstraintIqcJqc::fillpFpydot(SpMatDsptr mat)
{
	ScrewConstraintIqcJc::fillpFpydot(mat);
	mat->atandplusFullColumn(iqXJ, iG, pGpXJ->transpose());
	mat->atandplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}
