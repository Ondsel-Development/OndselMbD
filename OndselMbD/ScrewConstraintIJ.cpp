/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "corecrt_math_defines.h"

#include "ScrewConstraintIJ.h"
#include "ScrewConstraintIqcJqc.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<ScrewConstraintIJ> MbD::ScrewConstraintIJ::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
	assert(frmi->isEndFrameqc());
	assert(frmj->isEndFrameqc());
	auto inst = std::make_shared<ScrewConstraintIqcJqc>(frmi, frmj);
	inst->initialize();
	return inst;
}

void MbD::ScrewConstraintIJ::initialize()
{
	ConstraintIJ::initialize();
	initzIeJeIe();
	initthezIeJe();
}

void MbD::ScrewConstraintIJ::calcPostDynCorrectorIteration()
{
	auto z = zIeJeIe->value();
	auto thez = thezIeJe->thez;
	aG = (2.0 * OS_M_PI * z) - (pitch * thez) - aConstant;
}

void MbD::ScrewConstraintIJ::initzIeJeIe()
{
	assert(false);
}

void MbD::ScrewConstraintIJ::initthezIeJe()
{
	assert(false);
}

void MbD::ScrewConstraintIJ::initializeGlobally()
{
	zIeJeIe->initializeGlobally();
	thezIeJe->initializeGlobally();
}

void MbD::ScrewConstraintIJ::initializeLocally()
{
	zIeJeIe->initializeLocally();
	thezIeJe->initializeLocally();
}

void MbD::ScrewConstraintIJ::postInput()
{
	zIeJeIe->postInput();
	thezIeJe->postInput();
	aConstant = (2.0 * OS_M_PI * zIeJeIe->value()) - (thezIeJe->value() * pitch);
	ConstraintIJ::postInput();
}

void MbD::ScrewConstraintIJ::postPosICIteration()
{
	zIeJeIe->postPosICIteration();
	thezIeJe->postPosICIteration();
	ConstraintIJ::postPosICIteration();
}

void MbD::ScrewConstraintIJ::preAccIC()
{
	zIeJeIe->preAccIC();
	thezIeJe->preAccIC();
	ConstraintIJ::preAccIC();
}

void MbD::ScrewConstraintIJ::prePosIC()
{
	zIeJeIe->prePosIC();
	thezIeJe->prePosIC();
	ConstraintIJ::prePosIC();
}

void MbD::ScrewConstraintIJ::preVelIC()
{
	zIeJeIe->preVelIC();
	thezIeJe->preVelIC();
	ConstraintIJ::preVelIC();
}

void MbD::ScrewConstraintIJ::simUpdateAll()
{
	zIeJeIe->simUpdateAll();
	thezIeJe->simUpdateAll();
	ConstraintIJ::simUpdateAll();
}

void MbD::ScrewConstraintIJ::postDynPredictor()
{
	zIeJeIe->postDynPredictor();
	thezIeJe->postDynPredictor();
	ConstraintIJ::postDynPredictor();
}

void MbD::ScrewConstraintIJ::postDynCorrectorIteration()
{
	zIeJeIe->postDynCorrectorIteration();
	thezIeJe->postDynCorrectorIteration();
	ConstraintIJ::postDynCorrectorIteration();
}

void MbD::ScrewConstraintIJ::preDynOutput()
{
	zIeJeIe->preDynOutput();
	thezIeJe->preDynOutput();
	ConstraintIJ::preDynOutput();
}

void MbD::ScrewConstraintIJ::postDynOutput()
{
	zIeJeIe->postDynOutput();
	thezIeJe->postDynOutput();
	ConstraintIJ::postDynOutput();
}
