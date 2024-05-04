/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "ZTranslation.h"
#include "System.h"

using namespace MbD;

MbD::ZTranslation::ZTranslation(const char*)
{
	assert(false);
}

std::shared_ptr<ZTranslation> MbD::ZTranslation::With()
{
	auto inst = std::make_shared<ZTranslation>();
	inst->initialize();
	return inst;
}

std::shared_ptr<ZTranslation> MbD::ZTranslation::With(const char* str)
{
	auto inst = std::make_shared<ZTranslation>(str);
	inst->initialize();
	return inst;
}

void MbD::ZTranslation::initializeGlobally()
{
	if (constraints->empty()) {
		initMotions();
		auto tranCon = TranslationConstraintIJ::With(efrmI, efrmJ, 2);
		addConstraint(tranCon);
		root()->hasChanged = true;
	}
	else {
		PrescribedMotion::initializeGlobally();
	}
}
