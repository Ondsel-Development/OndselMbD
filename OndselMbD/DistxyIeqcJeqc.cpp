/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DistxyIeqcJeqc.h"
#include "DispCompIeqcJeqcIe.h"

using namespace MbD;

MbD::DistxyIeqcJeqc::DistxyIeqcJeqc(EndFrmsptr frmi, EndFrmsptr frmj) : DistxyIeqcJec(frmi, frmj)
{
	assert(false);
}

std::shared_ptr<DistxyIeqcJeqc> MbD::DistxyIeqcJeqc::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
	auto inst = std::make_shared<DistxyIeqcJeqc>(frmi, frmj);
	inst->initialize();
	return inst;
}

void MbD::DistxyIeqcJeqc::initialize()
{
	DistxyIeqcJec::initialize();
	pdistxypXJ = FullRow<double>::With(3);
	pdistxypEJ = FullRow<double>::With(4);
	ppdistxypXIpXJ = FullMatrix<double>::With(3, 3);
	ppdistxypXIpEJ = FullMatrix<double>::With(3, 4);
	ppdistxypEIpXJ = FullMatrix<double>::With(4, 3);
	ppdistxypEIpEJ = FullMatrix<double>::With(4, 4);
	ppdistxypXJpXJ = FullMatrix<double>::With(3, 3);
	ppdistxypXJpEJ = FullMatrix<double>::With(3, 4);
	ppdistxypEJpEJ = FullMatrix<double>::With(4, 4);
}

void MbD::DistxyIeqcJeqc::calc_ppdistxypEIpEJ()
{
	auto x = xIeJeIe->value();
	auto y = yIeJeIe->value();
	auto pxpEI = xIeJeIe->pvaluepEI();
	auto pypEI = yIeJeIe->pvaluepEI();
	auto pxpEJ = xIeJeIe->pvaluepEJ();
	auto pypEJ = yIeJeIe->pvaluepEJ();
	auto ppxpEIpEJ = xIeJeIe->ppvaluepEIpEJ();
	auto ppypEIpEJ = yIeJeIe->ppvaluepEIpEJ();
	for (size_t i = 0; i < 4; i++)
	{
		auto& ppdistxypEIpEJi = ppdistxypEIpEJ->at(i);
		auto& pdistxypEIi = pdistxypEI->at(i);
		auto& ppxpEIpEJi = ppxpEIpEJ->at(i);
		auto& ppypEIpEJi = ppypEIpEJ->at(i);
		auto& pxpEIi = pxpEI->at(i);
		auto& pypEIi = pypEI->at(i);
		for (size_t j = 0; j < 4; j++)
		{
			auto& pdistxypEJj = pdistxypEJ->at(j);
			auto& pxpEJj = pxpEJ->at(j);
			auto& pypEJj = pypEJ->at(j);
			auto term1 = -pdistxypEIi * pdistxypEJj;
			auto term2 = ppxpEIpEJi->at(j) * x + ppypEIpEJi->at(j) * y;
			auto term3 = pxpEIi * pxpEJj + pypEIi * pypEJj;
			auto ppdistxypEIpEJij = (term1 + term2 + term3) / distxy;
			ppdistxypEIpEJi->atput(j, ppdistxypEIpEJij);
		}
	}
}

void MbD::DistxyIeqcJeqc::calc_ppdistxypEIpXJ()
{
	auto x = xIeJeIe->value();
	auto y = yIeJeIe->value();
	auto pxpEI = xIeJeIe->pvaluepEI();
	auto pypEI = yIeJeIe->pvaluepEI();
	auto pxpXJ = xIeJeIe->pvaluepXJ();
	auto pypXJ = yIeJeIe->pvaluepXJ();
	auto ppxpEIpXJ = xIeJeIe->ppvaluepEIpXJ();
	auto ppypEIpXJ = yIeJeIe->ppvaluepEIpXJ();
	for (size_t i = 0; i < 4; i++)
	{
		auto& ppdistxypEIpXJi = ppdistxypEIpXJ->at(i);
		auto& pdistxypEIi = pdistxypEI->at(i);
		auto& ppxpEIpXJi = ppxpEIpXJ->at(i);
		auto& ppypEIpXJi = ppypEIpXJ->at(i);
		auto& pxpEIi = pxpEI->at(i);
		auto& pypEIi = pypEI->at(i);
		for (size_t j = 0; j < 3; j++)
		{
			auto& pdistxypXJj = pdistxypXJ->at(j);
			auto& pxpXJj = pxpXJ->at(j);
			auto& pypXJj = pypXJ->at(j);
			auto term1 = -pdistxypEIi * pdistxypXJj;
			auto term2 = ppxpEIpXJi->at(j) * x + ppypEIpXJi->at(j) * y;
			auto term3 = pxpEIi * pxpXJj + pypEIi * pypXJj;
			auto ppdistxypEIpXJij = (term1 + term2 + term3) / distxy;
			ppdistxypEIpXJi->atput(j, ppdistxypEIpXJij);
		}
	}
}

