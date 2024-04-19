/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "Translation.h"
#include "System.h"

using namespace MbD;

MbD::Translation::Translation(const char*)
{
	assert(false);
}

std::shared_ptr<Translation> MbD::Translation::With(const char* str)
{
	auto inst = std::make_shared<Translation>();
	inst->initialize();
	return inst;
}

void MbD::Translation::initializeGlobally()
{
	if (constraints->empty()) {
		initMotions();
		addConstraint(TranslationConstraintIJ::With(frmI, frmJ, 0));
		addConstraint(TranslationConstraintIJ::With(frmI, frmJ, 1));
		addConstraint(TranslationConstraintIJ::With(frmI, frmJ, 2));
		this->root()->hasChanged = true;
	}
	else {
		PrescribedMotion::initializeGlobally();
	}
}
