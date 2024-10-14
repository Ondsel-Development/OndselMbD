/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "DirectionCosineConstraintIctJqc.h"
#include "DirectionCosineIectJeqc.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<DirectionCosineConstraintIctJqc> MbD::DirectionCosineConstraintIctJqc::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj)
{
	auto inst = std::make_shared<DirectionCosineConstraintIctJqc>(frmi, frmj, axisi, axisj);
	inst->initialize();
	return inst;
}

void DirectionCosineConstraintIctJqc::initaAijIeJe()
{
	aAijIeJe = DirectionCosineIectJeqc::With(efrmI, efrmJ, axisI, axisJ);
}

ConstraintType DirectionCosineConstraintIctJqc::type()
{
	return essential;
}

void DirectionCosineConstraintIctJqc::preVelIC()
{
	DirectionCosineConstraintIJ::preVelIC();
	pGpt = std::static_pointer_cast<DirectionCosineIectJeqc>(aAijIeJe)->pAijIeJept;
}

void DirectionCosineConstraintIctJqc::fillVelICError(FColDsptr col)
{
	col->atminusNumber(iG, pGpt);
}

void DirectionCosineConstraintIctJqc::preAccIC()
{
	DirectionCosineConstraintIJ::preAccIC();
	ppGpEJpt = std::static_pointer_cast<DirectionCosineIectJeqc>(aAijIeJe)->ppAijIeJepEJpt;
	ppGptpt = std::static_pointer_cast<DirectionCosineIectJeqc>(aAijIeJe)->ppAijIeJeptpt;
}

void DirectionCosineConstraintIctJqc::fillAccICIterError(FColDsptr col)
{
	DirectionCosineConstraintIcJqc::fillAccICIterError(col);
	auto efrmJqc = std::static_pointer_cast<EndFrameqc>(efrmJ);
	auto qEdotJ = efrmJqc->qEdot();
	double sum = 0.0;
	sum += (ppGpEJpt->timesFullColumn(qEdotJ)) * 2.0;
	sum += ppGptpt;
	col->atplusNumber(iG, sum);
}
