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

MbD::ConstantVelocityJoint::ConstantVelocityJoint(const char* str) : AtPointJoint(str)
{
	assert(false);
}

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
		auto constVelIJ = ConstVelConstraintIJ::With(frmI, frmJ);
		constVelIJ->setConstant(0.0);
		addConstraint(constVelIJ);
		this->root()->hasChanged = true;
	}
	else {
		Joint::initializeGlobally();
	}
}

void MbD::ConstantVelocityJoint::connectsItoJ(EndFrmsptr frmIe, EndFrmsptr frmJe)
{
	//"Subsequent prescribed motions may make frmIe, frmJe become prescribed end frames."
	//"Use newCopyEndFrameqc to prevent efrms from becoming EndFrameqct."

	frmI = frmIe->newCopyEndFrameqc();
	frmJ = frmJe->newCopyEndFrameqc();
}
