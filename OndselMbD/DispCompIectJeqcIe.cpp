/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "DispCompIectJeqcIe.h"
#include "EndFramect.h"

using namespace MbD;

std::shared_ptr<DispCompIectJeqcIe> MbD::DispCompIectJeqcIe::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axis)
{
	auto inst = std::make_shared<DispCompIectJeqcIe>(frmi, frmj, axis);
	inst->initialize();
	return inst;
}

void MbD::DispCompIectJeqcIe::initialize()
{
	DispCompIecJeqcIe::initialize();
	ppriIeJeIepXJpt = FullRow<double>::With(3);
	ppriIeJeIepEJpt = FullRow<double>::With(4);
}

void MbD::DispCompIectJeqcIe::calc_ppvaluepEJpt()
{
	auto frmIeqct = std::static_pointer_cast<EndFramect>(efrmI);
	auto frmJeqc = std::static_pointer_cast<EndFrameqc>(efrmJ);
	auto pAjOIept = frmIeqct->pAjOept(axis);
	auto prIeJeOpEJT = frmJeqc->prOeOpE->transpose();
	for (size_t i = 0; i < 4; i++)
	{
		ppriIeJeIepEJpt->atput(i, pAjOIept->dot(prIeJeOpEJT->at(i)));
	}
}

void MbD::DispCompIectJeqcIe::calc_ppvalueptpt()
{
	auto frmIeqct = std::static_pointer_cast<EndFramect>(efrmI);
	auto pAjOIept = frmIeqct->pAjOept(axis);
	auto ppAjOIeptpt = frmIeqct->ppAjOeptpt(axis);
	auto mprIeJeOpt = frmIeqct->prOeOpt;
	auto mpprIeJeOptpt = frmIeqct->pprOeOptpt;
	ppriIeJeIeptpt = ppAjOIeptpt->dot(rIeJeO) - pAjOIept->dot(mprIeJeOpt) - pAjOIept->dot(mprIeJeOpt) - aAjOIe->dot(mpprIeJeOptpt);
}

void MbD::DispCompIectJeqcIe::calc_ppvaluepXJpt()
{
	auto frmIeqct = std::static_pointer_cast<EndFramect>(efrmI);
	auto pAjOIept = frmIeqct->pAjOept(axis);
	for (size_t i = 0; i < 3; i++)
	{
		ppriIeJeIepXJpt->atput(i, pAjOIept->at(i));
	}
}

void MbD::DispCompIectJeqcIe::calc_pvaluept()
{
	auto frmIeqct = std::static_pointer_cast<EndFramect>(efrmI);
	auto pAjOIept = frmIeqct->pAjOept(axis);
	auto mprIeJeOpt = frmIeqct->prOeOpt;
	priIeJeIept = pAjOIept->dot(rIeJeO) - aAjOIe->dot(mprIeJeOpt);
}

void MbD::DispCompIectJeqcIe::initializeGlobally()
{
	//"Do nothing."
}

void MbD::DispCompIectJeqcIe::preAccIC()
{
	DispCompIecJeqcIe::preAccIC();
	calc_ppvaluepXJpt();
	calc_ppvaluepEJpt();
	calc_ppvalueptpt();
}

void MbD::DispCompIectJeqcIe::preVelIC()
{
	DispCompIecJeqcIe::preVelIC();
	calc_pvaluept();
}

FRowDsptr MbD::DispCompIectJeqcIe::ppvaluepEJpt()
{
	return ppriIeJeIepEJpt;
}

double MbD::DispCompIectJeqcIe::ppvalueptpt()
{
	return ppriIeJeIeptpt;
}

FRowDsptr MbD::DispCompIectJeqcIe::ppvaluepXJpt()
{
	return ppriIeJeIepXJpt;
}

double MbD::DispCompIectJeqcIe::pvaluept()
{
	return priIeJeIept;
}
