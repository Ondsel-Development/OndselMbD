/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "DirectionCosineConstraintIcJqc.h"
#include "DirectionCosineIecJeqc.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<DirectionCosineConstraintIcJqc> MbD::DirectionCosineConstraintIcJqc::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj)
{
	auto inst = std::make_shared<DirectionCosineConstraintIcJqc>(frmi, frmj, axisi, axisj);
	inst->initialize();
	return inst;
}

void DirectionCosineConstraintIcJqc::initaAijIeJe()
{
	aAijIeJe = DirectionCosineIecJeqc::With(efrmI, efrmJ, axisI, axisJ);
}

void DirectionCosineConstraintIcJqc::calcPostDynCorrectorIteration()
{
	DirectionCosineConstraintIJ::calcPostDynCorrectorIteration();
	auto aAijIeqJqe = std::static_pointer_cast<DirectionCosineIecJeqc>(aAijIeJe);
	pGpEJ = aAijIeqJqe->pAijIeJepEJ;
	ppGpEJpEJ = aAijIeqJqe->ppAijIeJepEJpEJ;
}

void DirectionCosineConstraintIcJqc::useEquationNumbers()
{
	DirectionCosineConstraintIJ::useEquationNumbers();
	iqEJ = std::static_pointer_cast<EndFrameqc>(efrmJ)->iqE();
}

void MbD::DirectionCosineConstraintIcJqc::fillpFpy(SpMatDsptr mat)
{
	DirectionCosineConstraintIJ::fillpFpy(mat);
	mat->atandplusFullRow(iG, iqEJ, pGpEJ);
	mat->atandplusFullMatrixtimes(iqEJ, iqEJ, ppGpEJpEJ, lam);
}

void MbD::DirectionCosineConstraintIcJqc::fillpFpydot(SpMatDsptr mat)
{
	DirectionCosineConstraintIJ::fillpFpydot(mat);
	mat->atandplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}

void DirectionCosineConstraintIcJqc::fillPosICError(FColDsptr col)
{
	DirectionCosineConstraintIJ::fillPosICError(col);
	col->atplusFullVectortimes(iqEJ, pGpEJ, lam);
}

void DirectionCosineConstraintIcJqc::fillPosICJacob(SpMatDsptr mat)
{
	DirectionCosineConstraintIJ::fillPosICJacob(mat);
	mat->atandplusFullRow(iG, iqEJ, pGpEJ);
	mat->atandplusFullColumn(iqEJ, iG, pGpEJ->transpose());
	mat->atandplusFullMatrixtimes(iqEJ, iqEJ, ppGpEJpEJ, lam);
}

void DirectionCosineConstraintIcJqc::fillPosKineJacob(SpMatDsptr mat)
{
	DirectionCosineConstraintIJ::fillPosKineJacob(mat);
	mat->atandplusFullRow(iG, iqEJ, pGpEJ);
}

void DirectionCosineConstraintIcJqc::fillVelICJacob(SpMatDsptr mat)
{
	DirectionCosineConstraintIJ::fillVelICJacob(mat);
	mat->atandplusFullRow(iG, iqEJ, pGpEJ);
	mat->atandplusFullColumn(iqEJ, iG, pGpEJ->transpose());
}

void DirectionCosineConstraintIcJqc::fillAccICIterError(FColDsptr col)
{
	DirectionCosineConstraintIJ::fillAccICIterError(col);
	col->atplusFullVectortimes(iqEJ, pGpEJ, lam);
	auto efrmJqc = std::static_pointer_cast<EndFrameqc>(efrmJ);
	auto qEdotJ = efrmJqc->qEdot();
	double sum = pGpEJ->timesFullColumn(efrmJqc->qEddot());
	sum += qEdotJ->transposeTimesFullColumn(ppGpEJpEJ->timesFullColumn(qEdotJ));
	col->atplusNumber(iG, sum);
}
