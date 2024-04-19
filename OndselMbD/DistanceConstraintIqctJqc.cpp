/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DistanceConstraintIqctJqc.h"

using namespace MbD;

MbD::DistanceConstraintIqctJqc::DistanceConstraintIqctJqc(EndFrmsptr frmi, EndFrmsptr frmj) : DistanceConstraintIqcJqc(frmi, frmj)
{
	assert(false);
}

std::shared_ptr<DistanceConstraintIqctJqc> MbD::DistanceConstraintIqctJqc::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
	auto inst = std::make_shared<DistanceConstraintIqctJqc>(frmi, frmj);
	inst->initialize();
	return inst;
}

void MbD::DistanceConstraintIqctJqc::fillVelICError(FColDsptr col)
{
	col->atminusNumber(iG, pGpt);
}

ConstraintType MbD::DistanceConstraintIqctJqc::type()
{
	return essential;
}
