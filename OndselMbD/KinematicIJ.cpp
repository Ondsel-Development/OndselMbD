/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "KinematicIJ.h"
#include "EndFramec.h"
#include "SpatialContainerFrame.h"

using namespace MbD;

std::shared_ptr<KinematicIJ> MbD::KinematicIJ::With()
{
	auto inst = std::make_shared<KinematicIJ>();
	inst->initialize();
	return inst;
}

std::shared_ptr<KinematicIJ> MbD::KinematicIJ::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
	auto inst = std::make_shared<KinematicIJ>(frmi, frmj);
	inst->initialize();
	return inst;
}

bool MbD::KinematicIJ::isKineIJ()
{
	return true;
}

void MbD::KinematicIJ::calc_pvaluepXI()
{
	assert(false);
}

void MbD::KinematicIJ::calc_pvaluepEI()
{
	assert(false);
}

void MbD::KinematicIJ::calc_ppvaluepXIpXI()
{
	assert(false);
}

void MbD::KinematicIJ::calc_ppvaluepXIpEI()
{
	assert(false);
}

void MbD::KinematicIJ::calc_ppvaluepEIpEI()
{
	assert(false);
}

void MbD::KinematicIJ::calc_pvaluepXJ()
{
	assert(false);
}

void MbD::KinematicIJ::calc_pvaluepEJ()
{
	assert(false);
}

void MbD::KinematicIJ::calc_ppvaluepXIpXJ()
{
	assert(false);
}

void MbD::KinematicIJ::calc_ppvaluepXIpEJ()
{
	assert(false);
}

void MbD::KinematicIJ::calc_ppvaluepEIpXJ()
{
	assert(false);
}

void MbD::KinematicIJ::calc_ppvaluepEIpEJ()
{
	assert(false);
}

void MbD::KinematicIJ::calc_ppvaluepXJpXJ()
{
	assert(false);
}

void MbD::KinematicIJ::calc_ppvaluepXJpEJ()
{
	assert(false);
}

void MbD::KinematicIJ::calc_ppvaluepEJpEJ()
{
	assert(false);
}

void MbD::KinematicIJ::calc_pvaluepXK()
{
	assert(false);
}

void MbD::KinematicIJ::calc_pvaluepEK()
{
	assert(false);
}

void MbD::KinematicIJ::calc_ppvaluepXIpEK()
{
	assert(false);
}

void MbD::KinematicIJ::calc_ppvaluepEIpEK()
{
	assert(false);
}

void MbD::KinematicIJ::calc_ppvaluepXJpEK()
{
	assert(false);
}

void MbD::KinematicIJ::calc_ppvaluepEJpEK()
{
	assert(false);
}

void MbD::KinematicIJ::calc_ppvaluepEKpEK()
{
	assert(false);
}

void MbD::KinematicIJ::calc_pvaluept()
{
	assert(false);
}

void MbD::KinematicIJ::calc_ppvalueptpt()
{
	assert(false);
}

void MbD::KinematicIJ::calc_value()
{
	assert(false);
}

void MbD::KinematicIJ::calc_ppvaluepXIpt()
{
	assert(false);
}

void MbD::KinematicIJ::calc_ppvaluepEIpt()
{
	assert(false);
}

void MbD::KinematicIJ::calc_ppvaluepXJpt()
{
	assert(false);
}

void MbD::KinematicIJ::calc_ppvaluepEJpt()
{
	assert(false);
}

void MbD::KinematicIJ::calc_ppvaluepXKpt()
{
	assert(false);
}

void MbD::KinematicIJ::calc_ppvaluepEKpt()
{
	assert(false);
}

FRowDsptr MbD::KinematicIJ::pvaluepXI()
{
	return FRowDsptr();
}

FRowDsptr MbD::KinematicIJ::pvaluepEI()
{
	return FRowDsptr();
}

FMatDsptr MbD::KinematicIJ::ppvaluepXIpXI()
{
	assert(false);
	return FMatDsptr();
}

FMatDsptr MbD::KinematicIJ::ppvaluepXIpEI()
{
	assert(false);
	return FMatDsptr();
}

FMatDsptr MbD::KinematicIJ::ppvaluepEIpEI()
{
	assert(false);
	return FMatDsptr();
}

FRowDsptr MbD::KinematicIJ::pvaluepXJ()
{
	return FRowDsptr();
}

FRowDsptr MbD::KinematicIJ::pvaluepEJ()
{
	return FRowDsptr();
}

