/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DistxyIeqcJec.h"
#include "DispCompIeqcJecIe.h"

using namespace MbD;

MbD::DistxyIeqcJec::DistxyIeqcJec(EndFrmsptr frmi, EndFrmsptr frmj) : DistxyIecJec(frmi, frmj)
{
	assert(false);
}

std::shared_ptr<DistxyIeqcJec> MbD::DistxyIeqcJec::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
	auto inst = std::make_shared<DistxyIeqcJec>(frmi, frmj);
	inst->initialize();
	return inst;
}

void MbD::DistxyIeqcJec::initialize()
{
	DistxyIecJec::initialize();
	pdistxypXI = FullRow<double>::With(3);
	pdistxypEI = FullRow<double>::With(4);
	ppdistxypXIpXI = FullMatrix<double>::With(3, 3);
	ppdistxypXIpEI = FullMatrix<double>::With(3, 4);
	ppdistxypEIpEI = FullMatrix<double>::With(4, 4);
}

void MbD::DistxyIeqcJec::calc_ppdistxypEIpEI()
{
	auto x = xIeJeIe->value();
	auto y = yIeJeIe->value();
	auto pxpEI = xIeJeIe->pvaluepEI();
	auto pypEI = yIeJeIe->pvaluepEI();
	auto ppxpEIpEI = xIeJeIe->ppvaluepEIpEI();
	auto ppypEIpEI = yIeJeIe->ppvaluepEIpEI();
	for (size_t i = 0; i < 4; i++)
	{
		auto& ppdistxypEIpEIi = ppdistxypEIpEI->at(i);
		auto& pdistxypEIi = pdistxypEI->at(i);
		auto& ppxpEIpEIi = ppxpEIpEI->at(i);
		auto& ppypEIpEIi = ppypEIpEI->at(i);
		auto& pxpEIi = pxpEI->at(i);
		auto& pypEIi = pypEI->at(i);
		for (size_t j = i; j < 4; j++)
		{
			auto pdistxypEIj = pdistxypEI->at(j);
			auto pxpEIj = pxpEI->at(j);
			auto pypEIj = pypEI->at(j);
			auto term1 = -pdistxypEIi * pdistxypEIj;
			auto term2 = ppxpEIpEIi->at(j) * x + ppypEIpEIi->at(j) * y;
			auto term3 = pxpEIi * pxpEIj + pypEIi * pypEIj;
			auto ppdistxypEIpEIij = (term1 + term2 + term3) / distxy;
			ppdistxypEIpEIi->atput(j, ppdistxypEIpEIij);
			if (i < j) ppdistxypEIpEI->atandput(j, i, ppdistxypEIpEIij);
		}
	}
}

void MbD::DistxyIeqcJec::calc_ppdistxypXIpEI()
{
	auto x = xIeJeIe->value();
	auto y = yIeJeIe->value();
	auto pxpXI = xIeJeIe->pvaluepXI();
	auto pypXI = yIeJeIe->pvaluepXI();
	auto pxpEI = xIeJeIe->pvaluepEI();
	auto pypEI = yIeJeIe->pvaluepEI();
	auto ppxpXIpEI = xIeJeIe->ppvaluepXIpEI();
	auto ppypXIpEI = yIeJeIe->ppvaluepXIpEI();
	for (size_t i = 0; i < 3; i++)
	{
		auto& ppdistxypXIpEIi = ppdistxypXIpEI->at(i);
		auto& pdistxypXIi = pdistxypXI->at(i);
		auto& ppxpXIpEIi = ppxpXIpEI->at(i);
		auto& ppypXIpEIi = ppypXIpEI->at(i);
		auto& pxpXIi = pxpXI->at(i);
		auto& pypXIi = pypXI->at(i);
		for (size_t j = 0; j < 4; j++)
		{
			auto& pdistxypEIj = pdistxypEI->at(j);
			auto& pxpEIj = pxpEI->at(j);
			auto& pypEIj = pypEI->at(j);
			auto term1 = -pdistxypXIi * pdistxypEIj;
			auto term2 = ppxpXIpEIi->at(j) * x + ppypXIpEIi->at(j) * y;
			auto term3 = pxpXIi * pxpEIj + pypXIi * pypEIj;
			auto ppdistxypXIpEIij = (term1 + term2 + term3) / distxy;
			ppdistxypXIpEIi->atput(j, ppdistxypXIpEIij);
		}
	}
}