void MbD::DistxyIeqcJeqc::calc_ppdistxypEJpEJ()
{
	auto x = xIeJeIe->value();
	auto y = yIeJeIe->value();
	auto pxpEJ = xIeJeIe->pvaluepEJ();
	auto pypEJ = yIeJeIe->pvaluepEJ();
	auto ppxpEJpEJ = xIeJeIe->ppvaluepEJpEJ();
	auto ppypEJpEJ = yIeJeIe->ppvaluepEJpEJ();
	for (size_t i = 0; i < 4; i++)
	{
		auto& ppdistxypEJpEJi = ppdistxypEJpEJ->at(i);
		auto& pdistxypEJi = pdistxypEJ->at(i);
		auto& ppxpEJpEJi = ppxpEJpEJ->at(i);
		auto& ppypEJpEJi = ppypEJpEJ->at(i);
		auto& pxpEJi = pxpEJ->at(i);
		auto& pypEJi = pypEJ->at(i);
		for (size_t j = i; j < 4; j++)
		{
			auto& pdistxypEJj = pdistxypEJ->at(j);
			auto& pxpEJj = pxpEJ->at(j);
			auto& pypEJj = pypEJ->at(j);
			auto term1 = -pdistxypEJi * pdistxypEJj;
			auto term2 = ppxpEJpEJi->at(j) * x + ppypEJpEJi->at(j) * y;
			auto term3 = pxpEJi * pxpEJj + pypEJi * pypEJj;
			auto ppdistxypEJpEJij = (term1 + term2 + term3) / distxy;
			ppdistxypEJpEJi->atput(j, ppdistxypEJpEJij);
			if (i < j) ppdistxypEJpEJ->atandput(j, i, ppdistxypEJpEJij);
		}
	}
}

void MbD::DistxyIeqcJeqc::calc_ppdistxypXIpEJ()
{
	auto x = xIeJeIe->value();
	auto y = yIeJeIe->value();
	auto pxpXI = xIeJeIe->pvaluepXI();
	auto pypXI = yIeJeIe->pvaluepXI();
	auto pxpEJ = xIeJeIe->pvaluepEJ();
	auto pypEJ = yIeJeIe->pvaluepEJ();
	auto ppxpXIpEJ = xIeJeIe->ppvaluepXIpEJ();
	auto ppypXIpEJ = yIeJeIe->ppvaluepXIpEJ();
	for (size_t i = 0; i < 4; i++)
	{
		auto& ppdistxypXIpEJi = ppdistxypXIpEJ->at(i);
		auto& pdistxypXIi = pdistxypXI->at(i);
		auto& ppxpXIpEJi = ppxpXIpEJ->at(i);
		auto& ppypXIpEJi = ppypXIpEJ->at(i);
		auto& pxpXIi = pxpXI->at(i);
		auto& pypXIi = pypXI->at(i);
		for (size_t j = 0; j < 4; j++)
		{
			auto& pdistxypEJj = pdistxypEJ->at(j);
			auto& pxpEJj = pxpEJ->at(j);
			auto& pypEJj = pypEJ->at(j);
			auto term1 = -pdistxypXIi * pdistxypEJj;
			auto term2 = ppxpXIpEJi->at(j) * x + ppypXIpEJi->at(j) * y;
			auto term3 = pxpXIi * pxpEJj + pypXIi * pypEJj;
			auto ppdistxypXIpEJij = (term1 + term2 + term3) / distxy;
			ppdistxypXIpEJi->atput(j, ppdistxypXIpEJij);
		}
	}
}

