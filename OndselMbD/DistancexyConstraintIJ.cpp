/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DistancexyConstraintIJ.h"
#include "DistancexyConstraintIqcJqc.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<DistancexyConstraintIJ> MbD::DistancexyConstraintIJ::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
	assert(frmi->isEndFrameqc());
	assert(frmj->isEndFrameqc());
	auto inst = std::make_shared<DistancexyConstraintIqcJqc>(frmi, frmj);
	inst->init_xyIeJeIe();
	return inst;
}

void MbD::DistancexyConstraintIJ::initialize()
{
	ConstraintIJ::initialize();
	init_xyIeJeIe();
}

void MbD::DistancexyConstraintIJ::calcPostDynCorrectorIteration()
{
	auto x = xIeJeIe->value();
	auto y = yIeJeIe->value();
	aG = x * x + (y * y) - (aConstant * aConstant);
}

void MbD::DistancexyConstraintIJ::init_xyIeJeIe()
{
	assert(false);
}

void MbD::DistancexyConstraintIJ::initializeGlobally()
{
	xIeJeIe->initializeGlobally();
	yIeJeIe->initializeGlobally();
}

void MbD::DistancexyConstraintIJ::initializeLocally()
{
	xIeJeIe->initializeLocally();
	yIeJeIe->initializeLocally();
}

void MbD::DistancexyConstraintIJ::postInput()
{
	xIeJeIe->postInput();
	yIeJeIe->postInput();
	ConstraintIJ::postInput();
}

void MbD::DistancexyConstraintIJ::postPosICIteration()
{
	xIeJeIe->postPosICIteration();
	yIeJeIe->postPosICIteration();
	ConstraintIJ::postPosICIteration();
}

void MbD::DistancexyConstraintIJ::preAccIC()
{
	xIeJeIe->preAccIC();
	yIeJeIe->preAccIC();
	ConstraintIJ::preAccIC();
}

void MbD::DistancexyConstraintIJ::prePosIC()
{
	xIeJeIe->prePosIC();
	yIeJeIe->prePosIC();
	ConstraintIJ::prePosIC();
}

void MbD::DistancexyConstraintIJ::preVelIC()
{
	xIeJeIe->preVelIC();
	yIeJeIe->preVelIC();
	ConstraintIJ::preVelIC();
}

void MbD::DistancexyConstraintIJ::simUpdateAll()
{
	xIeJeIe->simUpdateAll();
	yIeJeIe->simUpdateAll();
	ConstraintIJ::simUpdateAll();
}

ConstraintType MbD::DistancexyConstraintIJ::type()
{
	return displacement;
}

void MbD::DistancexyConstraintIJ::postDynPredictor()
{
	xIeJeIe->postDynPredictor();
	yIeJeIe->postDynPredictor();
	ConstraintIJ::postDynPredictor();
}

void MbD::DistancexyConstraintIJ::postDynCorrectorIteration()
{
	xIeJeIe->postDynCorrectorIteration();
	yIeJeIe->postDynCorrectorIteration();
	ConstraintIJ::postDynCorrectorIteration();
}

void MbD::DistancexyConstraintIJ::preDynOutput()
{
	xIeJeIe->preDynOutput();
	yIeJeIe->preDynOutput();
	ConstraintIJ::preDynOutput();
}

void MbD::DistancexyConstraintIJ::postDynOutput()
{
	xIeJeIe->postDynOutput();
	yIeJeIe->postDynOutput();
	ConstraintIJ::postDynOutput();
}
