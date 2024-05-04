/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
#include <fstream>	

#include "ASMTTranslationalJoint.h"
#include "TranslationalJoint.h"

using namespace MbD;

std::shared_ptr<ASMTTranslationalJoint> MbD::ASMTTranslationalJoint::With()
{
	auto inst = std::make_shared<ASMTTranslationalJoint>();
	inst->initialize();
	return inst;
}

std::shared_ptr<JointIJ> MbD::ASMTTranslationalJoint::mbdClassNew()
{
	return TranslationalJoint::With();
}

void MbD::ASMTTranslationalJoint::storeOnLevel(std::ofstream& os, size_t level)
{
	storeOnLevelString(os, level, "TranslationalJoint");
	storeOnLevelString(os, level + 1, "Name");
	storeOnLevelString(os, level + 2, name);
	ASMTItemIJ::storeOnLevel(os, level);
}

void MbD::ASMTTranslationalJoint::storeOnTimeSeries(std::ofstream& os)
{
	os << "TranslationalJointSeries\t" << fullName("") << std::endl;
	ASMTItemIJ::storeOnTimeSeries(os);
}