void MbD::DistxyIeqcJeqc::calc_ppdistxypXIpXJ()
{
	auto x = xIeJeIe->value();
	auto y = yIeJeIe->value();
	auto pxpXI = xIeJeIe->pvaluepXI();
	auto pypXI = yIeJeIe->pvaluepXI();
	auto pxpXJ = xIeJeIe->pvaluepXJ();
	auto pypXJ = yIeJeIe->pvaluepXJ();
	auto ppxpXIpXJ = xIeJeIe->ppvaluepXIpXJ();
	auto ppypXIpXJ = yIeJeIe->ppvaluepXIpXJ();
	for (size_t i = 0; i < 4; i++)
	{
		auto& ppdistxypXIpXJi = ppdistxypXIpXJ->at(i);
		auto& pdistxypXIi = pdistxypXI->at(i);
		auto& ppxpXIpXJi = ppxpXIpXJ->at(i);
		auto& ppypXIpXJi = ppypXIpXJ->at(i);
		auto& pxpXIi = pxpXI->at(i);
		auto& pypXIi = pypXI->at(i);
		for (size_t j = 0; j < 4; j++)
		{
			auto& pdistxypXJj = pdistxypXJ->at(j);
			auto& pxpXJj = pxpXJ->at(j);
			auto& pypXJj = pypXJ->at(j);
			auto term1 = -pdistxypXIi * pdistxypXJj;
			auto term2 = ppxpXIpXJi->at(j) * x + ppypXIpXJi->at(j) * y;
			auto term3 = pxpXIi * pxpXJj + pypXIi * pypXJj;
			auto ppdistxypXIpXJij = (term1 + term2 + term3) / distxy;
			ppdistxypXIpXJi->atput(j, ppdistxypXIpXJij);
		}
	}
}

void MbD::DistxyIeqcJeqc::calc_ppdistxypXJpEJ()
{
	auto x = xIeJeIe->value();
	auto y = yIeJeIe->value();
	auto pxpXJ = xIeJeIe->pvaluepXJ();
	auto pypXJ = yIeJeIe->pvaluepXJ();
	auto pxpEJ = xIeJeIe->pvaluepEJ();
	auto pypEJ = yIeJeIe->pvaluepEJ();
	auto ppxpXJpEJ = xIeJeIe->ppvaluepXJpEJ();
	auto ppypXJpEJ = yIeJeIe->ppvaluepXJpEJ();
	for (size_t i = 0; i < 4; i++)
	{
		auto& ppdistxypXJpEJi = ppdistxypXJpEJ->at(i);
		auto& pdistxypXJi = pdistxypXJ->at(i);
		auto& ppxpXJpEJi = ppxpXJpEJ->at(i);
		auto& ppypXJpEJi = ppypXJpEJ->at(i);
		auto& pxpXJi = pxpXJ->at(i);
		auto& pypXJi = pypXJ->at(i);
		for (size_t j = 0; j < 4; j++)
		{
			auto& pdistxypEJj = pdistxypEJ->at(j);
			auto& pxpEJj = pxpEJ->at(j);
			auto& pypEJj = pypEJ->at(j);
			auto term1 = -pdistxypXJi * pdistxypEJj;
			auto term2 = ppxpXJpEJi->at(j) * x + ppypXJpEJi->at(j) * y;
			auto term3 = pxpXJi * pxpEJj + pypXJi * pypEJj;
			auto ppdistxypXJpEJij = (term1 + term2 + term3) / distxy;
			ppdistxypXJpEJi->atput(j, ppdistxypXJpEJij);
		}
	}
}

