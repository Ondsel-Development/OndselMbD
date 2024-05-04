/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "OrbitAngleZIeqcJeqc.h"
#include "DispCompIeqcJeqcIe.h"

using namespace MbD;

std::shared_ptr<OrbitAngleZIeqcJeqc> MbD::OrbitAngleZIeqcJeqc::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
	auto inst = std::make_shared<OrbitAngleZIeqcJeqc>(frmi, frmj);
	inst->initialize();
	return inst;
}

void MbD::OrbitAngleZIeqcJeqc::initialize()
{
	OrbitAngleZIeqcJec::initialize();
	pthezpXJ = FullRow<double>::With(3);
	pthezpEJ = FullRow<double>::With(4);
	ppthezpXIpXJ = FullMatrix<double>::With(3, 3);
	ppthezpXIpEJ = FullMatrix<double>::With(3, 4);
	ppthezpEIpXJ = FullMatrix<double>::With(4, 3);
	ppthezpEIpEJ = FullMatrix<double>::With(4, 4);
	ppthezpXJpXJ = FullMatrix<double>::With(3, 3);
	ppthezpXJpEJ = FullMatrix<double>::With(3, 4);
	ppthezpEJpEJ = FullMatrix<double>::With(4, 4);
}

void MbD::OrbitAngleZIeqcJeqc::calc_ppthezpEIpEJ()
{
	auto pxpEI = xIeJeIe->pvaluepEI();
	auto pypEI = yIeJeIe->pvaluepEI();
	auto pxpEJ = xIeJeIe->pvaluepEJ();
	auto pypEJ = yIeJeIe->pvaluepEJ();
	auto ppxpEIpEJ = xIeJeIe->ppvaluepEIpEJ();
	auto ppypEIpEJ = yIeJeIe->ppvaluepEIpEJ();
	for (size_t i = 0; i < 4; i++)
	{
		auto ppthezpEIpEJi = ppthezpEIpEJ->at(i);
		auto ppxpEIpEJi = ppxpEIpEJ->at(i);
		auto ppypEIpEJi = ppypEIpEJ->at(i);
		auto pxpEIi = pxpEI->at(i);
		auto pypEIi = pypEI->at(i);
		for (size_t j = 0; j < 4; j++)
		{
			auto pxpEJj = pxpEJ->at(j);
			auto pypEJj = pypEJ->at(j);
			auto term1 = (pxpEIi * pxpEJj - (pypEIi * pypEJj)) * twoCosSinOverSSqSq;
			auto term2 = ppypEIpEJi->at(j) * cosOverSSq - (ppxpEIpEJi->at(j) * sinOverSSq);
			auto term3 = (pypEIi * pxpEJj + (pxpEIi * pypEJj)) * dSqOverSSqSq;
			ppthezpEIpEJi->atput(j, term1 + term2 + term3);
		}
	}
}

void MbD::OrbitAngleZIeqcJeqc::calc_ppthezpEIpXJ()
{
	//ppxpEIpXJ = 0
	//ppypEIpXJ = 0

	auto pxpEI = xIeJeIe->pvaluepEI();
	auto pypEI = yIeJeIe->pvaluepEI();
	auto pxpXJ = xIeJeIe->pvaluepXJ();
	auto pypXJ = yIeJeIe->pvaluepXJ();
	for (size_t i = 0; i < 4; i++)
	{
		auto ppthezpEIpXJi = ppthezpEIpXJ->at(i);
		auto pxpEIi = pxpEI->at(i);
		auto pypEIi = pypEI->at(i);
		for (size_t j = 0; j < 3; j++)
		{
			auto pxpXJj = pxpXJ->at(j);
			auto pypXJj = pypXJ->at(j);
			auto term1 = (pxpEIi * pxpXJj - (pypEIi * pypXJj)) * twoCosSinOverSSqSq;
			auto term3 = (pypEIi * pxpXJj + (pxpEIi * pypXJj)) * dSqOverSSqSq;
			ppthezpEIpXJi->atput(j, term1 + term3);
		}
	}
}

