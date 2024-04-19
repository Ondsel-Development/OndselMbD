/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "AngleZIeqcJec.h"

using namespace MbD;

MbD::AngleZIeqcJec::AngleZIeqcJec(EndFrmsptr frmi, EndFrmsptr frmj) : AngleZIecJec(frmi, frmj)
{
	pthezpEI = FullRow<double>::With(4);
	ppthezpEIpEI = FullMatrix<double>::With(4, 4);
}

std::shared_ptr<AngleZIeqcJec> MbD::AngleZIeqcJec::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
	auto inst = std::make_shared<AngleZIeqcJec>(frmi, frmj);
	inst->initialize();
	return inst;
}

void MbD::AngleZIeqcJec::initialize()
{
	AngleZIecJec::initialize();
	pthezpEI = FullRow<double>::With(4);
	ppthezpEIpEI = FullMatrix<double>::With(4, 4);
}

void MbD::AngleZIeqcJec::calcPostDynCorrectorIteration()
{
	AngleZIecJec::calcPostDynCorrectorIteration();
	pcthezpEI = aA00IeJe->pvaluepEI();
	psthezpEI = aA10IeJe->pvaluepEI();
	auto ppcthezpEIpEI = aA00IeJe->ppvaluepEIpEI();
	auto ppsthezpEIpEI = aA10IeJe->ppvaluepEIpEI();
	for (size_t i = 0; i < 4; i++)
	{
		pthezpEI->atput(i, (psthezpEI->at(i)) * cosOverSSq - ((pcthezpEI->at(i)) * sinOverSSq));
	}
	for (size_t i = 0; i < 4; i++)
	{
		auto ppthezpEIpEIi = ppthezpEIpEI->at(i);
		auto ppcthezpEIpEIi = ppcthezpEIpEI->at(i);
		auto ppsthezpEIpEIi = ppsthezpEIpEI->at(i);
		auto pcthezpEIi = pcthezpEI->at(i);
		auto psthezpEIi = psthezpEI->at(i);
		auto term1 = (pcthezpEIi * pcthezpEIi - (psthezpEIi * psthezpEIi)) * twoCosSinOverSSqSq;
		auto term2 = ppsthezpEIpEIi->at(i) * cosOverSSq - (ppcthezpEIpEIi->at(i) * sinOverSSq);
		auto term3 = (psthezpEIi * pcthezpEIi + (pcthezpEIi * psthezpEIi)) * dSqOverSSqSq;
		ppthezpEIpEIi->atput(i, term1 + term2 + term3);
		for (size_t j = i + 1; j < 4; j++)
		{
			auto pcthezpEIj = pcthezpEI->at(j);
			auto psthezpEIj = psthezpEI->at(j);
			auto term1 = (pcthezpEIi * pcthezpEIj - (psthezpEIi * psthezpEIj)) * twoCosSinOverSSqSq;
			auto term2 = ppsthezpEIpEIi->at(j) * cosOverSSq - (ppcthezpEIpEIi->at(j) * sinOverSSq);
			auto term3 = (psthezpEIi * pcthezpEIj + (pcthezpEIi * psthezpEIj)) * dSqOverSSqSq;
			auto ppthezpEIpEIij = term1 + term2 + term3;
			ppthezpEIpEIi->atput(j, ppthezpEIpEIij);
			ppthezpEIpEI->atandput(j, i, ppthezpEIpEIij);
		}
	}
}

void MbD::AngleZIeqcJec::init_aAijIeJe()
{
	aA00IeJe = DirectionCosineIeqcJec::With(frmI, frmJ, 0, 0);
	aA10IeJe = DirectionCosineIeqcJec::With(frmI, frmJ, 1, 0);
}

FMatDsptr MbD::AngleZIeqcJec::ppvaluepEIpEI()
{
	return ppthezpEIpEI;
}

FRowDsptr MbD::AngleZIeqcJec::pvaluepEI()
{
	return pthezpEI;
}
