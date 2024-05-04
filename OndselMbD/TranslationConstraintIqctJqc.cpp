/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "TranslationConstraintIqctJqc.h"
#include "DispCompIeqctJeqcKeqct.h"

using namespace MbD;

std::shared_ptr<TranslationConstraintIqctJqc> MbD::TranslationConstraintIqctJqc::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi)
{
	auto inst = std::make_shared<TranslationConstraintIqctJqc>(frmi, frmj, axisi);
	inst->initialize();
	return inst;
}

void TranslationConstraintIqctJqc::initriIeJeIe()
{
	riIeJeIe = DispCompIeqctJeqcKeqct::With(efrmI, efrmJ, efrmI, axisI);
}

ConstraintType TranslationConstraintIqctJqc::type()
{
	return essential;
}

void TranslationConstraintIqctJqc::preVelIC()
{
	TranslationConstraintIJ::preVelIC();
	pGpt = std::static_pointer_cast<DispCompIeqctJeqcKeqct>(riIeJeIe)->pvaluept();
}

void TranslationConstraintIqctJqc::fillVelICError(FColDsptr col)
{
	col->atminusNumber(iG, pGpt);
}

void TranslationConstraintIqctJqc::preAccIC()
{
	TranslationConstraintIJ::preAccIC();
	auto riIeJeIeqct = std::static_pointer_cast<DispCompIeqctJeqcKeqct>(riIeJeIe);
	ppGpXIpt = riIeJeIeqct->ppvaluepXIpt();
	ppGpEIpt = riIeJeIeqct->ppvaluepEIpt()->plusFullRow(riIeJeIeqct->ppvaluepEKpt());
	ppGpXJpt = riIeJeIeqct->ppvaluepXJpt();
	ppGpEJpt = riIeJeIeqct->ppvaluepEJpt();
	ppGptpt = riIeJeIeqct->ppvalueptpt();
}

void TranslationConstraintIqctJqc::fillAccICIterError(FColDsptr col)
{
	TranslationConstraintIqcJqc::fillAccICIterError(col);
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
