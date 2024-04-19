/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "TranslationalJoint.h"
#include "System.h"
#include "DirectionCosineConstraintIJ.h"
#include "TranslationConstraintIJ.h"

using namespace MbD;

MbD::TranslationalJoint::TranslationalJoint(const char* str) : InLineJoint(str)
{
	assert(false);
}

std::shared_ptr<TranslationalJoint> MbD::TranslationalJoint::With()
{
	auto inst = std::make_shared<TranslationalJoint>();
	inst->initialize();
	return inst;
}

std::shared_ptr<TranslationalJoint> MbD::TranslationalJoint::With(const char* str)
{
	auto inst = std::make_shared<TranslationalJoint>(str);
	inst->initialize();
	return inst;
}

void MbD::TranslationalJoint::initializeGlobally()
{
	if (constraints->empty())
	{
		createInLineConstraints();
		addConstraint(DirectionCosineConstraintIJ::With(frmI, frmJ, 1, 0));
		addConstraint(DirectionCosineConstraintIJ::With(frmI, frmJ, 2, 0));
		addConstraint(DirectionCosineConstraintIJ::With(frmI, frmJ, 2, 1));
		this->root()->hasChanged = true;
	}
	else {
		Joint::initializeGlobally();
	}
}