FMatDsptr MbD::KinematicIJ::ppvaluepXIpXJ()
{
	assert(false);
	return FMatDsptr();
}

FMatDsptr MbD::KinematicIJ::ppvaluepXIpEJ()
{
	assert(false);
	return FMatDsptr();
}

FMatDsptr MbD::KinematicIJ::ppvaluepEIpXJ()
{
	assert(false);
	return FMatDsptr();
}

FMatDsptr MbD::KinematicIJ::ppvaluepEIpEJ()
{
	assert(false);
	return FMatDsptr();
}

FMatDsptr MbD::KinematicIJ::ppvaluepXJpXJ()
{
	assert(false);
	return FMatDsptr();
}

FMatDsptr MbD::KinematicIJ::ppvaluepXJpEJ()
{
	assert(false);
	return FMatDsptr();
}

FMatDsptr MbD::KinematicIJ::ppvaluepEJpEJ()
{
	assert(false);
	return FMatDsptr();
}

FRowDsptr MbD::KinematicIJ::pvaluepXK()
{
	return FRowDsptr();
}

FRowDsptr MbD::KinematicIJ::pvaluepEK()
{
	return FRowDsptr();
}

FMatDsptr MbD::KinematicIJ::ppvaluepXIpEK()
{
	assert(false);
	return FMatDsptr();
}

FMatDsptr MbD::KinematicIJ::ppvaluepEIpEK()
{
	assert(false);
	return FMatDsptr();
}

FMatDsptr MbD::KinematicIJ::ppvaluepXJpEK()
{
	assert(false);
	return FMatDsptr();
}

FMatDsptr MbD::KinematicIJ::ppvaluepEJpEK()
{
	assert(false);
	return FMatDsptr();
}

FMatDsptr MbD::KinematicIJ::ppvaluepEKpEK()
{
	assert(false);
	return FMatDsptr();
}

FMatDsptr MbD::KinematicIJ::puIeJeOpEI()
{
	assert(false);
	return FMatDsptr();
}

FMatDsptr MbD::KinematicIJ::puIeJeOpXI()
{
	assert(false);
	return FMatDsptr();
}

FMatDsptr MbD::KinematicIJ::puIeJeOpEJ()
{
	assert(false);
	return FMatDsptr();
}

FMatDsptr MbD::KinematicIJ::puIeJeOpXJ()
{
	assert(false);
	return FMatDsptr();
}

double MbD::KinematicIJ::pvaluept()
{
	assert(false);
	return 0.0;
}

double MbD::KinematicIJ::ppvalueptpt()
{
	assert(false);
	return 0.0;
}

FRowDsptr MbD::KinematicIJ::ppvaluepXIpt()
{
	assert(false);
	return FRowDsptr();
}

FRowDsptr MbD::KinematicIJ::ppvaluepEIpt()
{
	assert(false);
	return FRowDsptr();
}

FRowDsptr MbD::KinematicIJ::ppvaluepXJpt()
{
	assert(false);
	return FRowDsptr();
}

FRowDsptr MbD::KinematicIJ::ppvaluepEJpt()
{
	assert(false);
	return FRowDsptr();
}

FRowDsptr MbD::KinematicIJ::ppvaluepXKpt()
{
	assert(false);
	return FRowDsptr();
}

FRowDsptr MbD::KinematicIJ::ppvaluepEKpt()
{
	assert(false);
	return FRowDsptr();
}

double MbD::KinematicIJ::value()
{
	assert(false);
	return 0.0;
}

void MbD::KinematicIJ::withFrmIfrmJ(EndFrmsptr eFrmi, EndFrmsptr eFrmj)
{
	efrmI = eFrmi;
	efrmJ = eFrmj;
}

void MbD::KinematicIJ::withFrmIfrmJaxis(EndFrmsptr eFrmI, EndFrmsptr eFrmJ, size_t axis)
{
	assert(false);
}

void MbD::KinematicIJ::withFrmIfrmJfrmK(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk)
{
	assert(false);
}

void MbD::KinematicIJ::withFrmIfrmJfrmKaxis(EndFrmsptr eFrmi, EndFrmsptr eFrmj, EndFrmsptr eFrmk, size_t axis)
{
}

SpatialContainerFrame* MbD::KinematicIJ::partFrameI()
{
	return efrmI->getPartFrame();
}

SpatialContainerFrame* MbD::KinematicIJ::partFrameJ()
{
	return efrmJ->getPartFrame();
}
