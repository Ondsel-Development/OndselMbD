/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "ConstantVelocityJoint.h"
#include "System.h"
#include "AtPointConstraintIJ.h"
#include "ConstVelConstraintIJ.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<ConstantVelocityJoint> MbD::ConstantVelocityJoint::With()
{
	auto inst = std::make_shared<ConstantVelocityJoint>();
	inst->initialize();
	return inst;
}

std::shared_ptr<ConstantVelocityJoint> MbD::ConstantVelocityJoint::With(const char* str)
{
	auto inst = std::make_shared<ConstantVelocityJoint>(str);
	inst->initialize();
	return inst;
}

void MbD::ConstantVelocityJoint::initializeGlobally()
{
	if (constraints->empty())
	{
		createAtPointConstraints();
		auto constVelIJ = ConstVelConstraintIJ::With(efrmI, efrmJ);
		constVelIJ->setConstant(0.0);
		addConstraint(constVelIJ);
		root()->hasChanged = true;
	}
	else {
		JointIJ::initializeGlobally();
	}
}

void MbD::ConstantVelocityJoint::connectsItoJ(EndFrmsptr frmi, EndFrmsptr frmj)
{
	//"Subsequent prescribed motions may make frmi, frmj become prescribed end frames."
	//"Use newCopyEndFrameqc to prevent efrms from becoming EndFrameqct."

	efrmI = frmi->newCopyEndFrameqc();
	efrmJ = frmj->newCopyEndFrameqc();
}
