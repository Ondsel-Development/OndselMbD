/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "corecrt_math_defines.h"

#include "ScrewConstraintIqcJc.h"
#include "EndFrameqc.h"
#include "DispCompIeqcJecIe.h"
#include "AngleZIeqcJec.h"

using namespace MbD;

MbD::ScrewConstraintIqcJc::ScrewConstraintIqcJc(EndFrmsptr frmi, EndFrmsptr frmj) : ScrewConstraintIJ(frmi, frmj)
{
	pGpXI = FullRow<double>::With(3);
	pGpEI = FullRow<double>::With(4);
	ppGpXIpEI = FullMatrix<double>::With(3, 4);
	ppGpEIpEI = FullMatrix<double>::With(4, 4);
}

std::shared_ptr<ScrewConstraintIqcJc> MbD::ScrewConstraintIqcJc::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
	auto inst = std::make_shared<ScrewConstraintIqcJc>(frmi, frmj);
	inst->initialize();
	return inst;
}

void MbD::ScrewConstraintIqcJc::initzIeJeIe()
{
	zIeJeIe = std::make_shared<DispCompIeqcJecIe>(frmI, frmJ, 2);
}

void MbD::ScrewConstraintIqcJc::initthezIeJe()
{
	thezIeJe = std::make_shared<AngleZIeqcJec>(frmI, frmJ);
}

void MbD::ScrewConstraintIqcJc::addToJointForceI(FColDsptr col)
{
	col->equalSelfPlusFullVectortimes(pGpXI, lam);
}

void MbD::ScrewConstraintIqcJc::addToJointTorqueI(FColDsptr jointTorque)
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

void MbD::ScrewConstraintIqcJc::calc_pGpEI()
{
	pGpEI = zIeJeIe->pvaluepEI()->times(2.0 * OS_M_PI)->minusFullRow(thezIeJe->pvaluepEI()->times(pitch));
}

void MbD::ScrewConstraintIqcJc::calc_pGpXI()
{
	pGpXI = zIeJeIe->pvaluepXI()->times(2.0 * OS_M_PI);
}

void MbD::ScrewConstraintIqcJc::calc_ppGpEIpEI()
{
	ppGpEIpEI = zIeJeIe->ppvaluepEIpEI()->times(2.0 * OS_M_PI)
		->minusFullMatrix(thezIeJe->ppvaluepEIpEI()->times(pitch));
}

void MbD::ScrewConstraintIqcJc::calc_ppGpXIpEI()
{
	ppGpXIpEI = zIeJeIe->ppvaluepXIpEI()->times(2.0 * OS_M_PI);
}

void MbD::ScrewConstraintIqcJc::calcPostDynCorrectorIteration()
{
	ScrewConstraintIJ::calcPostDynCorrectorIteration();
	calc_pGpXI();
	calc_pGpEI();
	calc_ppGpXIpEI();
	calc_ppGpEIpEI();
}

void MbD::ScrewConstraintIqcJc::fillAccICIterError(FColDsptr col)
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

void MbD::ScrewConstraintIqcJc::fillPosICError(FColDsptr col)
{
	ScrewConstraintIJ::fillPosICError(col);
	col->atplusFullVectortimes(iqXI, pGpXI, lam);
	col->atplusFullVectortimes(iqEI, pGpEI, lam);
}

void MbD::ScrewConstraintIqcJc::fillPosICJacob(SpMatDsptr mat)
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

void MbD::ScrewConstraintIqcJc::fillPosKineJacob(SpMatDsptr mat)
{
	mat->atandplusFullRow(iG, iqXI, pGpXI);
	mat->atandplusFullRow(iG, iqEI, pGpEI);
}

void MbD::ScrewConstraintIqcJc::fillVelICJacob(SpMatDsptr mat)
{
	mat->atandplusFullRow(iG, iqXI, pGpXI);
	mat->atandplusFullColumn(iqXI, iG, pGpXI->transpose());
	mat->atandplusFullRow(iG, iqEI, pGpEI);
	mat->atandplusFullColumn(iqEI, iG, pGpEI->transpose());
}

void MbD::ScrewConstraintIqcJc::init_zthez()
{
	zIeJeIe = DispCompIeqcJecIe::With(frmI, frmJ, 2);
	thezIeJe = AngleZIeqcJec::With(frmJ, frmI);
}

void MbD::ScrewConstraintIqcJc::useEquationNumbers()
{
	auto frmIeqc = std::static_pointer_cast<EndFrameqc>(frmI);
	iqXI = frmIeqc->iqX();
	iqEI = frmIeqc->iqE();
}

void MbD::ScrewConstraintIqcJc::fillpFpy(SpMatDsptr mat)
{
	mat->atandplusFullRow(iG, iqXI, pGpXI);
	mat->atandplusFullRow(iG, iqEI, pGpEI);
	auto ppGpXIpEIlam = ppGpXIpEI->times(lam);
	mat->atandplusFullMatrix(iqXI, iqEI, ppGpXIpEIlam);
	mat->atandplusTransposeFullMatrix(iqEI, iqXI, ppGpXIpEIlam);
	mat->atandplusFullMatrixtimes(iqEI, iqEI, ppGpEIpEI, lam);
}

void MbD::ScrewConstraintIqcJc::fillpFpydot(SpMatDsptr mat)
{
	mat->atandplusFullColumn(iqXI, iG, pGpXI->transpose());
	mat->atandplusFullColumn(iqEI, iG, pGpEI->transpose());
}
