/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "FullMotion.h"
#include "System.h"
#include "TranslationConstraintIJ.h"
#include "DirectionCosineConstraintIJ.h"
#include "EndFrameqct.h"

using namespace MbD;

MbD::FullMotion::FullMotion(const char*)
{
	assert(false);
}

std::shared_ptr<FullMotion> MbD::FullMotion::With()
{
	auto inst = std::make_shared<FullMotion>();
	inst->initialize();
	return inst;
}

std::shared_ptr<FullMotion> MbD::FullMotion::With(const char* str)
{
	auto inst = std::make_shared<FullMotion>(str);
	inst->initialize();
	return inst;
}

void MbD::FullMotion::connectsItoJ(EndFrmsptr frmi, EndFrmsptr frmj)
{
	Joint::connectsItoJ(frmi, frmj);
	std::static_pointer_cast<EndFrameqc>(frmI)->initEndFrameqct2();
}

void MbD::FullMotion::initializeGlobally()
{
	if (constraints->empty()) {
		initMotions();
		addConstraint(TranslationConstraintIJ::With(frmI, frmJ, 0));
		addConstraint(TranslationConstraintIJ::With(frmI, frmJ, 1));
		addConstraint(TranslationConstraintIJ::With(frmI, frmJ, 2));
		addConstraint(DirectionCosineConstraintIJ::With(frmI, frmJ, 1, 0));
		addConstraint(DirectionCosineConstraintIJ::With(frmI, frmJ, 2, 0));
		addConstraint(DirectionCosineConstraintIJ::With(frmI, frmJ, 2, 1));
		this->root()->hasChanged = true;
	}
	else {
		PrescribedMotion::initializeGlobally();
	}
}

void MbD::FullMotion::initMotions()
{
	auto efrmI = std::static_pointer_cast<EndFrameqct>(frmI);
	efrmI->rmemBlks = frIJI;
	efrmI->phiThePsiBlks = fangIJJ;
}
