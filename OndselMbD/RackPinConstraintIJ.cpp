/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "RackPinConstraintIJ.h"
#include "RackPinConstraintIqcJqc.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<RackPinConstraintIJ> MbD::RackPinConstraintIJ::With()
{
	auto inst = std::make_shared<RackPinConstraintIJ>();
	inst->initialize();
	return inst;
}

std::shared_ptr<RackPinConstraintIJ> MbD::RackPinConstraintIJ::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
	assert(frmi->isEndFrameqc());
	assert(frmj->isEndFrameqc());
	auto inst = std::make_shared<RackPinConstraintIqcJqc>(frmi, frmj);
	inst->initialize();
	return inst;
}

void MbD::RackPinConstraintIJ::initialize()
{
	ConstraintIJ::initialize();
	initxIeJeIe();
	initthezIeJe();
}

void MbD::RackPinConstraintIJ::calcPostDynCorrectorIteration()
{
	auto x = xIeJeIe->value();
	auto thez = thezIeJe->value();
	aG = x + (pitchRadius * thez) - aConstant;
}

void MbD::RackPinConstraintIJ::initxIeJeIe()
{
	assert(false);
}

void MbD::RackPinConstraintIJ::initthezIeJe()
{
	assert(false);
}

void MbD::RackPinConstraintIJ::initializeGlobally()
{
	xIeJeIe->initializeGlobally();
	thezIeJe->initializeGlobally();
}

void MbD::RackPinConstraintIJ::initializeLocally()
{
	xIeJeIe->initializeLocally();
	thezIeJe->initializeLocally();
}

void MbD::RackPinConstraintIJ::postInput()
{
	xIeJeIe->postInput();
	thezIeJe->postInput();
	if (aConstant == std::numeric_limits<double>::min()) {
		aConstant = xIeJeIe->value() + (pitchRadius * thezIeJe->value());
	}
	ConstraintIJ::postInput();
}

void MbD::RackPinConstraintIJ::postPosICIteration()
{
	xIeJeIe->postPosICIteration();
	thezIeJe->postPosICIteration();
	ConstraintIJ::postPosICIteration();
}

void MbD::RackPinConstraintIJ::preAccIC()
{
	xIeJeIe->preAccIC();
	thezIeJe->preAccIC();
	ConstraintIJ::preAccIC();
}

void MbD::RackPinConstraintIJ::prePosIC()
{
	xIeJeIe->prePosIC();
	thezIeJe->prePosIC();
	ConstraintIJ::prePosIC();
}

void MbD::RackPinConstraintIJ::preVelIC()
{
	xIeJeIe->preVelIC();
	thezIeJe->preVelIC();
	ConstraintIJ::preVelIC();
}

void MbD::RackPinConstraintIJ::simUpdateAll()
{
	xIeJeIe->simUpdateAll();
	thezIeJe->simUpdateAll();
	ConstraintIJ::simUpdateAll();
}

void MbD::RackPinConstraintIJ::postDynPredictor()
{
	xIeJeIe->postDynPredictor();
	thezIeJe->postDynPredictor();
	ConstraintIJ::postDynPredictor();
}

void MbD::RackPinConstraintIJ::postDynCorrectorIteration()
{
	xIeJeIe->postDynCorrectorIteration();
	thezIeJe->postDynCorrectorIteration();
	ConstraintIJ::postDynCorrectorIteration();
}

void MbD::RackPinConstraintIJ::preDynOutput()
{
	xIeJeIe->preDynOutput();
	thezIeJe->preDynOutput();
	ConstraintIJ::preDynOutput();
}

void MbD::RackPinConstraintIJ::postDynOutput()
{
	xIeJeIe->postDynOutput();
	thezIeJe->postDynOutput();
	ConstraintIJ::postDynOutput();
}
