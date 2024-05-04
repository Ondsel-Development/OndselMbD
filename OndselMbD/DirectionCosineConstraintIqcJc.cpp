/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DirectionCosineConstraintIqcJc.h"
#include "DirectionCosineIeqcJec.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<DirectionCosineConstraintIqcJc> MbD::DirectionCosineConstraintIqcJc::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj)
{
	auto inst = std::make_shared<DirectionCosineConstraintIqcJc>(frmi, frmj, axisi, axisj);
	inst->initialize();
	return inst;
}

void DirectionCosineConstraintIqcJc::initaAijIeJe()
{
	aAijIeJe = DirectionCosineIeqcJec::With(efrmI, efrmJ, axisI, axisJ);
}

void DirectionCosineConstraintIqcJc::calcPostDynCorrectorIteration()
{
	DirectionCosineConstraintIJ::calcPostDynCorrectorIteration();
	auto aAijIeqJe = std::static_pointer_cast<DirectionCosineIeqcJec>(aAijIeJe);
	pGpEI = aAijIeqJe->pAijIeJepEI;
	ppGpEIpEI = aAijIeqJe->ppAijIeJepEIpEI;
}

void DirectionCosineConstraintIqcJc::useEquationNumbers()
{
	iqEI = std::static_pointer_cast<EndFrameqc>(efrmI)->iqE();
}

void MbD::DirectionCosineConstraintIqcJc::fillpFpy(SpMatDsptr mat)
{
	mat->atandplusFullRow(iG, iqEI, pGpEI);
	mat->atandplusFullMatrixtimes(iqEI, iqEI, ppGpEIpEI, lam);
}


void MbD::DirectionCosineConstraintIqcJc::fillpFpydot(SpMatDsptr mat)
{
	mat->atandplusFullColumn(iqEI, iG, pGpEI->transpose());
}

void DirectionCosineConstraintIqcJc::fillPosICError(FColDsptr col)
{
	Constraint::fillPosICError(col);
	col->atplusFullVectortimes(iqEI, pGpEI, lam);
}

void DirectionCosineConstraintIqcJc::fillPosICJacob(SpMatDsptr mat)
{
	mat->atandplusFullRow(iG, iqEI, pGpEI);
	mat->atandplusFullColumn(iqEI, iG, pGpEI->transpose());
	mat->atandplusFullMatrixtimes(iqEI, iqEI, ppGpEIpEI, lam);
}

void DirectionCosineConstraintIqcJc::fillPosKineJacob(SpMatDsptr mat)
{
	mat->atandplusFullRow(iG, iqEI, pGpEI);
}

void DirectionCosineConstraintIqcJc::fillVelICJacob(SpMatDsptr mat)
{
	mat->atandplusFullRow(iG, iqEI, pGpEI);
	mat->atandplusFullColumn(iqEI, iG, pGpEI->transpose());
}

void DirectionCosineConstraintIqcJc::fillAccICIterError(FColDsptr col)
{
	col->atplusFullVector(iqEI, pGpEI->times(lam));
	auto efrmIqc = std::static_pointer_cast<EndFrameqc>(efrmI);
	auto qEdotI = efrmIqc->qEdot();
	auto sum = pGpEI->timesFullColumn(efrmIqc->qEddot());
	sum += qEdotI->transposeTimesFullColumn(ppGpEIpEI->timesFullColumn(qEdotI));
	col->atplusNumber(iG, sum);
}

void DirectionCosineConstraintIqcJc::addToJointTorqueI(FColDsptr jointTorque)
{
	auto aBOIp = efrmI->aBOp();
	auto lampGpE = pGpEI->transpose()->times(lam);
	auto c2Torque = aBOIp->timesFullColumn(lampGpE);
	jointTorque->equalSelfPlusFullColumntimes(c2Torque, 0.5);
}