void MbD::DistxyIeqcJeqc::calc_ppdistxypXJpXJ()
{
	auto x = xIeJeIe->value();
	auto y = yIeJeIe->value();
	auto pxpXJ = xIeJeIe->pvaluepXJ();
	auto pypXJ = yIeJeIe->pvaluepXJ();
	auto ppxpXJpXJ = xIeJeIe->ppvaluepXJpXJ();
	auto ppypXJpXJ = yIeJeIe->ppvaluepXJpXJ();
	for (size_t i = 0; i < 3; i++)
	{
		auto& ppdistxypXJpXJi = ppdistxypXJpXJ->at(i);
		auto& pdistxypXJi = pdistxypXJ->at(i);
		auto& ppxpXJpXJi = ppxpXJpXJ->at(i);
		auto& ppypXJpXJi = ppypXJpXJ->at(i);
		auto& pxpXJi = pxpXJ->at(i);
		auto& pypXJi = pypXJ->at(i);
		for (size_t j = i; j < 3; j++)
		{
			auto& pdistxypXJj = pdistxypXJ->at(j);
			auto& pxpXJj = pxpXJ->at(j);
			auto& pypXJj = pypXJ->at(j);
			auto term1 = -pdistxypXJi * pdistxypXJj;
			auto term2 = ppxpXJpXJi->at(j) * x + ppypXJpXJi->at(j) * y;
			auto term3 = pxpXJi * pxpXJj + pypXJi * pypXJj;
			auto ppdistxypXJpXJij = (term1 + term2 + term3) / distxy;
			ppdistxypXJpXJi->atput(j, ppdistxypXJpXJij);
			if (i < j) ppdistxypXJpXJ->atandput(j, i, ppdistxypXJpXJij);
		}
	}
}

void MbD::DistxyIeqcJeqc::calc_pdistxypEJ()
{
	auto x = xIeJeIe->value();
	auto y = yIeJeIe->value();
	auto pxpEJ = xIeJeIe->pvaluepEJ();
	auto pypEJ = yIeJeIe->pvaluepEJ();
	for (size_t i = 0; i < 4; i++)
	{
		auto term = pxpEJ->at(i) * x + pypEJ->at(i) * y;
		pdistxypEJ->atput(i, term / distxy);
	}
}

void MbD::DistxyIeqcJeqc::calc_pdistxypXJ()
{
	auto x = xIeJeIe->value();
	auto y = yIeJeIe->value();
	auto pxpXJ = xIeJeIe->pvaluepXJ();
	auto pypXJ = yIeJeIe->pvaluepXJ();
	for (size_t i = 0; i < 3; i++)
	{
		auto term = pxpXJ->at(i) * x + pypXJ->at(i) * y;
		pdistxypXJ->atput(i, term / distxy);
	}
}

void MbD::DistxyIeqcJeqc::calcPostDynCorrectorIteration()
{
	DistxyIeqcJec::calcPostDynCorrectorIteration();
	calc_pdistxypXJ();
	calc_pdistxypEJ();
	calc_ppdistxypXIpXJ();
	calc_ppdistxypXIpEJ();
	calc_ppdistxypEIpXJ();
	calc_ppdistxypEIpEJ();
	calc_ppdistxypXJpXJ();
	calc_ppdistxypXJpEJ();
	calc_ppdistxypEJpEJ();
}

void MbD::DistxyIeqcJeqc::init_xyIeJeIe()
{
	xIeJeIe = DispCompIeqcJeqcIe::With(frmI, frmJ, 0);
	yIeJeIe = DispCompIeqcJeqcIe::With(frmI, frmJ, 1);
}

FMatDsptr MbD::DistxyIeqcJeqc::ppvaluepEIpEJ()
{
	return ppdistxypEIpEJ;
}

FMatDsptr MbD::DistxyIeqcJeqc::ppvaluepEIpXJ()
{
	return ppdistxypEIpXJ;
}

FMatDsptr MbD::DistxyIeqcJeqc::ppvaluepEJpEJ()
{
	return ppdistxypEJpEJ;
}

FMatDsptr MbD::DistxyIeqcJeqc::ppvaluepXIpEJ()
{
	return ppdistxypXIpEJ;
}

FMatDsptr MbD::DistxyIeqcJeqc::ppvaluepXIpXJ()
{
	return ppdistxypXIpXJ;
}

FMatDsptr MbD::DistxyIeqcJeqc::ppvaluepXJpEJ()
{
	return ppdistxypXJpEJ;
}

FMatDsptr MbD::DistxyIeqcJeqc::ppvaluepXJpXJ()
{
	return ppdistxypXJpXJ;
}

FRowDsptr MbD::DistxyIeqcJeqc::pvaluepEJ()
{
	return pdistxypEJ;
}

FRowDsptr MbD::DistxyIeqcJeqc::pvaluepXJ()
{
	return pdistxypXJ;
}
