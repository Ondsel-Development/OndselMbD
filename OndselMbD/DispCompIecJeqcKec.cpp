/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "DispCompIecJeqcKec.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<DispCompIecJeqcKec> MbD::DispCompIecJeqcKec::With(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk, size_t axisk)
{
	auto inst = std::make_shared<DispCompIecJeqcKec>(frmi, frmj, frmk, axisk);
	inst->initialize();
	return inst;
}

void DispCompIecJeqcKec::initialize()
{
	DispCompIecJecKec::initialize();
	priIeJeKepXJ = FullRow<double>::With(3);
	priIeJeKepEJ = FullRow<double>::With(4);
	ppriIeJeKepEJpEJ = FullMatrix<double>::With(4, 4);
}

void DispCompIecJeqcKec::calcPostDynCorrectorIteration()
{
	DispCompIecJecKec::calcPostDynCorrectorIteration();
	auto frmJqc = std::static_pointer_cast<EndFrameqc>(efrmJ);
	auto prIeJeOpEJT = frmJqc->prOeOpE->transpose();
	auto& pprIeJeOpEJpEJ = frmJqc->pprOeOpEpE;
	for (size_t i = 0; i < 3; i++)
	{
		priIeJeKepXJ->atput(i, aAjOKe->at(i));
	}
	for (size_t i = 0; i < 4; i++)
	{
		priIeJeKepEJ->atput(i, aAjOKe->dot(prIeJeOpEJT->at(i)));
	}
	for (size_t i = 0; i < 4; i++)
	{
		auto& pprIeJeOpEJipEJ = pprIeJeOpEJpEJ->at(i);
		auto& ppriIeJeKepEJipEJ = ppriIeJeKepEJpEJ->at(i);
		ppriIeJeKepEJipEJ->atput(i, aAjOKe->dot(pprIeJeOpEJipEJ->at(i)));
		for (size_t j = 0; j < 4; j++)
		{
			auto ppriIeJeKepEJipEJj = (aAjOKe->dot(pprIeJeOpEJipEJ->at(j)));
			ppriIeJeKepEJipEJ->atput(j, ppriIeJeKepEJipEJj);
			ppriIeJeKepEJpEJ->atandput(j, i, ppriIeJeKepEJipEJj);
		}
	}
}

FRowDsptr DispCompIecJeqcKec::pvaluepXJ()
{
	return priIeJeKepXJ;
}

FRowDsptr DispCompIecJeqcKec::pvaluepEJ()
{
	return priIeJeKepEJ;
}

FMatDsptr DispCompIecJeqcKec::ppvaluepEJpEJ()
{
	return ppriIeJeKepEJpEJ;
}
