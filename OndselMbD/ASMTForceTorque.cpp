/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "ASMTForceTorque.h"

using namespace MbD;

std::shared_ptr<ASMTForceTorque> MbD::ASMTForceTorque::With()
{
	return std::make_shared<ASMTForceTorque>();
}

void MbD::ASMTForceTorque::updateFromMbD()
{
	assert(false);
}

void MbD::ASMTForceTorque::compareResults(AnalysisType)
{
	assert(false);
}

void MbD::ASMTForceTorque::outputResults(AnalysisType)
{
	assert(false);
}
