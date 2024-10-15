/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DistIecJec.h"
#include "EndFrameqct.h"
#include "EndFrameqc.h"
#include "EndFramect.h"
#include "EndFramec.h"
#include "DistIeqctJeqc.h"
#include "DistIeqcJeqc.h"
#include "DistIecJeqc.h"

using namespace MbD;

std::shared_ptr<DistIecJec> MbD::DistIecJec::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
	std::shared_ptr<DistIecJec> inst;
	if (std::dynamic_pointer_cast<EndFrameqct>(frmi)) {
		if (std::dynamic_pointer_cast<EndFrameqct>(frmj)) {
			assert(false);
		}
		else if (std::dynamic_pointer_cast<EndFrameqc>(frmj)) {
			inst = std::make_shared<DistIeqctJeqc>(frmi, frmj);
		}
		else if (std::dynamic_pointer_cast<EndFramect>(frmj)) {
			assert(false);
		}
		else if (std::dynamic_pointer_cast<EndFramec>(frmj)) {
			assert(false);
		}
	}
	else if (std::dynamic_pointer_cast<EndFrameqc>(frmi)) {
		if (std::dynamic_pointer_cast<EndFrameqct>(frmj)) {
			assert(false);
		}
		else if (std::dynamic_pointer_cast<EndFrameqc>(frmj)) {
			inst = std::make_shared<DistIeqcJeqc>(frmi, frmj);
		}
		else if (std::dynamic_pointer_cast<EndFramect>(frmj)) {
			assert(false);
		}
		else if (std::dynamic_pointer_cast<EndFramec>(frmj)) {
			inst = std::make_shared<DistIeqcJec>(frmi, frmj);
		}
	}
	else if (std::dynamic_pointer_cast<EndFramect>(frmi)) {
		if (std::dynamic_pointer_cast<EndFrameqct>(frmj)) {
			assert(false);
		}
		else if (std::dynamic_pointer_cast<EndFrameqc>(frmj)) {
			assert(false);
		}
		else if (std::dynamic_pointer_cast<EndFramect>(frmj)) {
			assert(false);
		}
		else if (std::dynamic_pointer_cast<EndFramec>(frmj)) {
			assert(false);
		}
	}
	else if (std::dynamic_pointer_cast<EndFramec>(frmi)) {
		if (std::dynamic_pointer_cast<EndFrameqct>(frmj)) {
			assert(false);
		}
		else if (std::dynamic_pointer_cast<EndFrameqc>(frmj)) {
			inst = std::make_shared<DistIecJeqc>(frmi, frmj);
		}
		else if (std::dynamic_pointer_cast<EndFramect>(frmj)) {
			assert(false);
		}
		else if (std::dynamic_pointer_cast<EndFramec>(frmj)) {
			assert(false);
		}
	}
	assert(inst);
	inst->initialize();
	return inst;
}

void MbD::DistIecJec::calcPostDynCorrectorIteration()
{
	rIeJeO = efrmJ->rOeO->minusFullColumn(efrmI->rOeO);
	rIeJe = rIeJeO->length();
	calcPrivate();
}

void MbD::DistIecJec::calcPrivate()
{
	if (rIeJe == 0.0) return;
	uIeJeO = rIeJeO->times(1.0 / rIeJe);
	muIeJeO = uIeJeO->negated();
}

double MbD::DistIecJec::value()
{
	return rIeJe;
}

FColDsptr MbD::DistIecJec::rIeJeIe()
{
	return FColDsptr();
}
