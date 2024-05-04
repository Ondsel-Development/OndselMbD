/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "AtPointConstraintIqctJqc.h"
#include "DispCompIeqctJeqcO.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<AtPointConstraintIqctJqc> MbD::AtPointConstraintIqctJqc::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisO)
{
	auto inst = std::make_shared<AtPointConstraintIqctJqc>(frmi, frmj, axisO);
	inst->initialize();
	return inst;
}

void AtPointConstraintIqctJqc::initializeGlobally()
{
	riIeJeO->initializeGlobally();
	ppGpEJpEJ = std::static_pointer_cast<DispCompIeqctJeqcO>(riIeJeO)->ppriIeJeOpEJpEJ;
}

void AtPointConstraintIqctJqc::initriIeJeO()
{
	riIeJeO = DispCompIeqctJeqcO::With(efrmI, efrmJ, axis);
}

void AtPointConstraintIqctJqc::calcPostDynCorrectorIteration()
{
	//"ppGpEIpEI is no longer constant."

	ppGpEIpEI = std::static_pointer_cast<DispCompIeqctJeqcO>(riIeJeO)->ppriIeJeOpEIpEI;
	AtPointConstraintIqcJqc::calcPostDynCorrectorIteration();
}

ConstraintType AtPointConstraintIqctJqc::type()
{
	return essential;
}

void AtPointConstraintIqctJqc::preVelIC()
{
	AtPointConstraintIqcJqc::preVelIC();
	pGpt = std::static_pointer_cast<DispCompIeqctJeqcO>(riIeJeO)->priIeJeOpt;
}

void AtPointConstraintIqctJqc::fillVelICError(FColDsptr col)
{
	col->atminusNumber(iG, pGpt);
}

void AtPointConstraintIqctJqc::fillAccICIterError(FColDsptr col)
{
	AtPointConstraintIqcJqc::fillAccICIterError(col);
	auto efrmIqc = std::static_pointer_cast<EndFrameqc>(efrmI);
	auto qEdotI = efrmIqc->qEdot();
	double sum = (ppGpEIpt->timesFullColumn(qEdotI)) * 2.0;
	sum += ppGptpt;
	col->atplusNumber(iG, sum);
}

void AtPointConstraintIqctJqc::preAccIC()
{
	AtPointConstraintIqcJqc::preAccIC();
	ppGpEIpt = std::static_pointer_cast<DispCompIeqctJeqcO>(riIeJeO)->ppriIeJeOpEIpt;
	ppGptpt = std::static_pointer_cast<DispCompIeqctJeqcO>(riIeJeO)->ppriIeJeOptpt;
}
