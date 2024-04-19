/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
#include <fstream>	

#include "ASMTRevoluteJoint.h"
#include "RevoluteJoint.h"

using namespace MbD;

std::shared_ptr<ASMTRevoluteJoint> MbD::ASMTRevoluteJoint::With()
{
	auto inst = std::make_shared<ASMTRevoluteJoint>();
	inst->initialize();
	return inst;
}

std::shared_ptr<Joint> MbD::ASMTRevoluteJoint::mbdClassNew()
{
	return RevoluteJoint::With();
}

void MbD::ASMTRevoluteJoint::storeOnLevel(std::ofstream& os, size_t level)
{
	storeOnLevelString(os, level, "RevoluteJoint");
	storeOnLevelString(os, level + 1, "Name");
	storeOnLevelString(os, level + 2, name);
	ASMTItemIJ::storeOnLevel(os, level);
}

void MbD::ASMTRevoluteJoint::storeOnTimeSeries(std::ofstream& os)
{
	os << "RevoluteJointSeries\t" << fullName("") << std::endl;
	ASMTItemIJ::storeOnTimeSeries(os);
}
