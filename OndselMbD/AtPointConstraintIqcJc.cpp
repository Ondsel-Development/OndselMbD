/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "AtPointConstraintIqcJc.h"
#include "DispCompIeqcJecO.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<AtPointConstraintIqcJc> MbD::AtPointConstraintIqcJc::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisO)
{
	auto inst = std::make_shared<AtPointConstraintIqcJc>(frmi, frmj, axisO);
	inst->initialize();
	return inst;
}

void AtPointConstraintIqcJc::initializeGlobally()
{
	AtPointConstraintIJ::initializeGlobally();
	ppGpEIpEI = (std::static_pointer_cast<DispCompIeqcJecO>(riIeJeO))->ppriIeJeOpEIpEI;
}

void AtPointConstraintIqcJc::initriIeJeO()
{
	riIeJeO = DispCompIeqcJecO::With(efrmI, efrmJ, axis);
}

void AtPointConstraintIqcJc::calcPostDynCorrectorIteration()
{
	AtPointConstraintIJ::calcPostDynCorrectorIteration();
	pGpEI = std::static_pointer_cast<DispCompIeqcJecO>(riIeJeO)->priIeJeOpEI;
}

void AtPointConstraintIqcJc::useEquationNumbers()
{
	auto frmIeqc = std::static_pointer_cast<EndFrameqc>(efrmI);
	iqXIminusOnePlusAxis = frmIeqc->iqX() + axis;
	iqEI = frmIeqc->iqE();
}

void MbD::AtPointConstraintIqcJc::fillpFpy(SpMatDsptr mat)
{
	mat->atandplusNumber(iG, iqXIminusOnePlusAxis, -1.0);
	mat->atandplusFullRow(iG, iqEI, pGpEI);
	mat->atandplusFullMatrixtimes(iqEI, iqEI, ppGpEIpEI, lam);
}

void MbD::AtPointConstraintIqcJc::fillpFpydot(SpMatDsptr mat)
{
	mat->atandplusNumber(iqXIminusOnePlusAxis, iG, -1.0);
	mat->atandplusFullColumn(iqEI, iG, pGpEI->transpose());
}

void AtPointConstraintIqcJc::fillPosICError(FColDsptr col)
{
	Constraint::fillPosICError(col);
	col->atminusNumber(iqXIminusOnePlusAxis, lam);
	col->atplusFullVectortimes(iqEI, pGpEI, lam);
}

void AtPointConstraintIqcJc::fillPosICJacob(SpMatDsptr mat)
{
	mat->atandplusNumber(iG, iqXIminusOnePlusAxis, -1.0);
	mat->atandplusNumber(iqXIminusOnePlusAxis, iG, -1.0);
	mat->atandplusFullRow(iG, iqEI, pGpEI);
	mat->atandplusFullColumn(iqEI, iG, pGpEI->transpose());
	mat->atandplusFullMatrixtimes(iqEI, iqEI, ppGpEIpEI, lam);
}

void AtPointConstraintIqcJc::fillPosKineJacob(SpMatDsptr mat)
{
	mat->atandplusNumber(iG, iqXIminusOnePlusAxis, -1.0);
	mat->atandplusFullRow(iG, iqEI, pGpEI);
}

void AtPointConstraintIqcJc::fillVelICJacob(SpMatDsptr mat)
{
	mat->atandplusNumber(iG, iqXIminusOnePlusAxis, -1.0);
	mat->atandplusNumber(iqXIminusOnePlusAxis, iG, -1.0);
	mat->atandplusFullRow(iG, iqEI, pGpEI);
	mat->atandplusFullColumn(iqEI, iG, pGpEI->transpose());
}

void AtPointConstraintIqcJc::fillAccICIterError(FColDsptr col)
{
	col->atminusNumber(iqXIminusOnePlusAxis, lam);
	col->atplusFullVectortimes(iqEI, pGpEI, lam);
	auto efrmIqc = std::static_pointer_cast<EndFrameqc>(efrmI);
	auto qEdotI = efrmIqc->qEdot();
	auto sum = -efrmIqc->qXddot()->at(axis);
	sum += pGpEI->timesFullColumn(efrmIqc->qEddot());
	sum += qEdotI->transposeTimesFullColumn(ppGpEIpEI->timesFullColumn(qEdotI));
	col->atplusNumber(iG, sum);
}

void AtPointConstraintIqcJc::addToJointForceI(FColDsptr col)
{
	col->atminusNumber(axis, lam);
}

void AtPointConstraintIqcJc::addToJointTorqueI(FColDsptr jointTorque)
{
	auto cForceT = FullRow<double>::With(3, 0.0);
	cForceT->atput(axis, -lam);
	auto efrmqc = std::static_pointer_cast<EndFrameqc>(efrmI);
	auto rIpIeIp = efrmqc->rpep();
	auto pAOIppEI = efrmqc->pAOppE();
	auto aBOIp = efrmqc->aBOp();
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
