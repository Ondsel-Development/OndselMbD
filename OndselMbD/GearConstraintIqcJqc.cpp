/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "GearConstraintIqcJqc.h"
#include "EndFrameqc.h"
#include "OrbitAngleZIeqcJeqc.h"

using namespace MbD;

MbD::GearConstraintIqcJqc::GearConstraintIqcJqc(EndFrmsptr frmi, EndFrmsptr frmj) : GearConstraintIqcJc(frmi, frmj)
{
	assert(false);
}

std::shared_ptr<GearConstraintIqcJqc> MbD::GearConstraintIqcJqc::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
	auto inst = std::make_shared<GearConstraintIqcJqc>(frmi, frmj);
	inst->initialize();
	return inst;
}

void MbD::GearConstraintIqcJqc::calc_pGpEJ()
{
	pGpEJ = orbitJeIe->pvaluepEI()->plusFullRow(orbitIeJe->pvaluepEJ()->times(this->ratio()));
}

void MbD::GearConstraintIqcJqc::calc_pGpXJ()
{
	pGpXJ = orbitJeIe->pvaluepXI()->plusFullRow(orbitIeJe->pvaluepXJ()->times(this->ratio()));
}

void MbD::GearConstraintIqcJqc::calc_ppGpEIpEJ()
{
	ppGpEIpEJ = orbitJeIe->ppvaluepEIpEJ()->transpose()->plusFullMatrix(orbitIeJe->ppvaluepEIpEJ()->times(this->ratio()));
}

void MbD::GearConstraintIqcJqc::calc_ppGpEIpXJ()
{
	ppGpEIpXJ = orbitJeIe->ppvaluepXIpEJ()->transpose()->plusFullMatrix(orbitIeJe->ppvaluepEIpXJ()->times(this->ratio()));
}

void MbD::GearConstraintIqcJqc::calc_ppGpEJpEJ()
{
	ppGpEJpEJ = orbitJeIe->ppvaluepEIpEI()->plusFullMatrix(orbitIeJe->ppvaluepEJpEJ()->times(this->ratio()));
}

void MbD::GearConstraintIqcJqc::calc_ppGpXIpEJ()
{
	ppGpXIpEJ = orbitJeIe->ppvaluepEIpXJ()->transpose()->plusFullMatrix(orbitIeJe->ppvaluepXIpEJ()->times(this->ratio()));
}

void MbD::GearConstraintIqcJqc::calc_ppGpXIpXJ()
{
	ppGpXIpXJ = orbitJeIe->ppvaluepXIpXJ()->transpose()->plusFullMatrix(orbitIeJe->ppvaluepXIpXJ()->times(this->ratio()));
}

void MbD::GearConstraintIqcJqc::calc_ppGpXJpEJ()
{
	ppGpXJpEJ = orbitJeIe->ppvaluepXIpEI()->plusFullMatrix(orbitIeJe->ppvaluepXJpEJ()->times(this->ratio()));
}

void MbD::GearConstraintIqcJqc::calc_ppGpXJpXJ()
{
	ppGpXJpXJ = orbitJeIe->ppvaluepXIpXI()->plusFullMatrix(orbitIeJe->ppvaluepXJpXJ()->times(this->ratio()));
}

void MbD::GearConstraintIqcJqc::calcPostDynCorrectorIteration()
{
	GearConstraintIqcJc::calcPostDynCorrectorIteration();
	calc_pGpXJ();
	calc_pGpEJ();
	calc_ppGpXIpXJ();
	calc_ppGpXIpEJ();
	calc_ppGpEIpXJ();
	calc_ppGpEIpEJ();
	calc_ppGpXJpXJ();
	calc_ppGpXJpEJ();
	calc_ppGpEJpEJ();
}

void MbD::GearConstraintIqcJqc::fillAccICIterError(FColDsptr col)
{
	GearConstraintIqcJc::fillAccICIterError(col);
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

void MbD::GearConstraintIqcJqc::fillPosICError(FColDsptr col)
{
	GearConstraintIqcJc::fillPosICError(col);
	col->atplusFullVectortimes(iqXJ, pGpXJ, lam);
	col->atplusFullVectortimes(iqEJ, pGpEJ, lam);
}

void MbD::GearConstraintIqcJqc::fillPosICJacob(SpMatDsptr mat)
{
	GearConstraintIqcJc::fillPosICJacob(mat);
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

void MbD::GearConstraintIqcJqc::fillPosKineJacob(SpMatDsptr mat)
{
	GearConstraintIqcJc::fillPosKineJacob(mat);
	mat->atandplusFullRow(iG, iqXJ, pGpXJ);
	mat->atandplusFullRow(iG, iqEJ, pGpEJ);
}

void MbD::GearConstraintIqcJqc::fillVelICJacob(SpMatDsptr mat)
{
	GearConstraintIqcJc::fillVelICJacob(mat);
	mat->atandplusFullRow(iG, iqXJ, pGpXJ);
	mat->atandplusFullColumn(iqXJ, iG, pGpXJ->transpose());
	mat->atandplusFullRow(iG, iqEJ, pGpEJ);
	mat->atandplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}

void MbD::GearConstraintIqcJqc::initorbitsIJ()
{
	orbitIeJe = OrbitAngleZIeqcJeqc::With(frmI, frmJ);
	orbitJeIe = OrbitAngleZIeqcJeqc::With(frmJ, frmI);
}

void MbD::GearConstraintIqcJqc::useEquationNumbers()
{
	GearConstraintIqcJc::useEquationNumbers();
	auto frmJeqc = std::static_pointer_cast<EndFrameqc>(frmJ);
	iqXJ = frmJeqc->iqX();
	iqEJ = frmJeqc->iqE();
}

void MbD::GearConstraintIqcJqc::fillpFpy(SpMatDsptr mat)
{
	GearConstraintIqcJc::fillpFpy(mat);
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

void MbD::GearConstraintIqcJqc::fillpFpydot(SpMatDsptr mat)
{
	GearConstraintIqcJc::fillpFpydot(mat);
	mat->atandplusFullColumn(iqXJ, iG, pGpXJ->transpose());
	mat->atandplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}
