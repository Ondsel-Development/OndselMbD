/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "TranslationConstraintIctJqc.h"
#include "DispCompIeqctJeqcKeqct.h"

using namespace MbD;

std::shared_ptr<TranslationConstraintIctJqc> MbD::TranslationConstraintIctJqc::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi)
{
	auto inst = std::make_shared<TranslationConstraintIctJqc>(frmi, frmj, axisi);
	inst->initialize();
	return inst;
}

void TranslationConstraintIctJqc::initriIeJeIe()
{
	riIeJeIe = DispCompIeqctJeqcKeqct::With(efrmI, efrmJ, efrmI, axisI);
}

ConstraintType TranslationConstraintIctJqc::type()
{
	return essential;
}

void TranslationConstraintIctJqc::preVelIC()
{
	TranslationConstraintIJ::preVelIC();
	pGpt = std::static_pointer_cast<DispCompIeqctJeqcKeqct>(riIeJeIe)->pvaluept();
}

void TranslationConstraintIctJqc::fillVelICError(FColDsptr col)
{
	col->atminusNumber(iG, pGpt);
}

void TranslationConstraintIctJqc::preAccIC()
{
	TranslationConstraintIJ::preAccIC();
	auto riIeJeIeqct = std::static_pointer_cast<DispCompIeqctJeqcKeqct>(riIeJeIe);
	ppGpXIpt = riIeJeIeqct->ppvaluepXIpt();
	ppGpEIpt = riIeJeIeqct->ppvaluepEIpt()->plusFullRow(riIeJeIeqct->ppvaluepEKpt());
	ppGpXJpt = riIeJeIeqct->ppvaluepXJpt();
	ppGpEJpt = riIeJeIeqct->ppvaluepEJpt();
	ppGptpt = riIeJeIeqct->ppvalueptpt();
}

void TranslationConstraintIctJqc::fillAccICIterError(FColDsptr col)
{
	TranslationConstraintIcJqc::fillAccICIterError(col);
	auto efrmIqc = std::static_pointer_cast<EndFrameqc>(efrmI);
	auto efrmJqc = std::static_pointer_cast<EndFrameqc>(efrmJ);
	auto qXdotI = efrmIqc->qXdot();
	auto qEdotI = efrmIqc->qEdot();
	auto qXdotJ = efrmJqc->qXdot();
	auto qEdotJ = efrmJqc->qEdot();
	double sum = 2.0 * ppGpXIpt->timesFullColumn(qXdotI);
	sum += 2.0 * ppGpEIpt->timesFullColumn(qEdotI);
	sum += 2.0 * ppGpXJpt->timesFullColumn(qXdotJ);
	sum += 2.0 * ppGpEJpt->timesFullColumn(qEdotJ);
	sum += ppGptpt;
	col->atplusNumber(iG, sum);
}
