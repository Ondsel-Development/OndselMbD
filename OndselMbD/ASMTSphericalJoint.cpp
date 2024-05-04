/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
#include <fstream>	

#include "ASMTSphericalJoint.h"
#include "SphericalJoint.h"

using namespace MbD;

std::shared_ptr<ASMTSphericalJoint> MbD::ASMTSphericalJoint::With()
{
	auto inst = std::make_shared<ASMTSphericalJoint>();
	inst->initialize();
	return inst;
}

std::shared_ptr<JointIJ> MbD::ASMTSphericalJoint::mbdClassNew()
{
	return SphericalJoint::With();
}

void MbD::ASMTSphericalJoint::storeOnLevel(std::ofstream& os, size_t level)
{
	storeOnLevelString(os, level, "SphericalJoint");
	storeOnLevelString(os, level + 1, "Name");
	storeOnLevelString(os, level + 2, name);
	ASMTItemIJ::storeOnLevel(os, level);
}

void MbD::ASMTSphericalJoint::storeOnTimeSeries(std::ofstream& os)
{
	os << "SphericalJointSeries\t" << fullName("") << std::endl;
	ASMTItemIJ::storeOnTimeSeries(os);
}
