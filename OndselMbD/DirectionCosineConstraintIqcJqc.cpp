/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DirectionCosineConstraintIqcJqc.h"
#include "DirectionCosineIeqcJeqc.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<DirectionCosineConstraintIqcJqc> MbD::DirectionCosineConstraintIqcJqc::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj)
{
	auto inst = std::make_shared<DirectionCosineConstraintIqcJqc>(frmi, frmj, axisi, axisj);
	inst->initialize();
	return inst;
}

void DirectionCosineConstraintIqcJqc::initaAijIeJe()
{
	aAijIeJe = DirectionCosineIeqcJeqc::With(efrmI, efrmJ, axisI, axisJ);
}

void DirectionCosineConstraintIqcJqc::calcPostDynCorrectorIteration()
{
	DirectionCosineConstraintIqcJc::calcPostDynCorrectorIteration();
	auto aAijIeqJqe = std::static_pointer_cast<DirectionCosineIeqcJeqc>(aAijIeJe);
	pGpEJ = aAijIeqJqe->pAijIeJepEJ;
	ppGpEIpEJ = aAijIeqJqe->ppAijIeJepEIpEJ;
	ppGpEJpEJ = aAijIeqJqe->ppAijIeJepEJpEJ;
}

void DirectionCosineConstraintIqcJqc::useEquationNumbers()
{
	DirectionCosineConstraintIqcJc::useEquationNumbers();
	iqEJ = std::static_pointer_cast<EndFrameqc>(efrmJ)->iqE();
}

void MbD::DirectionCosineConstraintIqcJqc::fillpFpy(SpMatDsptr mat)
{
	DirectionCosineConstraintIqcJc::fillpFpy(mat);
	mat->atandplusFullRow(iG, iqEJ, pGpEJ);
	auto ppGpEIpEJlam = ppGpEIpEJ->times(lam);
	mat->atandplusFullMatrix(iqEI, iqEJ, ppGpEIpEJlam);
	mat->atandplusTransposeFullMatrix(iqEJ, iqEI, ppGpEIpEJlam);
	mat->atandplusFullMatrixtimes(iqEJ, iqEJ, ppGpEJpEJ, lam);
}

void MbD::DirectionCosineConstraintIqcJqc::fillpFpydot(SpMatDsptr mat)
{
	DirectionCosineConstraintIqcJc::fillpFpydot(mat);
	mat->atandplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}

void DirectionCosineConstraintIqcJqc::fillPosICError(FColDsptr col)
{
	DirectionCosineConstraintIqcJc::fillPosICError(col);
	col->atplusFullVectortimes(iqEJ, pGpEJ, lam);
}

void DirectionCosineConstraintIqcJqc::fillPosICJacob(SpMatDsptr mat)
{
	DirectionCosineConstraintIqcJc::fillPosICJacob(mat);
	mat->atandplusFullRow(iG, iqEJ, pGpEJ);
	mat->atandplusFullColumn(iqEJ, iG, pGpEJ->transpose());
	auto ppGpEIpEJlam = ppGpEIpEJ->times(lam);
	mat->atandplusFullMatrix(iqEI, iqEJ, ppGpEIpEJlam);
	mat->atandplusTransposeFullMatrix(iqEJ, iqEI, ppGpEIpEJlam);
	mat->atandplusFullMatrixtimes(iqEJ, iqEJ, ppGpEJpEJ, lam);
}

void DirectionCosineConstraintIqcJqc::fillPosKineJacob(SpMatDsptr mat)
{
	DirectionCosineConstraintIqcJc::fillPosKineJacob(mat);
	mat->atandplusFullRow(iG, iqEJ, pGpEJ);
}

void DirectionCosineConstraintIqcJqc::fillVelICJacob(SpMatDsptr mat)
{
	DirectionCosineConstraintIqcJc::fillVelICJacob(mat);
	mat->atandplusFullRow(iG, iqEJ, pGpEJ);
	mat->atandplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}

void DirectionCosineConstraintIqcJqc::fillAccICIterError(FColDsptr col)
{
	DirectionCosineConstraintIqcJc::fillAccICIterError(col);
	col->atplusFullVectortimes(iqEJ, pGpEJ, lam);
	auto efrmIqc = std::static_pointer_cast<EndFrameqc>(efrmI);
	auto efrmJqc = std::static_pointer_cast<EndFrameqc>(efrmJ);
	auto qEdotI = efrmIqc->qEdot();
	auto qEdotJ = efrmJqc->qEdot();
	double sum = pGpEJ->timesFullColumn(efrmJqc->qEddot());
	sum += (qEdotI->transposeTimesFullColumn(ppGpEIpEJ->timesFullColumn(qEdotJ))) * 2.0;
	sum += qEdotJ->transposeTimesFullColumn(ppGpEJpEJ->timesFullColumn(qEdotJ));
	col->atplusNumber(iG, sum);
}
