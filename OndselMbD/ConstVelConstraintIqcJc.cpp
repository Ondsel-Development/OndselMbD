/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <memory>

#include "ConstVelConstraintIqcJc.h"
#include "DirectionCosineIeqcJec.h"
#include "DirectionCosineIeqcJeqc.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<ConstVelConstraintIqcJc> MbD::ConstVelConstraintIqcJc::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
	auto inst = std::make_shared<ConstVelConstraintIqcJc>(frmi, frmj);
	inst->initialize();
	return inst;
}

void MbD::ConstVelConstraintIqcJc::initialize()
{
	ConstVelConstraintIJ::initialize();
	pGpEI = FullRow<double>::With(4);
	ppGpEIpEI = FullMatrix<double>::With(4, 4);
}

void MbD::ConstVelConstraintIqcJc::calcPostDynCorrectorIteration()
{
	ConstVelConstraintIJ::calcPostDynCorrectorIteration();
	auto aA01IeqcJec = std::dynamic_pointer_cast<DirectionCosineIeqcJec>(aA01IeJe);
	auto& pA01IeJepEI = aA01IeqcJec->pAijIeJepEI;
	auto& ppA01IeJepEIpEI = aA01IeqcJec->ppAijIeJepEIpEI;
	auto aA10IeqcJec = std::dynamic_pointer_cast<DirectionCosineIeqcJec>(aA10IeJe);
	auto& pA10IeJepEI = aA10IeqcJec->pAijIeJepEI;
	auto& ppA10IeJepEIpEI = aA10IeqcJec->ppAijIeJepEIpEI;
	for (size_t i = 0; i < 4; i++)
	{
		pGpEI->atput(i, pA01IeJepEI->at(i) + pA10IeJepEI->at(i));
	}
	for (size_t i = 0; i < 4; i++)
	{
		auto& ppGpEIpEIi = ppGpEIpEI->at(i);
		auto& ppA01IeJepEIpEIi = ppA01IeJepEIpEI->at(i);
		auto& ppA10IeJepEIpEIi = ppA10IeJepEIpEI->at(i);
		ppGpEIpEIi->atput(i, ppA01IeJepEIpEIi->at(i) + ppA10IeJepEIpEIi->at(i));
		for (size_t j = i + 1; j < 4; j++)
		{
			auto ppGpEIpEIij = ppA01IeJepEIpEIi->at(j) + ppA10IeJepEIpEIi->at(j);
			ppGpEIpEIi->atput(j, ppGpEIpEIij);
			ppGpEIpEI->atandput(j, i, ppGpEIpEIij);
		}
	}
}

void MbD::ConstVelConstraintIqcJc::fillAccICIterError(FColDsptr col)
{
	col->atplusFullVectortimes(iqEI, pGpEI, lam);
	auto efrmIqc = std::static_pointer_cast<EndFrameqc>(efrmI);
	auto qEdotI = efrmIqc->qEdot();
	double sum = 0.0;
	sum += pGpEI->timesFullColumn(efrmIqc->qEddot());
	sum += qEdotI->transposeTimesFullColumn(ppGpEIpEI->timesFullColumn(qEdotI));
	col->atplusNumber(iG, sum);
}

void MbD::ConstVelConstraintIqcJc::fillPosICError(FColDsptr col)
{
	Constraint::fillPosICError(col);
	col->atplusFullVectortimes(iqEI, pGpEI, lam);
}

void MbD::ConstVelConstraintIqcJc::fillPosICJacob(SpMatDsptr mat)
{
	mat->atandplusFullRow(iG, iqEI, pGpEI);
	mat->atandplusFullColumn(iqEI, iG, pGpEI->transpose());
	mat->atandplusFullMatrixtimes(iqEI, iqEI, ppGpEIpEI, lam);
}

void MbD::ConstVelConstraintIqcJc::fillPosKineJacob(SpMatDsptr mat)
{
	mat->atandplusFullRow(iG, iqEI, pGpEI);
}

void MbD::ConstVelConstraintIqcJc::fillVelICJacob(SpMatDsptr mat)
{
	mat->atandplusFullRow(iG, iqEI, pGpEI);
	mat->atandplusFullColumn(iqEI, iG, pGpEI->transpose());
}

void MbD::ConstVelConstraintIqcJc::initA01IeJe()
{
	aA01IeJe = DirectionCosineIeqcJec::With(efrmI, efrmJ, 0, 1);
}

void MbD::ConstVelConstraintIqcJc::initA10IeJe()
{
	aA10IeJe = DirectionCosineIeqcJec::With(efrmI, efrmJ, 1, 0);
}

void MbD::ConstVelConstraintIqcJc::useEquationNumbers()
{
	iqEI = std::static_pointer_cast<EndFrameqc>(efrmI)->iqE();
}

void MbD::ConstVelConstraintIqcJc::fillpFpy(SpMatDsptr mat)
{
	mat->atandplusFullRow(iG, iqEI, pGpEI);
	mat->atandplusFullMatrixtimes(iqEI, iqEI, ppGpEIpEI, lam);
}

void MbD::ConstVelConstraintIqcJc::fillpFpydot(SpMatDsptr mat)
{
	mat->atandplusFullColumn(iqEI, iG, pGpEI->transpose());
}
