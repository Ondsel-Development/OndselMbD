/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "System.h"
#include "AllowZRotation.h"
#include "FullColumn.h"
#include "AllowZRotationConstraintIqctJqc.h"
#include "EndFrameqc.h"
#include "EndFrameqct.h"
#include "RedundantConstraint.h"

using namespace MbD;
//
//MbD::AllowZRotation::AllowZRotation()
//{
//	//Do nothing.
//}

MbD::AllowZRotation::AllowZRotation(const char* str) : PrescribedMotion(str) 
{
	assert(false);
}

std::shared_ptr<AllowZRotation> MbD::AllowZRotation::With()
{
	auto inst = std::make_shared<AllowZRotation>();
	inst->initialize();
	return inst;
}

std::shared_ptr<AllowZRotation> MbD::AllowZRotation::With(const char* str)
{
	auto inst = std::make_shared<AllowZRotation>(str);
	inst->initialize();
	return inst;
}

void MbD::AllowZRotation::initializeGlobally()
{
	if (constraints->empty()) {
		initMotions();
		auto dirCosCon = AllowZRotationConstraintIqctJqc::With(efrmI, efrmJ, 1, 0);
		addConstraint(dirCosCon);
		root()->hasChanged = true;
	}
	else {
		PrescribedMotion::initializeGlobally();
	}
}

void MbD::AllowZRotation::postPosIC()
{
	for (size_t i = 0; i < constraints->size(); i++)
	{
		auto& constraint = constraints->at(i);
		auto redunCon = RedundantConstraint::With();
		redunCon->constraint = constraint;
		constraints->at(i) = redunCon;
	}
}
