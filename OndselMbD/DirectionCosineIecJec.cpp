/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include <memory>

#include "DirectionCosineIecJec.h"
#include "FullColumn.h"
#include "EndFramec.h"

using namespace MbD;

std::shared_ptr<DirectionCosineIecJec> MbD::DirectionCosineIecJec::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj)
{
	auto inst = std::make_shared<DirectionCosineIecJec>(frmi, frmj, axisi, axisj);
	inst->initialize();
	return inst;
}

void DirectionCosineIecJec::calcPostDynCorrectorIteration()
{
	aAjOIe = efrmI->aAjOe(axisI);
	aAjOJe = efrmJ->aAjOe(axisJ);
	aAijIeJe = aAjOIe->dot(aAjOJe);
}

double MbD::DirectionCosineIecJec::value()
{
	return aAijIeJe;
}
