/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "ASMTRefSurface.h"

using namespace MbD;

std::shared_ptr<ASMTRefSurface> MbD::ASMTRefSurface::With()
{
	auto inst = std::make_shared<ASMTRefSurface>();
	inst->initialize();
	return inst;
}

void MbD::ASMTRefSurface::parseASMT(std::vector<std::string>&)
{
	assert(false);
}

void MbD::ASMTRefSurface::storeOnLevel(std::ofstream&, size_t)
{
	assert(false);
}
