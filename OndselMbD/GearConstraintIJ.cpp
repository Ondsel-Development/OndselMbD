/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "GearConstraintIJ.h"
#include "GearConstraintIqcJqc.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<GearConstraintIJ> MbD::GearConstraintIJ::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
	assert(frmi->isEndFrameqc());
	assert(frmj->isEndFrameqc());
	auto inst = std::make_shared<GearConstraintIqcJqc>(frmi, frmj);
	inst->initorbitsIJ();
	return inst;
}

void MbD::GearConstraintIJ::initialize()
{
	ConstraintIJ::initialize();
	initorbitsIJ();
}

void MbD::GearConstraintIJ::calcPostDynCorrectorIteration()
{
	aG = orbitJeIe->value() + (ratio() * orbitIeJe->value()) - aConstant;
}

void MbD::GearConstraintIJ::initializeGlobally()
{
	orbitIeJe->initializeGlobally();
	orbitJeIe->initializeGlobally();
}

void MbD::GearConstraintIJ::initializeLocally()
{
	orbitIeJe->initializeLocally();
	orbitJeIe->initializeLocally();
}

void MbD::GearConstraintIJ::initorbitsIJ()
{
	assert(false);
}

void MbD::GearConstraintIJ::postInput()
{
	orbitIeJe->postInput();
	orbitJeIe->postInput();
	if (aConstant == std::numeric_limits<double>::min()) {
		aConstant = orbitJeIe->value() + (ratio() * orbitIeJe->value());
	}
	ConstraintIJ::postInput();
}

void MbD::GearConstraintIJ::postPosICIteration()
{
	orbitIeJe->postPosICIteration();
	orbitJeIe->postPosICIteration();
	ConstraintIJ::postPosICIteration();
}

void MbD::GearConstraintIJ::preAccIC()
{
	orbitIeJe->preAccIC();
	orbitJeIe->preAccIC();
	ConstraintIJ::preAccIC();
}

void MbD::GearConstraintIJ::prePosIC()
{
	orbitIeJe->prePosIC();
	orbitJeIe->prePosIC();
	ConstraintIJ::prePosIC();
}

void MbD::GearConstraintIJ::preVelIC()
{
	orbitIeJe->preVelIC();
	orbitJeIe->preVelIC();
	ConstraintIJ::preVelIC();
}

double MbD::GearConstraintIJ::ratio()
{
	return radiusI / radiusJ;
}

void MbD::GearConstraintIJ::simUpdateAll()
{
	orbitIeJe->simUpdateAll();
	orbitJeIe->simUpdateAll();
	ConstraintIJ::simUpdateAll();
}

void MbD::GearConstraintIJ::postDynPredictor()
{
	orbitIeJe->postDynPredictor();
	orbitJeIe->postDynPredictor();
	ConstraintIJ::postDynPredictor();
}

void MbD::GearConstraintIJ::postDynCorrectorIteration()
{
	orbitIeJe->postDynCorrectorIteration();
	orbitJeIe->postDynCorrectorIteration();
	ConstraintIJ::postDynCorrectorIteration();
}

void MbD::GearConstraintIJ::preDynOutput()
{
	orbitIeJe->preDynOutput();
	orbitJeIe->preDynOutput();
	ConstraintIJ::preDynOutput();
}

void MbD::GearConstraintIJ::postDynOutput()
{
	orbitIeJe->postDynOutput();
	orbitJeIe->postDynOutput();
	ConstraintIJ::postDynOutput();
}
