/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "TranslationConstraintIqcJc.h"
#include "DispCompIeqcJecKeqc.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<TranslationConstraintIqcJc> MbD::TranslationConstraintIqcJc::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi)
{
	auto inst = std::make_shared<TranslationConstraintIqcJc>(frmi, frmj, axisi);
	inst->initialize();
	return inst;
}

void TranslationConstraintIqcJc::initriIeJeIe()
{
	riIeJeIe = DispCompIeqcJecKeqc::With(frmI, frmJ, frmI, axisI);
}

void TranslationConstraintIqcJc::calcPostDynCorrectorIteration()
{
	TranslationConstraintIJ::calcPostDynCorrectorIteration();
	auto riIeqJeIeq = std::static_pointer_cast<DispCompIeqcJecKeqc>(riIeJeIe);
	pGpXI = riIeqJeIeq->pvaluepXI();
	pGpEI = (riIeqJeIeq->pvaluepEI())->plusFullRow(riIeqJeIeq->pvaluepEK());
	ppGpXIpEI = riIeqJeIeq->ppvaluepXIpEK();
	ppGpEIpEI = riIeqJeIeq->ppvaluepEIpEI()
			->plusFullMatrix(riIeqJeIeq->ppvaluepEIpEK())
			->plusFullMatrix((riIeqJeIeq->ppvaluepEIpEK()->
				transpose()->plusFullMatrix(riIeqJeIeq->ppvaluepEKpEK())));
}

void TranslationConstraintIqcJc::useEquationNumbers()
{
	auto frmIeqc = std::static_pointer_cast<EndFrameqc>(frmI);
	iqXI = frmIeqc->iqX();
	iqEI = frmIeqc->iqE();
}

void MbD::TranslationConstraintIqcJc::fillpFpy(SpMatDsptr mat)
{
	mat->atandplusFullRow(iG, iqXI, pGpXI);
	mat->atandplusFullRow(iG, iqEI, pGpEI);
	auto ppGpXIpEIlam = ppGpXIpEI->times(lam);
	mat->atandplusFullMatrix(iqXI, iqEI, ppGpXIpEIlam);
	mat->atandplusTransposeFullMatrix(iqEI, iqXI, ppGpXIpEIlam);
	mat->atandplusFullMatrixtimes(iqEI, iqEI, ppGpEIpEI, lam);
}

void MbD::TranslationConstraintIqcJc::fillpFpydot(SpMatDsptr mat)
{
	mat->atandplusFullColumn(iqXI, iG, pGpXI->transpose());
	mat->atandplusFullColumn(iqEI, iG, pGpEI->transpose());
}

void TranslationConstraintIqcJc::fillPosICError(FColDsptr col)
{
	Constraint::fillPosICError(col);
	col->atplusFullVectortimes(iqXI, pGpXI, lam);
	col->atplusFullVectortimes(iqEI, pGpEI, lam);
}

void TranslationConstraintIqcJc::fillPosICJacob(SpMatDsptr mat)
{
	mat->atandplusFullRow(iG, iqXI, pGpXI);
	mat->atandplusFullColumn(iqXI, iG, pGpXI->transpose());
	mat->atandplusFullRow(iG, iqEI, pGpEI);
	mat->atandplusFullColumn(iqEI, iG, pGpEI->transpose());
	auto ppGpXIpEIlam = ppGpXIpEI->times(lam);
	mat->atandplusFullMatrix(iqXI, iqEI, ppGpXIpEIlam);
	mat->atandplusTransposeFullMatrix(iqEI, iqXI, ppGpXIpEIlam);
	mat->atandplusFullMatrixtimes(iqEI, iqEI, ppGpEIpEI, lam);
}

void TranslationConstraintIqcJc::fillPosKineJacob(SpMatDsptr mat)
{
	mat->atandplusFullRow(iG, iqXI, pGpXI);
	mat->atandplusFullRow(iG, iqEI, pGpEI);
}

void TranslationConstraintIqcJc::fillVelICJacob(SpMatDsptr mat)
{
	mat->atandplusFullRow(iG, iqXI, pGpXI);
	mat->atandplusFullColumn(iqXI, iG, pGpXI->transpose());
	mat->atandplusFullRow(iG, iqEI, pGpEI);
	mat->atandplusFullColumn(iqEI, iG, pGpEI->transpose());
}

void TranslationConstraintIqcJc::fillAccICIterError(FColDsptr col)
{
	col->atplusFullVectortimes(iqXI, pGpXI, lam);
	col->atplusFullVectortimes(iqEI, pGpEI, lam);
	auto efrmIqc = std::static_pointer_cast<EndFrameqc>(frmI);
	auto qXdotI = efrmIqc->qXdot();
	auto qEdotI = efrmIqc->qEdot();
	auto sum = pGpXI->timesFullColumn(efrmIqc->qXddot());
	sum += pGpEI->timesFullColumn(efrmIqc->qEddot());
	sum += 2.0 * (qXdotI->transposeTimesFullColumn(ppGpXIpEI->timesFullColumn(qEdotI)));
	sum += qEdotI->transposeTimesFullColumn(ppGpEIpEI->timesFullColumn(qEdotI));
	col->atplusNumber(iG, sum);
}

void TranslationConstraintIqcJc::addToJointForceI(FColDsptr col)
{
	col->equalSelfPlusFullVectortimes(pGpXI, lam);
}

void TranslationConstraintIqcJc::addToJointTorqueI(FColDsptr jointTorque)
{
	auto cForceT = pGpXI->times(lam);
		auto rIpIeIp = frmI->rpep();
		auto pAOIppEI = frmI->pAOppE();
		auto aBOIp = frmI->aBOp();
		auto fpAOIppEIrIpIeIp = std::make_shared<FullColumn<double>>(4, 0.0);
		for (size_t i = 0; i < 4; i++)
		{
			auto dum = cForceT->timesFullColumn(pAOIppEI->at(i)->timesFullColumn(rIpIeIp));
			fpAOIppEIrIpIeIp->atput(i, dum);
		}
		auto lampGpE = pGpEI->transpose()->times(lam);
		auto c2Torque = aBOIp->timesFullColumn(lampGpE->minusFullColumn(fpAOIppEIrIpIeIp));
		jointTorque->equalSelfPlusFullColumntimes(c2Torque, 0.5);
}
