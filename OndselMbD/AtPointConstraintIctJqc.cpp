/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "AtPointConstraintIctJqc.h"
#include "DispCompIectJeqcO.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<AtPointConstraintIctJqc> MbD::AtPointConstraintIctJqc::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisO)
{
	auto inst = std::make_shared<AtPointConstraintIctJqc>(frmi, frmj, axisO);
	inst->initialize();
	return inst;
}

void AtPointConstraintIctJqc::initializeGlobally()
{
	riIeJeO->initializeGlobally();
	ppGpEJpEJ = std::static_pointer_cast<DispCompIectJeqcO>(riIeJeO)->ppriIeJeOpEJpEJ;
}

void AtPointConstraintIctJqc::initriIeJeO()
{
	riIeJeO = DispCompIectJeqcO::With(efrmI, efrmJ, axis);
}

void AtPointConstraintIctJqc::calcPostDynCorrectorIteration()
{
	AtPointConstraintIcJqc::calcPostDynCorrectorIteration();
}

ConstraintType AtPointConstraintIctJqc::type()
{
	return essential;
}

void AtPointConstraintIctJqc::preVelIC()
{
	AtPointConstraintIcJqc::preVelIC();
	pGpt = std::static_pointer_cast<DispCompIectJeqcO>(riIeJeO)->priIeJeOpt;
}

void AtPointConstraintIctJqc::fillVelICError(FColDsptr col)
{
	col->atminusNumber(iG, pGpt);
}

void AtPointConstraintIctJqc::fillAccICIterError(FColDsptr col)
{
	AtPointConstraintIcJqc::fillAccICIterError(col);
	double sum = ppGptpt;
	col->atplusNumber(iG, sum);
}

void AtPointConstraintIctJqc::preAccIC()
{
	AtPointConstraintIcJqc::preAccIC();
	ppGptpt = std::static_pointer_cast<DispCompIectJeqcO>(riIeJeO)->ppriIeJeOptpt;
}
