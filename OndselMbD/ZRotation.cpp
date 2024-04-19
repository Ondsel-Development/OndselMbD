/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "System.h"
#include "ZRotation.h"
#include "FullColumn.h"
#include "DirectionCosineConstraintIJ.h"
#include "EndFrameqc.h"
#include "EndFrameqct.h"

using namespace MbD;

ZRotation::ZRotation(const char* str) : PrescribedMotion(str) {
	assert(false);
}

std::shared_ptr<ZRotation> MbD::ZRotation::With()
{
	auto inst = std::make_shared<ZRotation>();
	inst->initialize();
	return inst;
}

std::shared_ptr<ZRotation> MbD::ZRotation::With(const char* str)
{
	auto inst = std::make_shared<ZRotation>(str);
	inst->initialize();
	return inst;
}

void ZRotation::initializeGlobally()
{
	if (constraints->empty()) {
		initMotions();
		auto dirCosCon = DirectionCosineConstraintIJ::With(frmI, frmJ, 1, 0);
		addConstraint(dirCosCon);
		this->root()->hasChanged = true;
	}
	else {
		PrescribedMotion::initializeGlobally();
	}
}