void MbD::OrbitAngleZIeqcJeqc::calc_ppthezpEJpEJ()
{
	auto pxpEJ = xIeJeIe->pvaluepEJ();
	auto pypEJ = yIeJeIe->pvaluepEJ();
	auto ppxpEJpEJ = xIeJeIe->ppvaluepEJpEJ();
	auto ppypEJpEJ = yIeJeIe->ppvaluepEJpEJ();
	for (size_t i = 0; i < 4; i++)
	{
		auto ppthezpEJpEJi = ppthezpEJpEJ->at(i);
		auto ppxpEJpEJi = ppxpEJpEJ->at(i);
		auto ppypEJpEJi = ppypEJpEJ->at(i);
		auto pxpEJi = pxpEJ->at(i);
		auto pypEJi = pypEJ->at(i);
		for (size_t j = i; j < 4; j++)
		{
			auto pxpEJj = pxpEJ->at(j);
			auto pypEJj = pypEJ->at(j);
			auto term1 = (pxpEJi * pxpEJj - (pypEJi * pypEJj)) * twoCosSinOverSSqSq;
			auto term2 = ppypEJpEJi->at(j) * cosOverSSq - (ppxpEJpEJi->at(j) * sinOverSSq);
			auto term3 = (pypEJi * pxpEJj + (pxpEJi * pypEJj)) * dSqOverSSqSq;
			auto ppthezpEJpEJij = term1 + term2 + term3;
			ppthezpEJpEJi->atput(j, ppthezpEJpEJij);
			if (i < j) ppthezpEJpEJ->atandput(j, i, ppthezpEJpEJij);
		}
	}
}

void MbD::OrbitAngleZIeqcJeqc::calc_ppthezpXIpEJ()
{
	//ppxpXIpEJ = 0
	//ppypXIpEJ = 0

	auto pxpXI = xIeJeIe->pvaluepXI();
	auto pypXI = yIeJeIe->pvaluepXI();
	auto pxpEJ = xIeJeIe->pvaluepEJ();
	auto pypEJ = yIeJeIe->pvaluepEJ();
	for (size_t i = 0; i < 3; i++)
	{
		auto ppthezpXIpEJi = ppthezpXIpEJ->at(i);
		auto pxpXIi = pxpXI->at(i);
		auto pypXIi = pypXI->at(i);
		for (size_t j = 0; j < 4; j++)
		{
			auto pxpEJj = pxpEJ->at(j);
			auto pypEJj = pypEJ->at(j);
			auto term1 = (pxpXIi * pxpEJj - (pypXIi * pypEJj)) * twoCosSinOverSSqSq;
			auto term3 = (pypXIi * pxpEJj + (pxpXIi * pypEJj)) * dSqOverSSqSq;
			ppthezpXIpEJi->atput(j, term1 + term3);
		}
	}
}

void MbD::OrbitAngleZIeqcJeqc::calc_ppthezpXIpXJ()
{
	//ppxpXIpXJ = 0
	//ppypXIpXJ = 0

	auto pxpXI = xIeJeIe->pvaluepXI();
	auto pypXI = yIeJeIe->pvaluepXI();
	auto pxpXJ = xIeJeIe->pvaluepXJ();
	auto pypXJ = yIeJeIe->pvaluepXJ();
	for (size_t i = 0; i < 3; i++)
	{
		auto ppthezpXIpXJi = ppthezpXIpXJ->at(i);
		auto pxpXIi = pxpXI->at(i);
		auto pypXIi = pypXI->at(i);
		for (size_t j = 0; j < 3; j++)
		{
			auto pxpXJj = pxpXJ->at(j);
			auto pypXJj = pypXJ->at(j);
			auto term1 = (pxpXIi * pxpXJj - (pypXIi * pypXJj)) * twoCosSinOverSSqSq;
			auto term3 = (pypXIi * pxpXJj + (pxpXIi * pypXJj)) * dSqOverSSqSq;
			ppthezpXIpXJi->atput(j, term1 + term3);
		}
	}
}

void MbD::OrbitAngleZIeqcJeqc::calc_ppthezpXJpEJ()
{
	//ppxpXJpEJ = 0
	//ppypXJpEJ = 0

	auto pxpXJ = xIeJeIe->pvaluepXJ();
	auto pypXJ = yIeJeIe->pvaluepXJ();
	auto pxpEJ = xIeJeIe->pvaluepEJ();
	auto pypEJ = yIeJeIe->pvaluepEJ();
	for (size_t i = 0; i < 3; i++)
	{
		auto ppthezpXJpEJi = ppthezpXJpEJ->at(i);
		auto pxpXJi = pxpXJ->at(i);
		auto pypXJi = pypXJ->at(i);
		for (size_t j = 0; j < 4; j++)
		{
			auto pxpEJj = pxpEJ->at(j);
			auto pypEJj = pypEJ->at(j);
			auto term1 = (pxpXJi * pxpEJj - (pypXJi * pypEJj)) * twoCosSinOverSSqSq;
			auto term3 = (pypXJi * pxpEJj + (pxpXJi * pypEJj)) * dSqOverSSqSq;
			ppthezpXJpEJi->atput(j, term1 + term3);
		}
	}
}

