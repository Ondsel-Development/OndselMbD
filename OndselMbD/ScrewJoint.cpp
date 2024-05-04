/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "ScrewJoint.h"
#include "System.h"
#include "ScrewConstraintIJ.h"

using namespace MbD;

std::shared_ptr<ScrewJoint> MbD::ScrewJoint::With()
{
	auto inst = std::make_shared<ScrewJoint>();
	inst->initialize();
	return inst;
}

std::shared_ptr<ScrewJoint> MbD::ScrewJoint::With(const char* str)
{
	auto inst = std::make_shared<ScrewJoint>(str);
	inst->initialize();
	return inst;
}

void MbD::ScrewJoint::initializeGlobally()
{
	if (constraints->empty())
	{
		auto screwIJ = ScrewConstraintIJ::With(efrmI, efrmJ);
		screwIJ->setConstant(std::numeric_limits<double>::min());
		screwIJ->pitch = pitch;
		addConstraint(screwIJ);
		root()->hasChanged = true;
	}
	else {
		JointIJ::initializeGlobally();
	}
}

void MbD::ScrewJoint::connectsItoJ(EndFrmsptr frmi, EndFrmsptr frmj)
{
	//"Subsequent prescribed motions may make frmi, frmj become prescribed end frames."
	//"Use newCopyEndFrameqc to prevent efrms from becoming EndFrameqct."

	efrmI = frmi->newCopyEndFrameqc();
	efrmJ = frmj->newCopyEndFrameqc();
}
