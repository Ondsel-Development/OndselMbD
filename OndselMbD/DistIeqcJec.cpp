/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "DistIeqcJec.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<DistIeqcJec> MbD::DistIeqcJec::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
	auto inst = std::make_shared<DistIeqcJec>(frmi, frmj);
	inst->initialize();
	return inst;
}

void MbD::DistIeqcJec::initialize()
{
	DistIecJec::initialize();
	prIeJepXI = FullRow<double>::With(3);
	prIeJepEI = FullRow<double>::With(4);
	pprIeJepXIpXI = FullMatrix<double>::With(3, 3);
	pprIeJepXIpEI = FullMatrix<double>::With(3, 4);
	pprIeJepEIpEI = FullMatrix<double>::With(4, 4);
}

void MbD::DistIeqcJec::calcPrivate()
{
	DistIecJec::calcPrivate();
	if (rIeJe == 0.0) return;
	auto frmIeqc = std::static_pointer_cast<EndFrameqc>(efrmI);
	auto& mprIeJeOpEI = frmIeqc->prOeOpE;
	mprIeJeOpEIT = mprIeJeOpEI->transpose();
	auto& mpprIeJeOpEIpEI = frmIeqc->pprOeOpEpE;
	auto muIeJeOT = muIeJeO->transpose();
	prIeJepXI = muIeJeOT;
	prIeJepEI = muIeJeOT->timesFullMatrix(mprIeJeOpEI);
	for (size_t i = 0; i < 3; i++)
	{
		auto& pprIeJepXIipXI = pprIeJepXIpXI->at(i);
		auto& prIeJepXIi = prIeJepXI->at(i);
		for (size_t j = 0; j < 3; j++)
		{
			auto element = (i == j) ? 1.0 : 0.0;
			element -= prIeJepXIi * prIeJepXI->at(j);
			pprIeJepXIipXI->atput(j, element / rIeJe);
		}
	}
	pprIeJepXIpEI = FullMatrix<double>::With(3, 4);
	for (size_t i = 0; i < 3; i++)
	{
		auto& pprIeJepXIipEI = pprIeJepXIpEI->at(i);
		auto& prIeJepXIi = prIeJepXI->at(i);
		auto& mprIeJeOipEI = mprIeJeOpEI->at(i);
		for (size_t j = 0; j < 4; j++)
		{
			auto element = mprIeJeOipEI->at(j) - prIeJepXIi * prIeJepEI->at(j);
			pprIeJepXIipEI->atput(j, element / rIeJe);
		}
	}
	pprIeJepEIpEI = FullMatrix<double>::With(4, 4);
	for (size_t i = 0; i < 4; i++)
	{
		auto& pprIeJepEIipEI = pprIeJepEIpEI->at(i);
		auto& prIeJepEIi = prIeJepEI->at(i);
		auto& mpprIeJeOpEIipEI = mpprIeJeOpEIpEI->at(i);
		auto& mprIeJeOpEIiT = mprIeJeOpEIT->at(i);
		for (size_t j = 0; j < 4; j++)
		{
			auto element = mprIeJeOpEIiT->dot(mprIeJeOpEIT->at(j))
				- mpprIeJeOpEIipEI->at(j)->dot(rIeJeO) - prIeJepEIi * prIeJepEI->at(j);
			pprIeJepEIipEI->atput(j, element / rIeJe);
		}
	}
}

FMatDsptr MbD::DistIeqcJec::ppvaluepEIpEI()
{
	return pprIeJepEIpEI;
}

FMatDsptr MbD::DistIeqcJec::ppvaluepXIpEI()
{
	return pprIeJepXIpEI;
}

FMatDsptr MbD::DistIeqcJec::ppvaluepXIpXI()
{
	return pprIeJepXIpXI;
}

FMatDsptr MbD::DistIeqcJec::puIeJeOpEI()
{
	auto answer = FullMatrix<double>::With(3, 4);
	auto mprIeJeOpEI = std::static_pointer_cast<EndFrameqc>(efrmI)->prOeOpE;
	auto m1OverrIeJe = -1.0 / rIeJe;
	auto m1OverrIeJeSq = m1OverrIeJe / rIeJe;
	for (size_t i = 0; i < 3; i++) {
		auto answeri = answer->at(i);
		auto mprIeJeOpEIi = mprIeJeOpEI->at(i);
		auto rIeJeOi = rIeJeO->at(i);
		for (size_t j = 0; j < 4; j++) {
			auto aij = mprIeJeOpEIi->at(j) * m1OverrIeJe + (rIeJeOi * prIeJepEI->at(j) * m1OverrIeJeSq);
			answeri->atput(j, aij);
		}
	}
	return answer;
}

FMatDsptr MbD::DistIeqcJec::puIeJeOpXI()
{
	auto answer = FullMatrix<double>::With(3, 3);
	auto m1OverrIeJe = -1.0 / rIeJe;
	auto m1OverrIeJeSq = m1OverrIeJe / rIeJe;
	for (size_t i = 0; i < 3; i++) {
		auto answeri = answer->at(i);
		auto rIeJeOi = rIeJeO->at(i);
		for (size_t j = 0; j < 3; j++) {
			auto aij = rIeJeOi * prIeJepXI->at(j) * m1OverrIeJeSq;
			answeri->atput(j, aij);
		}
		answeri->atplusNumber(i, m1OverrIeJe);
	}
	return answer;
}

FRowDsptr MbD::DistIeqcJec::pvaluepEI()
{
	return prIeJepEI;
}

FRowDsptr MbD::DistIeqcJec::pvaluepXI()
{
	return prIeJepXI;
}