void MbD::OrbitAngleZIeqcJeqc::calc_ppthezpXJpXJ()
{
	//ppxpXJpXJ = 0
	//ppypXJpXJ = 0

	auto pxpXJ = xIeJeIe->pvaluepXJ();
	auto pypXJ = yIeJeIe->pvaluepXJ();
	for (size_t i = 0; i < 3; i++)
	{
		auto ppthezpXJpXJi = ppthezpXJpXJ->at(i);
		auto pxpXJi = pxpXJ->at(i);
		auto pypXJi = pypXJ->at(i);
		for (size_t j = 0; j < 3; j++)
		{
			auto pxpXJj = pxpXJ->at(j);
			auto pypXJj = pypXJ->at(j);
			auto term1 = (pxpXJi * pxpXJj - (pypXJi * pypXJj)) * twoCosSinOverSSqSq;
			auto term3 = (pypXJi * pxpXJj + (pxpXJi * pypXJj)) * dSqOverSSqSq;
			ppthezpXJpXJi->atput(j, term1 + term3);
		}
	}
}

void MbD::OrbitAngleZIeqcJeqc::calc_pthezpEJ()
{
	auto pxpEJ = xIeJeIe->pvaluepEJ();
	auto pypEJ = yIeJeIe->pvaluepEJ();
	for (size_t i = 0; i < 4; i++)
	{
		pthezpEJ->atput(i, pypEJ->at(i) * cosOverSSq - (pxpEJ->at(i) * sinOverSSq));
	}
}

void MbD::OrbitAngleZIeqcJeqc::calc_pthezpXJ()
{
	auto pxpXJ = xIeJeIe->pvaluepXJ();
	auto pypXJ = yIeJeIe->pvaluepXJ();
	for (size_t i = 0; i < 3; i++)
	{
		pthezpXJ->atput(i, pypXJ->at(i) * cosOverSSq - (pxpXJ->at(i) * sinOverSSq));
	}
}

void MbD::OrbitAngleZIeqcJeqc::calcPostDynCorrectorIteration()
{
	OrbitAngleZIeqcJec::calcPostDynCorrectorIteration();
	calc_pthezpXJ();
	calc_pthezpEJ();
	calc_ppthezpXIpXJ();
	calc_ppthezpXIpEJ();
	calc_ppthezpEIpXJ();
	calc_ppthezpEIpEJ();
	calc_ppthezpXJpXJ();
	calc_ppthezpXJpEJ();
	calc_ppthezpEJpEJ();
}

void MbD::OrbitAngleZIeqcJeqc::init_xyIeJeIe()
{
	xIeJeIe = DispCompIeqcJeqcIe::With(efrmI, efrmJ, 0);
	yIeJeIe = DispCompIeqcJeqcIe::With(efrmI, efrmJ, 1);
}

FMatDsptr MbD::OrbitAngleZIeqcJeqc::ppvaluepEIpEJ()
{
	return ppthezpEIpEJ;
}

FMatDsptr MbD::OrbitAngleZIeqcJeqc::ppvaluepEIpXJ()
{
	return ppthezpEIpXJ;
}

FMatDsptr MbD::OrbitAngleZIeqcJeqc::ppvaluepEJpEJ()
{
	return ppthezpEJpEJ;
}

FMatDsptr MbD::OrbitAngleZIeqcJeqc::ppvaluepXIpEJ()
{
	return ppthezpXIpEJ;
}

FMatDsptr MbD::OrbitAngleZIeqcJeqc::ppvaluepXIpXJ()
{
	return ppthezpXIpXJ;
}

FMatDsptr MbD::OrbitAngleZIeqcJeqc::ppvaluepXJpEJ()
{
	return ppthezpXJpEJ;
}

FMatDsptr MbD::OrbitAngleZIeqcJeqc::ppvaluepXJpXJ()
{
	return ppthezpXJpXJ;
}

FRowDsptr MbD::OrbitAngleZIeqcJeqc::pvaluepEJ()
{
	return pthezpEJ;
}

FRowDsptr MbD::OrbitAngleZIeqcJeqc::pvaluepXJ()
{
	return pthezpXJ;
}
