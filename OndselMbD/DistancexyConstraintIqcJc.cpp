/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DistancexyConstraintIqcJc.h"
//#include "EndFramec.h"
#include "DispCompIeqcJecIe.h"

using namespace MbD;

std::shared_ptr<DistancexyConstraintIqcJc> MbD::DistancexyConstraintIqcJc::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
	auto inst = std::make_shared<DistancexyConstraintIqcJc>(frmi, frmj);
	inst->initialize();
	return inst;
}

void MbD::DistancexyConstraintIqcJc::addToJointForceI(FColDsptr col)
{
	col->equalSelfPlusFullVectortimes(pGpXI, lam);
}

void MbD::DistancexyConstraintIqcJc::addToJointTorqueI(FColDsptr jointTorque)
{
	auto cForceT = pGpXI->times(lam);
	auto frmIeqc = std::static_pointer_cast<EndFrameqc>(efrmI);
	auto rIpIeIp = frmIeqc->rpep();
	auto pAOIppEI = frmIeqc->pAOppE();
	auto aBOIp = frmIeqc->aBOp();
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

void MbD::DistancexyConstraintIqcJc::calcPostDynCorrectorIteration()
{
	DistancexyConstraintIJ::calcPostDynCorrectorIteration();
	calc_pGpXI();
	calc_pGpEI();
	calc_ppGpXIpXI();
	calc_ppGpXIpEI();
	calc_ppGpEIpEI();
}

void MbD::DistancexyConstraintIqcJc::calc_pGpEI()
{
	pGpEI = (xIeJeIe->pvaluepEI()->times(xIeJeIe->value())->plusFullRow(yIeJeIe->pvaluepEI()->times(yIeJeIe->value())));
	pGpEI->magnifySelf(2.0);
}

void MbD::DistancexyConstraintIqcJc::calc_pGpXI()
{
	pGpXI = (xIeJeIe->pvaluepXI()->times(xIeJeIe->value())->plusFullRow(yIeJeIe->pvaluepXI()->times(yIeJeIe->value())));
	pGpXI->magnifySelf(2.0);
}

void MbD::DistancexyConstraintIqcJc::calc_ppGpEIpEI()
{
	ppGpEIpEI = (xIeJeIe->pvaluepEI()->transposeTimesFullRow(xIeJeIe->pvaluepEI()));
	ppGpEIpEI = ppGpEIpEI->plusFullMatrix(xIeJeIe->ppvaluepEIpEI()->times(xIeJeIe->value()));
	ppGpEIpEI = ppGpEIpEI->plusFullMatrix(yIeJeIe->pvaluepEI()->transposeTimesFullRow(yIeJeIe->pvaluepEI()));
	ppGpEIpEI = ppGpEIpEI->plusFullMatrix(yIeJeIe->ppvaluepEIpEI()->times(yIeJeIe->value()));
	ppGpEIpEI->magnifySelf(2.0);
}

void MbD::DistancexyConstraintIqcJc::calc_ppGpXIpEI()
{
	ppGpXIpEI = (xIeJeIe->pvaluepXI()->transposeTimesFullRow(xIeJeIe->pvaluepEI()));
	ppGpXIpEI = ppGpXIpEI->plusFullMatrix(xIeJeIe->ppvaluepXIpEI()->times(xIeJeIe->value()));
	ppGpXIpEI = ppGpXIpEI->plusFullMatrix(yIeJeIe->pvaluepXI()->transposeTimesFullRow(yIeJeIe->pvaluepEI()));
	ppGpXIpEI = ppGpXIpEI->plusFullMatrix(yIeJeIe->ppvaluepXIpEI()->times(yIeJeIe->value()));
	ppGpXIpEI->magnifySelf(2.0);
}

void MbD::DistancexyConstraintIqcJc::calc_ppGpXIpXI()
{
	//xIeJeIe ppvaluepXIpXI = 0
	//yIeJeIe ppvaluepXIpXI = 0
	ppGpXIpXI = (xIeJeIe->pvaluepXI()->transposeTimesFullRow(xIeJeIe->pvaluepXI()));
	ppGpXIpXI = ppGpXIpXI->plusFullMatrix(yIeJeIe->pvaluepXI()->transposeTimesFullRow(yIeJeIe->pvaluepXI()));
	ppGpXIpXI->magnifySelf(2.0);
}

void MbD::DistancexyConstraintIqcJc::init_xyIeJeIe()
{
	xIeJeIe = DispCompIeqcJecIe::With(efrmI, efrmJ, 0);
	yIeJeIe = DispCompIeqcJecIe::With(efrmI, efrmJ, 1);
}

void MbD::DistancexyConstraintIqcJc::fillAccICIterError(FColDsptr col)
{
	col->atplusFullVectortimes(iqXI, pGpXI, lam);
	col->atplusFullVectortimes(iqEI, pGpEI, lam);
	auto efrmIqc = std::static_pointer_cast<EndFrameqc>(efrmI);
	auto qXdotI = efrmIqc->qXdot();
	auto qEdotI = efrmIqc->qEdot();
	auto sum = pGpXI->timesFullColumn(efrmIqc->qXddot());
	sum += pGpEI->timesFullColumn(efrmIqc->qEddot());
	sum += qXdotI->transposeTimesFullColumn(ppGpXIpXI->timesFullColumn(qXdotI));
	sum += 2.0 * (qXdotI->transposeTimesFullColumn(ppGpXIpEI->timesFullColumn(qEdotI)));
	sum += qEdotI->transposeTimesFullColumn(ppGpEIpEI->timesFullColumn(qEdotI));
	col->atplusNumber(iG, sum);
}

void MbD::DistancexyConstraintIqcJc::fillPosICError(FColDsptr col)
{
	DistancexyConstraintIJ::fillPosICError(col);
	col->atplusFullVectortimes(iqXI, pGpXI, lam);
	col->atplusFullVectortimes(iqEI, pGpEI, lam);
}

void MbD::DistancexyConstraintIqcJc::fillPosICJacob(SpMatDsptr mat)
{
	mat->atandplusFullRow(iG, iqXI, pGpXI);
	mat->atandplusFullColumn(iqXI, iG, pGpXI->transpose());
	mat->atandplusFullRow(iG, iqEI, pGpEI);
	mat->atandplusFullColumn(iqEI, iG, pGpEI->transpose());
	mat->atandplusFullMatrixtimes(iqXI, iqXI, ppGpXIpXI, lam);
	auto ppGpXIpEIlam = ppGpXIpEI->times(lam);
	mat->atandplusFullMatrix(iqXI, iqEI, ppGpXIpEIlam);
	mat->atandplusTransposeFullMatrix(iqEI, iqXI, ppGpXIpEIlam);
	mat->atandplusFullMatrixtimes(iqEI, iqEI, ppGpEIpEI, lam);
}

void MbD::DistancexyConstraintIqcJc::fillPosKineJacob(SpMatDsptr mat)
{
	mat->atandplusFullRow(iG, iqXI, pGpXI);
	mat->atandplusFullRow(iG, iqEI, pGpEI);
}

void MbD::DistancexyConstraintIqcJc::fillVelICJacob(SpMatDsptr mat)
{
	mat->atandplusFullRow(iG, iqXI, pGpXI);
	mat->atandplusFullColumn(iqXI, iG, pGpXI->transpose());
	mat->atandplusFullRow(iG, iqEI, pGpEI);
	mat->atandplusFullColumn(iqEI, iG, pGpEI->transpose());
}

void MbD::DistancexyConstraintIqcJc::useEquationNumbers()
{
	auto frmIeqc = std::static_pointer_cast<EndFrameqc>(efrmI);
	iqXI = frmIeqc->iqX();
	iqEI = frmIeqc->iqE();
}

void MbD::DistancexyConstraintIqcJc::fillpFpy(SpMatDsptr mat)
{
	mat->atandplusFullRow(iG, iqXI, pGpXI);
	mat->atandplusFullRow(iG, iqEI, pGpEI);
	mat->atandplusFullMatrixtimes(iqXI, iqXI, ppGpXIpXI, lam);
	auto ppGpXIpEIlam = ppGpXIpEI->times(lam);
	mat->atandplusFullMatrix(iqXI, iqEI, ppGpXIpEIlam);
	mat->atandplusTransposeFullMatrix(iqEI, iqXI, ppGpXIpEIlam);
	mat->atandplusFullMatrixtimes(iqEI, iqEI, ppGpEIpEI, lam);
}

void MbD::DistancexyConstraintIqcJc::fillpFpydot(SpMatDsptr mat)
{
	mat->atandplusFullColumn(iqXI, iG, pGpXI->transpose());
	mat->atandplusFullColumn(iqEI, iG, pGpEI->transpose());
}
