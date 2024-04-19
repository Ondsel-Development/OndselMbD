/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselMbD.									   *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "ConstantGravity.h"
#include "System.h"
#include "Part.h"

using namespace MbD;

std::shared_ptr<ConstantGravity> MbD::ConstantGravity::With()
{
	auto inst = std::make_shared<ConstantGravity>();
	inst->initialize();
	return inst;
}

void MbD::ConstantGravity::fillAccICIterError(FColDsptr col)
{
	fillDynError(col);
}

void MbD::ConstantGravity::fillDynError(FColDsptr col)
{
	for (auto& part : *(root()->parts)) {
		col->atplusFullColumntimes(part->iqX(), gXYZ, part->m);
	}
}

void MbD::ConstantGravity::fillStaticError(FColDsptr col)
{
	fillDynError(col);
}

void MbD::ConstantGravity::postAccICIteration()
{
	//Do nothing.
}

void MbD::ConstantGravity::postDynCorrectorIteration()
{
	//Do nothing.
}

void MbD::ConstantGravity::preDynOutput()
{
	//Do nothing.
}

void MbD::ConstantGravity::postDynPredictor()
{
	//Do nothing.
}

void MbD::ConstantGravity::postInput()
{
	//Do nothing.
}

void MbD::ConstantGravity::postStaticIteration()
{
	//Do nothing.
}

void MbD::ConstantGravity::preAccIC()
{
	//Do nothing.
}

void MbD::ConstantGravity::postDynOutput()
{
	//Do nothing.
}

void MbD::ConstantGravity::preStatic()
{
	//Do nothing.
}

void MbD::ConstantGravity::simUpdateAll()
{
	//Do nothing.
}
