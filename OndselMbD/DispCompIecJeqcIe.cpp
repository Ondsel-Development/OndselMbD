/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "DispCompIecJeqcIe.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<DispCompIecJeqcIe> MbD::DispCompIecJeqcIe::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axis)
{
	auto inst = std::make_shared<DispCompIecJeqcIe>(frmi, frmj, axis);
	inst->initialize();
	return inst;
}

void MbD::DispCompIecJeqcIe::initialize()
{
	DispCompIecJecIe::initialize();
	priIeJeIepXJ = FullRow<double>::With(3);
	priIeJeIepEJ = FullRow<double>::With(4);
	ppriIeJeIepXJpEJ = FullMatrix<double>::With(3, 4);
	ppriIeJeIepEJpEJ = FullMatrix<double>::With(4, 4);
}

void MbD::DispCompIecJeqcIe::calc_ppvaluepEJpEJ()
{
	auto frmIeqc = std::static_pointer_cast<EndFrameqc>(efrmI);
	auto mprIeJeOpEJT = frmIeqc->prOeOpE->transpose();
	auto mpprIeJeOpEJpEJ = frmIeqc->pprOeOpEpE;
	for (size_t i = 0; i < 4; i++)
	{
		auto ppAjOIepEJipEJ = ppAjOIepEJpEJ->at(i);
		auto mpprIeJeOpEJipEJ = mpprIeJeOpEJpEJ->at(i);
		auto ppriIeJeIepEJipEJ = ppriIeJeIepEJpEJ->at(i);
		for (size_t j = i; j < 4; j++)
		{
			auto term1 = ppAjOIepEJipEJ->at(j)->dot(rIeJeO);
			auto mterm2 = pAjOIepEJT->at(i)->dot(mprIeJeOpEJT->at(j));
			auto mterm3 = (i == j) ? mterm2 : pAjOIepEJT->at(j)->dot(mprIeJeOpEJT->at(i));
			auto mterm4 = aAjOIe->dot(mpprIeJeOpEJipEJ->at(j));
			ppriIeJeIepEJipEJ->atput(j, term1 - mterm2 - mterm3 - mterm4);
		}
	}
	ppriIeJeIepEJpEJ->symLowerWithUpper();
}

void MbD::DispCompIecJeqcIe::calc_ppvaluepXJpEJ()
{
	for (size_t i = 0; i < 3; i++)
	{
		auto ppriIeJeIepXJipEJ = ppriIeJeIepXJpEJ->at(i);
		for (size_t j = 0; j < 4; j++)
		{
			ppriIeJeIepXJipEJ->atput(j, -pAjOIepEJT->at(j)->at(i));
		}
	}
}

void MbD::DispCompIecJeqcIe::calc_pvaluepEJ()
{
	auto frmIeqc = std::static_pointer_cast<EndFrameqc>(efrmI);
	pAjOIepEJT = frmIeqc->pAjOepET(axis);
	auto mprIeJeOpEJT = frmIeqc->prOeOpE->transpose();
	for (size_t i = 0; i < 4; i++)
	{
		priIeJeIepEJ->atput(i, pAjOIepEJT->at(i)->dot(rIeJeO) - aAjOIe->dot(mprIeJeOpEJT->at(i)));
	}
}

void MbD::DispCompIecJeqcIe::calc_pvaluepXJ()
{
	for (size_t i = 0; i < 3; i++)
	{
		priIeJeIepXJ->atput(i, -aAjOIe->at(i));
	}
}

void MbD::DispCompIecJeqcIe::calcPostDynCorrectorIteration()
{
	//Must maintain order of calc_xxx.
	DispCompIecJecIe::calcPostDynCorrectorIteration();
	calc_pvaluepXJ();
	calc_pvaluepEJ();
	calc_ppvaluepXJpEJ();
	calc_ppvaluepEJpEJ();
}

void MbD::DispCompIecJeqcIe::initializeGlobally()
{
	auto frmIeqc = std::static_pointer_cast<EndFrameqc>(efrmI);
	ppAjOIepEJpEJ = frmIeqc->ppAjOepEpE(axis);
}

FMatDsptr MbD::DispCompIecJeqcIe::ppvaluepEJpEJ()
{
	return ppriIeJeIepEJpEJ;
}

FMatDsptr MbD::DispCompIecJeqcIe::ppvaluepXJpEJ()
{
	return ppriIeJeIepXJpEJ;
}

FRowDsptr MbD::DispCompIecJeqcIe::pvaluepEJ()
{
	return priIeJeIepEJ;
}

FRowDsptr MbD::DispCompIecJeqcIe::pvaluepXJ()
{
	return priIeJeIepXJ;
}
