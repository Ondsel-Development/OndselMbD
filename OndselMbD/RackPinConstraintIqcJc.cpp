/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "RackPinConstraintIqcJc.h"
#include "EndFrameqc.h"
#include "AngleZIeqcJec.h"
#include "DispCompIeqcJecIe.h"

using namespace MbD;

std::shared_ptr<RackPinConstraintIqcJc> MbD::RackPinConstraintIqcJc::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
	auto inst = std::make_shared<RackPinConstraintIqcJc>(frmi, frmj);
	inst->initialize();
	return inst;
}

void MbD::RackPinConstraintIqcJc::initialize()
{
	RackPinConstraintIJ::initialize();
	pGpXI = FullRow<double>::With(3);
	pGpEI = FullRow<double>::With(4);
	ppGpXIpEI = FullMatrix<double>::With(3, 4);
	ppGpEIpEI = FullMatrix<double>::With(4, 4);
}

void MbD::RackPinConstraintIqcJc::initxIeJeIe()
{
	xIeJeIe = DispCompIeqcJecIe::With(efrmI, efrmJ, 0);
}

void MbD::RackPinConstraintIqcJc::initthezIeJe()
{
	thezIeJe = AngleZIeqcJec::With(efrmI, efrmJ);
}

void MbD::RackPinConstraintIqcJc::addToJointForceI(FColDsptr col)
{
	col->equalSelfPlusFullVectortimes(pGpXI, lam);
}

void MbD::RackPinConstraintIqcJc::addToJointTorqueI(FColDsptr jointTorque)
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

void MbD::RackPinConstraintIqcJc::calc_pGpEI()
{
	pGpEI = xIeJeIe->pvaluepEI()->plusFullRow(thezIeJe->pvaluepEI()->times(pitchRadius));
}

void MbD::RackPinConstraintIqcJc::calc_pGpXI()
{
	pGpXI = xIeJeIe->pvaluepXI();
}

void MbD::RackPinConstraintIqcJc::calc_ppGpEIpEI()
{
	ppGpEIpEI = xIeJeIe->ppvaluepEIpEI()
			->plusFullMatrix(thezIeJe->ppvaluepEIpEI()->times(pitchRadius));
}

void MbD::RackPinConstraintIqcJc::calc_ppGpXIpEI()
{
	ppGpXIpEI = xIeJeIe->ppvaluepXIpEI();
}

void MbD::RackPinConstraintIqcJc::calcPostDynCorrectorIteration()
{
	RackPinConstraintIJ::calcPostDynCorrectorIteration();
	calc_pGpXI();
	calc_pGpEI();
	calc_ppGpXIpEI();
	calc_ppGpEIpEI();
}

void MbD::RackPinConstraintIqcJc::fillAccICIterError(FColDsptr col)
{
	col->atplusFullVectortimes(iqXI, pGpXI, lam);
	col->atplusFullVectortimes(iqEI, pGpEI, lam);
	auto efrmIqc = std::static_pointer_cast<EndFrameqc>(efrmI);
	auto qXdotI = efrmIqc->qXdot();
	auto qEdotI = efrmIqc->qEdot();
	auto sum = pGpXI->timesFullColumn(efrmIqc->qXddot());
	sum += pGpEI->timesFullColumn(efrmIqc->qEddot());
	sum += 2.0 * (qXdotI->transposeTimesFullColumn(ppGpXIpEI->timesFullColumn(qEdotI)));
	sum += qEdotI->transposeTimesFullColumn(ppGpEIpEI->timesFullColumn(qEdotI));
	col->atplusNumber(iG, sum);
}

void MbD::RackPinConstraintIqcJc::fillPosICError(FColDsptr col)
{
	RackPinConstraintIJ::fillPosICError(col);
	col->atplusFullVectortimes(iqXI, pGpXI, lam);
	col->atplusFullVectortimes(iqEI, pGpEI, lam);
}

void MbD::RackPinConstraintIqcJc::fillPosICJacob(SpMatDsptr mat)
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

void MbD::RackPinConstraintIqcJc::fillPosKineJacob(SpMatDsptr mat)
{
	mat->atandplusFullRow(iG, iqXI, pGpXI);
	mat->atandplusFullRow(iG, iqEI, pGpEI);
}

void MbD::RackPinConstraintIqcJc::fillVelICJacob(SpMatDsptr mat)
{
	mat->atandplusFullRow(iG, iqXI, pGpXI);
	mat->atandplusFullColumn(iqXI, iG, pGpXI->transpose());
	mat->atandplusFullRow(iG, iqEI, pGpEI);
	mat->atandplusFullColumn(iqEI, iG, pGpEI->transpose());
}

void MbD::RackPinConstraintIqcJc::useEquationNumbers()
{
	auto frmIeqc = std::static_pointer_cast<EndFrameqc>(efrmI);
	iqXI = frmIeqc->iqX();
	iqEI = frmIeqc->iqE();
}

void MbD::RackPinConstraintIqcJc::fillpFpy(SpMatDsptr mat)
{
	mat->atandplusFullRow(iG, iqXI, pGpXI);
	mat->atandplusFullRow(iG, iqEI, pGpEI);
	auto ppGpXIpEIlam = ppGpXIpEI->times(lam);
	mat->atandplusFullMatrix(iqXI, iqEI, ppGpXIpEIlam);
	mat->atandplusTransposeFullMatrix(iqEI, iqXI, ppGpXIpEIlam);
	mat->atandplusFullMatrixtimes(iqEI, iqEI, ppGpEIpEI, lam);
}

void MbD::RackPinConstraintIqcJc::fillpFpydot(SpMatDsptr mat)
{
	mat->atandplusFullColumn(iqXI, iG, pGpXI->transpose());
	mat->atandplusFullColumn(iqEI, iG, pGpEI->transpose());
}
