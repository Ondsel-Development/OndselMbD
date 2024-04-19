/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "Orientation.h"
#include "System.h"

using namespace MbD;

MbD::Orientation::Orientation(const char*)
{
	assert(false);
}

std::shared_ptr<Orientation> MbD::Orientation::With(const char* str)
{
	auto inst = std::make_shared<Orientation>(str);
	inst->initialize();
	return inst;
}

void MbD::Orientation::initializeGlobally()
{
	if (constraints->empty()) {
		initMotions();
		addConstraint(DirectionCosineConstraintIJ::With(frmI, frmJ, 1, 0));
		addConstraint(DirectionCosineConstraintIJ::With(frmI, frmJ, 2, 0));
		addConstraint(DirectionCosineConstraintIJ::With(frmI, frmJ, 2, 1));
		this->root()->hasChanged = true;
	}
	else {
		PrescribedMotion::initializeGlobally();
	}
}
