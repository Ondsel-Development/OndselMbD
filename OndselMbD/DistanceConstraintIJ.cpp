/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DistanceConstraintIJ.h"
#include "DistanceConstraintIqcJqc.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<DistanceConstraintIJ> MbD::DistanceConstraintIJ::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
	assert(frmi->isEndFrameqc());
	assert(frmj->isEndFrameqc());
	auto inst = std::make_shared<DistanceConstraintIqcJqc>(frmi, frmj);
	inst->init_distIeJe();
	return inst;
}

void MbD::DistanceConstraintIJ::initialize()
{
	ConstraintIJ::initialize();
	init_distIeJe();
}

void MbD::DistanceConstraintIJ::calcPostDynCorrectorIteration()
{
aG = distIeJe->value() - aConstant;
}

void MbD::DistanceConstraintIJ::init_distIeJe()
{
	assert(false);
}

void MbD::DistanceConstraintIJ::initializeGlobally()
{
	distIeJe->initializeGlobally();
}

void MbD::DistanceConstraintIJ::initializeLocally()
{
	distIeJe->initializeLocally();
}

void MbD::DistanceConstraintIJ::postInput()
{
	distIeJe->postInput();
	ConstraintIJ::postInput();
}

void MbD::DistanceConstraintIJ::postPosICIteration()
{
	distIeJe->postPosICIteration();
	ConstraintIJ::postPosICIteration();
}

void MbD::DistanceConstraintIJ::preAccIC()
{
	distIeJe->preAccIC();
	ConstraintIJ::preAccIC();
}

void MbD::DistanceConstraintIJ::prePosIC()
{
	distIeJe->prePosIC();
	ConstraintIJ::prePosIC();
}

void MbD::DistanceConstraintIJ::preVelIC()
{
	distIeJe->preVelIC();
	ConstraintIJ::preVelIC();
}

void MbD::DistanceConstraintIJ::simUpdateAll()
{
	distIeJe->simUpdateAll();
	ConstraintIJ::simUpdateAll();
}

ConstraintType MbD::DistanceConstraintIJ::type()
{
	return ConstraintType::displacement;
}

void MbD::DistanceConstraintIJ::postDynPredictor()
{
	distIeJe->postDynPredictor();
	ConstraintIJ::postDynPredictor();
}

void MbD::DistanceConstraintIJ::postDynCorrectorIteration()
{
	distIeJe->postDynCorrectorIteration();
	ConstraintIJ::postDynCorrectorIteration();
}

void MbD::DistanceConstraintIJ::preDynOutput()
{
	distIeJe->preDynOutput();
	ConstraintIJ::preDynOutput();
}

void MbD::DistanceConstraintIJ::postDynOutput()
{
	distIeJe->postDynOutput();
	ConstraintIJ::postDynOutput();
}
