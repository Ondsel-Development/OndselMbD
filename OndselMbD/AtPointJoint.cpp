/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "AtPointJoint.h"
#include "System.h"
#include "AtPointConstraintIJ.h"

using namespace MbD;

MbD::AtPointJoint::AtPointJoint(const char* str) : Joint(str)
{
	assert(false);
}

std::shared_ptr<AtPointJoint> MbD::AtPointJoint::With()
{
	auto inst = std::make_shared<AtPointJoint>();
	inst->initialize();
	return inst;
}

std::shared_ptr<AtPointJoint> MbD::AtPointJoint::With(const char* str)
{
	auto inst = std::make_shared<AtPointJoint>(str);
	inst->initialize();
	return inst;
}

void MbD::AtPointJoint::createAtPointConstraints()
{
	addConstraint(AtPointConstraintIJ::With(frmI, frmJ, 0));
	addConstraint(AtPointConstraintIJ::With(frmI, frmJ, 1));
	addConstraint(AtPointConstraintIJ::With(frmI, frmJ, 2));
}
