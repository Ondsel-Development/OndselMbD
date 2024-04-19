/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "DispCompIecJecKec.h"
#include "EndFramec.h"

using namespace MbD;

std::shared_ptr<DispCompIecJecKec> MbD::DispCompIecJecKec::With(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk, size_t axisk)
{
	auto inst = std::make_shared<DispCompIecJecKec>(frmi, frmj, frmk, axisk);
	inst->initialize();
	return inst;
}

PartFrame* MbD::DispCompIecJecKec::partFrameK()
{
	return efrmK->getPartFrame();
}

double DispCompIecJecKec::value()
{
	return riIeJeKe;
}
