/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselMbD.                                       *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include <corecrt_math_defines.h>

#include "ScrewConstraintIqcJqc.h"
#include "EndFrameqc.h"
#include "CREATE.h"
#include "DispCompIeqcJeqcIe.h"
#include "AngleZIeqcJeqc.h"

using namespace MbD;

MbD::ScrewConstraintIqcJqc::ScrewConstraintIqcJqc(EndFrmsptr frmi, EndFrmsptr frmj) : ScrewConstraintIqcJc(frmi, frmj)
{
}

void MbD::ScrewConstraintIqcJqc::calc_pGpEJ()
{
	pGpEJ = zIeJeIe->pvaluepEJ()->times(2.0 * M_PI)->minusFullRow(thezIeJe->pvaluepEJ()->times(pitch));
}

void MbD::ScrewConstraintIqcJqc::calc_pGpXJ()
{
	pGpXJ = zIeJeIe->pvaluepXJ()->times(2.0 * M_PI)->minusFullRow(thezIeJe->pvaluepXJ()->times(pitch));
}

void MbD::ScrewConstraintIqcJqc::calc_ppGpEIpEJ()
{
	ppGpEIpEJ = zIeJeIe->ppvaluepEIpEJ()->times(2.0 * M_PI)->minusFullMatrix(thezIeJe->ppvaluepEIpEJ()->times(pitch));
}

void MbD::ScrewConstraintIqcJqc::calc_ppGpEIpXJ()
{
	ppGpEIpXJ = zIeJeIe->ppvaluepEIpXJ()->times(2.0 * M_PI)->minusFullMatrix(thezIeJe->ppvaluepEIpXJ()->times(pitch));
}

void MbD::ScrewConstraintIqcJqc::calc_ppGpEJpEJ()
{
	ppGpEJpEJ = zIeJeIe->ppvaluepEJpEJ()->times(2.0 * M_PI)->minusFullMatrix(thezIeJe->ppvaluepEJpEJ()->times(pitch));
}

void MbD::ScrewConstraintIqcJqc::calcPostDynCorrectorIteration()
{
	ScrewConstraintIqcJc::calcPostDynCorrectorIteration();
	this->calc_pGpXJ();
	this->calc_pGpEJ();
	this->calc_ppGpEIpXJ();
	this->calc_ppGpEIpEJ();
	this->calc_ppGpEJpEJ();
}

void MbD::ScrewConstraintIqcJqc::fillAccICIterError(FColDsptr col)
{
	ScrewConstraintIqcJc::fillAccICIterError(col);
	col->atiplusFullVectortimes(iqXJ, pGpXJ, lam);
	col->atiplusFullVectortimes(iqEJ, pGpEJ, lam);
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
	col->atiplusNumber(iG, sum);
}

void MbD::ScrewConstraintIqcJqc::fillPosICError(FColDsptr col)
{
	ScrewConstraintIqcJc::fillPosICError(col);
	col->atiplusFullVectortimes(iqXJ, pGpXJ, lam);
	col->atiplusFullVectortimes(iqEJ, pGpEJ, lam);
}

void MbD::ScrewConstraintIqcJqc::fillPosICJacob(SpMatDsptr mat)
{
	ScrewConstraintIqcJc::fillPosICJacob(mat);
	mat->atijplusFullRow(iG, iqXJ, pGpXJ);
	mat->atijplusFullColumn(iqXJ, iG, pGpXJ->transpose());
	mat->atijplusFullRow(iG, iqEJ, pGpEJ);
	mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
	auto ppGpEIpXJlam = ppGpEIpXJ->times(lam);
	mat->atijplusFullMatrix(iqEI, iqXJ, ppGpEIpXJlam);
	mat->atijplusTransposeFullMatrix(iqXJ, iqEI, ppGpEIpXJlam);
	auto ppGpEIpEJlam = ppGpEIpEJ->times(lam);
	mat->atijplusFullMatrix(iqEI, iqEJ, ppGpEIpEJlam);
	mat->atijplusTransposeFullMatrix(iqEJ, iqEI, ppGpEIpEJlam);
	mat->atijplusFullMatrixtimes(iqEJ, iqEJ, ppGpEJpEJ, lam);
}

void MbD::ScrewConstraintIqcJqc::fillPosKineJacob(SpMatDsptr mat)
{
	ScrewConstraintIqcJc::fillPosKineJacob(mat);
	mat->atijplusFullRow(iG, iqXJ, pGpXJ);
	mat->atijplusFullRow(iG, iqEJ, pGpEJ);
}

void MbD::ScrewConstraintIqcJqc::fillVelICJacob(SpMatDsptr mat)
{
	ScrewConstraintIqcJc::fillVelICJacob(mat);
	mat->atijplusFullRow(iG, iqXJ, pGpXJ);
	mat->atijplusFullColumn(iqXJ, iG, pGpXJ->transpose());
	mat->atijplusFullRow(iG, iqEJ, pGpEJ);
	mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}

void MbD::ScrewConstraintIqcJqc::init_zthez()
{
	zIeJeIe = CREATE<DispCompIeqcJeqcIe>::With(frmI, frmJ, 2);
	thezIeJe = CREATE<AngleZIeqcJeqc>::With(frmJ, frmI);
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
	mat->atijplusFullRow(iG, iqXJ, pGpXJ);
	mat->atijplusFullRow(iG, iqEJ, pGpEJ);
	auto ppGpEIpXJlam = ppGpEIpXJ->times(lam);
	mat->atijplusFullMatrix(iqEI, iqXJ, ppGpEIpXJlam);
	mat->atijplusTransposeFullMatrix(iqXJ, iqEI, ppGpEIpXJlam);
	auto ppGpEIpEJlam = ppGpEIpEJ->times(lam);
	mat->atijplusFullMatrix(iqEI, iqEJ, ppGpEIpEJlam);
	mat->atijplusTransposeFullMatrix(iqEJ, iqEI, ppGpEIpEJlam);
	mat->atijplusFullMatrixtimes(iqEJ, iqEJ, ppGpEJpEJ, lam);
}

void MbD::ScrewConstraintIqcJqc::fillpFpydot(SpMatDsptr mat)
{
	ScrewConstraintIqcJc::fillpFpydot(mat);
	mat->atijplusFullColumn(iqXJ, iG, pGpXJ->transpose());
	mat->atijplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}
