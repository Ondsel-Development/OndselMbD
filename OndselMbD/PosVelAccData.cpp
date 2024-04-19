/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include <ostream>

#include "PosVelAccData.h"

using namespace MbD;

std::shared_ptr<PosVelAccData> MbD::PosVelAccData::With()
{
	auto inst = std::make_shared<PosVelAccData>();
	inst->initialize();
	return inst;
}

std::ostream& PosVelAccData::printOn(std::ostream& s) const
{
	s << "refData = " << *refData << std::endl;
	s << "rFfF = " << *rFfF << std::endl;
	s << "vFfF = " << *vFfF << std::endl;
	s << "omeFfF = " << *omeFfF << std::endl;
	s << "aFfF = " << *aFfF << std::endl;
	s << "alpFfF = " << *alpFfF << std::endl;
	s << "aAFf = " << *aAFf;
	return s;
}