void MbD::DistxyIeqcJec::calc_ppdistxypXIpXI()
{
	auto x = xIeJeIe->value();
	auto y = yIeJeIe->value();
	auto pxpXI = xIeJeIe->pvaluepXI();
	auto pypXI = yIeJeIe->pvaluepXI();
	auto ppxpXIpXI = xIeJeIe->ppvaluepXIpXI();
	auto ppypXIpXI = yIeJeIe->ppvaluepXIpXI();
	for (size_t i = 0; i < 3; i++)
	{
		auto& ppdistxypXIpXIi = ppdistxypXIpXI->at(i);
		auto& pdistxypXIi = pdistxypXI->at(i);
		auto& ppxpXIpXIi = ppxpXIpXI->at(i);
		auto& ppypXIpXIi = ppypXIpXI->at(i);
		auto& pxpXIi = pxpXI->at(i);
		auto& pypXIi = pypXI->at(i);
		for (size_t j = i; j < 3; j++)
		{
			auto pdistxypXIj = pdistxypXI->at(j);
			auto pxpXIj = pxpXI->at(j);
			auto pypXIj = pypXI->at(j);
			auto term1 = -pdistxypXIi * pdistxypXIj;
			auto term2 = ppxpXIpXIi->at(j) * x + ppypXIpXIi->at(j) * y;
			auto term3 = pxpXIi * pxpXIj + pypXIi * pypXIj;
			auto ppdistxypXIpXIij = (term1 + term2 + term3) / distxy;
			ppdistxypXIpXIi->atput(j, ppdistxypXIpXIij);
			if (i < j) ppdistxypXIpXI->atandput(j, i, ppdistxypXIpXIij);
		}
	}
}

void MbD::DistxyIeqcJec::calc_pdistxypEI()
{
	auto x = xIeJeIe->value();
	auto y = yIeJeIe->value();
	auto pxpEI = xIeJeIe->pvaluepEI();
	auto pypEI = yIeJeIe->pvaluepEI();
	for (size_t i = 0; i < 4; i++)
	{
		auto term = pxpEI->at(i) * x + pypEI->at(i) * y;
		pdistxypEI->atput(i, term / distxy);
	}
}

void MbD::DistxyIeqcJec::calc_pdistxypXI()
{
	auto x = xIeJeIe->value();
	auto y = yIeJeIe->value();
	auto pxpXI = xIeJeIe->pvaluepXI();
	auto pypXI = yIeJeIe->pvaluepXI();
	for (size_t i = 0; i < 3; i++)
	{
		auto term = pxpXI->at(i) * x + pypXI->at(i) * y;
		pdistxypXI->atput(i, term / distxy);
	}
}

void MbD::DistxyIeqcJec::calcPostDynCorrectorIteration()
{
	DistxyIecJec::calcPostDynCorrectorIteration();
	calc_pdistxypXI();
	calc_pdistxypEI();
	calc_ppdistxypXIpXI();
	calc_ppdistxypXIpEI();
	calc_ppdistxypEIpEI();
}

void MbD::DistxyIeqcJec::init_xyIeJeIe()
{
	xIeJeIe = DispCompIeqcJecIe::With(efrmI, efrmJ, 0);
	yIeJeIe = DispCompIeqcJecIe::With(efrmI, efrmJ, 1);
}

FMatDsptr MbD::DistxyIeqcJec::ppvaluepEIpEI()
{
	return ppdistxypEIpEI;
}

FMatDsptr MbD::DistxyIeqcJec::ppvaluepXIpEI()
{
	return ppdistxypXIpEI;
}

FMatDsptr MbD::DistxyIeqcJec::ppvaluepXIpXI()
{
	return ppdistxypXIpXI;
}

FRowDsptr MbD::DistxyIeqcJec::pvaluepEI()
{
	return pdistxypEI;
}

FRowDsptr MbD::DistxyIeqcJec::pvaluepXI()
{
	return pdistxypXI;
}
