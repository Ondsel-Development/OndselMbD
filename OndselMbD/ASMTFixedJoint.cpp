/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
#include <fstream>	

#include "ASMTFixedJoint.h"
#include "FixedJoint.h"

using namespace MbD;

std::shared_ptr<ASMTFixedJoint> MbD::ASMTFixedJoint::With()
{
	auto inst = std::make_shared<ASMTFixedJoint>();
	inst->initialize();
	return inst;
}

std::shared_ptr<JointIJ> MbD::ASMTFixedJoint::mbdClassNew()
{
	return FixedJoint::With();
}

void MbD::ASMTFixedJoint::storeOnLevel(std::ofstream& os, size_t level)
{
	storeOnLevelString(os, level, "FixedJoint");
	storeOnLevelString(os, level + 1, "Name");
	storeOnLevelString(os, level + 2, name);
	ASMTItemIJ::storeOnLevel(os, level);
}

void MbD::ASMTFixedJoint::storeOnTimeSeries(std::ofstream& os)
{
	os << "FixedJointSeries\t" << fullName("") << std::endl;
	ASMTItemIJ::storeOnTimeSeries(os);
}
