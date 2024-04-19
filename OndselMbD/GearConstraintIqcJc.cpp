/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "GearConstraintIqcJc.h"
#include "EndFrameqc.h"
#include "OrbitAngleZIeqcJec.h"

using namespace MbD;

MbD::GearConstraintIqcJc::GearConstraintIqcJc(EndFrmsptr frmi, EndFrmsptr frmj) : GearConstraintIJ(frmi, frmj)
{
	assert(false);
}

std::shared_ptr<GearConstraintIqcJc> MbD::GearConstraintIqcJc::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
	auto inst = std::make_shared<GearConstraintIqcJc>(frmi, frmj);
	inst->initialize();
	return inst;
}

void MbD::GearConstraintIqcJc::addToJointForceI(FColDsptr col)
{
	col->equalSelfPlusFullVectortimes(pGpXI, lam);
}

void MbD::GearConstraintIqcJc::addToJointTorqueI(FColDsptr jointTorque)
{
	auto cForceT = pGpXI->times(lam);
	auto frmIeqc = std::static_pointer_cast<EndFrameqc>(frmI);
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

void MbD::GearConstraintIqcJc::calc_pGpEI()
{
	pGpEI = orbitJeIe->pvaluepEJ()->plusFullRow(orbitIeJe->pvaluepEI()->times(this->ratio()));
}

void MbD::GearConstraintIqcJc::calc_pGpXI()
{
	pGpXI = orbitJeIe->pvaluepXJ()->plusFullRow(orbitIeJe->pvaluepXI()->times(this->ratio()));
}

void MbD::GearConstraintIqcJc::calc_ppGpEIpEI()
{
	ppGpEIpEI = orbitJeIe->ppvaluepEJpEJ()->plusFullMatrix(orbitIeJe->ppvaluepEIpEI()->times(this->ratio()));
}

void MbD::GearConstraintIqcJc::calc_ppGpXIpEI()
{
	ppGpXIpEI = orbitJeIe->ppvaluepXJpEJ()->plusFullMatrix(orbitIeJe->ppvaluepXIpEI()->times(this->ratio()));
}

void MbD::GearConstraintIqcJc::calc_ppGpXIpXI()
{
	ppGpXIpXI = orbitJeIe->ppvaluepXJpXJ()->plusFullMatrix(orbitIeJe->ppvaluepXIpXI()->times(this->ratio()));
}

void MbD::GearConstraintIqcJc::calcPostDynCorrectorIteration()
{
	GearConstraintIJ::calcPostDynCorrectorIteration();
	calc_pGpXI();
	calc_pGpEI();
	calc_ppGpXIpXI();
	calc_ppGpXIpEI();
	calc_ppGpEIpEI();
}

void MbD::GearConstraintIqcJc::fillAccICIterError(FColDsptr col)
{
	col->atplusFullVectortimes(iqXI, pGpXI, lam);
	col->atplusFullVectortimes(iqEI, pGpEI, lam);
	auto efrmIqc = std::static_pointer_cast<EndFrameqc>(frmI);
	auto qXdotI = efrmIqc->qXdot();
	auto qEdotI = efrmIqc->qEdot();
	auto sum = pGpXI->timesFullColumn(efrmIqc->qXddot());
	sum += pGpEI->timesFullColumn(efrmIqc->qEddot());
	sum += qXdotI->transposeTimesFullColumn(ppGpXIpXI->timesFullColumn(qXdotI));
	sum += 2.0 * (qXdotI->transposeTimesFullColumn(ppGpXIpEI->timesFullColumn(qEdotI)));
	sum += qEdotI->transposeTimesFullColumn(ppGpEIpEI->timesFullColumn(qEdotI));
	col->atplusNumber(iG, sum);
}

void MbD::GearConstraintIqcJc::fillPosICError(FColDsptr col)
{
	GearConstraintIJ::fillPosICError(col);
	col->atplusFullVectortimes(iqXI, pGpXI, lam);
	col->atplusFullVectortimes(iqEI, pGpEI, lam);
}

void MbD::GearConstraintIqcJc::fillPosICJacob(SpMatDsptr mat)
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

void MbD::GearConstraintIqcJc::fillPosKineJacob(SpMatDsptr mat)
{
	mat->atandplusFullRow(iG, iqXI, pGpXI);
	mat->atandplusFullRow(iG, iqEI, pGpEI);
}

void MbD::GearConstraintIqcJc::fillVelICJacob(SpMatDsptr mat)
{
	mat->atandplusFullRow(iG, iqXI, pGpXI);
	mat->atandplusFullColumn(iqXI, iG, pGpXI->transpose());
	mat->atandplusFullRow(iG, iqEI, pGpEI);
	mat->atandplusFullColumn(iqEI, iG, pGpEI->transpose());
}

void MbD::GearConstraintIqcJc::initorbitsIJ()
{
	orbitIeJe = OrbitAngleZIeqcJec::With(frmI, frmJ);
	orbitJeIe = OrbitAngleZIeqcJec::With(frmJ, frmI);
}

void MbD::GearConstraintIqcJc::useEquationNumbers()
{
	auto frmIeqc = std::static_pointer_cast<EndFrameqc>(frmI);
	iqXI = frmIeqc->iqX();
	iqEI = frmIeqc->iqE();
}

void MbD::GearConstraintIqcJc::fillpFpy(SpMatDsptr mat)
{
	mat->atandplusFullRow(iG, iqXI, pGpXI);
	mat->atandplusFullRow(iG, iqEI, pGpEI);
	mat->atandplusFullMatrixtimes(iqXI, iqXI, ppGpXIpXI, lam);
	auto ppGpXIpEIlam = ppGpXIpEI->times(lam);
	mat->atandplusFullMatrix(iqXI, iqEI, ppGpXIpEIlam);
	mat->atandplusTransposeFullMatrix(iqEI, iqXI, ppGpXIpEIlam);
	mat->atandplusFullMatrixtimes(iqEI, iqEI, ppGpEIpEI, lam);
}

void MbD::GearConstraintIqcJc::fillpFpydot(SpMatDsptr mat)
{
	mat->atandplusFullColumn(iqXI, iG, pGpXI->transpose());
	mat->atandplusFullColumn(iqEI, iG, pGpEI->transpose());
}
