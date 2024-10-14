/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
//#include "DirectionCosineConstraintIJ.h"
#include "DirectionCosineConstraintIqctJqc.h"
#include "DirectionCosineConstraintIctJqc.h"
#include "DirectionCosineIeqctJeqc.h"
#include "EndFrameqct.h"
#include "EndFrameqc.h"
#include "EndFramect.h"
#include "EndFramec.h"

using namespace MbD;

std::shared_ptr<DirectionCosineConstraintIJ> MbD::DirectionCosineConstraintIJ::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj)
{
	std::shared_ptr<DirectionCosineConstraintIJ> inst;
	if (std::dynamic_pointer_cast<EndFrameqct>(frmi)) {
		if (std::dynamic_pointer_cast<EndFrameqct>(frmj)) {
			assert(false);
		}
		else if (std::dynamic_pointer_cast<EndFrameqc>(frmj)) {
			inst = std::make_shared<DirectionCosineConstraintIqctJqc>(frmi, frmj, axisi, axisj);
		}
		else if (std::dynamic_pointer_cast<EndFramect>(frmj)) {
			assert(false);
		}
		else if (std::dynamic_pointer_cast<EndFramec>(frmj)) {
			assert(false);
		}
	}
	else if (std::dynamic_pointer_cast<EndFrameqc>(frmi)) {
		if (std::dynamic_pointer_cast<EndFrameqct>(frmj)) {
			assert(false);
		}
		else if (std::dynamic_pointer_cast<EndFrameqc>(frmj)) {
			inst = std::make_shared<DirectionCosineConstraintIqcJqc>(frmi, frmj, axisi, axisj);
		}
		else if (std::dynamic_pointer_cast<EndFramect>(frmj)) {
			assert(false);
		}
		else if (std::dynamic_pointer_cast<EndFramec>(frmj)) {
			inst = std::make_shared<DirectionCosineConstraintIqcJc>(frmi, frmj, axisi, axisj);
		}
	}
	else if (std::dynamic_pointer_cast<EndFramect>(frmi)) {
		if (std::dynamic_pointer_cast<EndFrameqct>(frmj)) {
			assert(false);
		}
		else if (std::dynamic_pointer_cast<EndFrameqc>(frmj)) {
			inst = std::make_shared<DirectionCosineConstraintIctJqc>(frmi, frmj, axisi, axisj);
		}
		else if (std::dynamic_pointer_cast<EndFramect>(frmj)) {
			assert(false);
		}
		else if (std::dynamic_pointer_cast<EndFramec>(frmj)) {
			assert(false);
		}
	}
	else if (std::dynamic_pointer_cast<EndFramec>(frmi)) {
		if (std::dynamic_pointer_cast<EndFrameqct>(frmj)) {
			assert(false);
		}
		else if (std::dynamic_pointer_cast<EndFrameqc>(frmj)) {
			inst = std::make_shared<DirectionCosineConstraintIcJqc>(frmi, frmj, axisi, axisj);
		}
		else if (std::dynamic_pointer_cast<EndFramect>(frmj)) {
			assert(false);
		}
		else if (std::dynamic_pointer_cast<EndFramec>(frmj)) {
			assert(false);
		}
	}
	assert(inst);
	inst->initialize();
	return inst;
}

void DirectionCosineConstraintIJ::initialize()
{
	ConstraintIJ::initialize();
	initaAijIeJe();
}

void DirectionCosineConstraintIJ::initializeLocally()
{
	aAijIeJe->initializeLocally();
}

void DirectionCosineConstraintIJ::initializeGlobally()
{
	aAijIeJe->initializeGlobally();
}

void DirectionCosineConstraintIJ::initaAijIeJe()
{
	aAijIeJe = DirectionCosineIecJec::With(efrmI, efrmJ, axisI, axisJ);
}

void DirectionCosineConstraintIJ::postInput()
{
	aAijIeJe->postInput();
	ConstraintIJ::postInput();
}

void DirectionCosineConstraintIJ::calcPostDynCorrectorIteration()
{
	aG = aAijIeJe->aAijIeJe - aConstant;
}

void DirectionCosineConstraintIJ::prePosIC()
{
	aAijIeJe->prePosIC();
	ConstraintIJ::prePosIC();
}

void DirectionCosineConstraintIJ::postPosICIteration()
{
	aAijIeJe->postPosICIteration();
	ConstraintIJ::postPosICIteration();
}

ConstraintType DirectionCosineConstraintIJ::type()
{
	return perpendicular;
}

void MbD::DirectionCosineConstraintIJ::postDynPredictor()
{
	aAijIeJe->postDynPredictor();
	ConstraintIJ::postDynPredictor();
}

void MbD::DirectionCosineConstraintIJ::postDynCorrectorIteration()
{
	aAijIeJe->postDynCorrectorIteration();
	ConstraintIJ::postDynCorrectorIteration();
}

void MbD::DirectionCosineConstraintIJ::preDynOutput()
{
	aAijIeJe->preDynOutput();
	ConstraintIJ::preDynOutput();
}

void MbD::DirectionCosineConstraintIJ::postDynOutput()
{
	aAijIeJe->postDynOutput();
	ConstraintIJ::postDynOutput();
}

void DirectionCosineConstraintIJ::preVelIC()
{
	aAijIeJe->preVelIC();
	ConstraintIJ::preVelIC();
}

void MbD::DirectionCosineConstraintIJ::simUpdateAll()
{
	aAijIeJe->simUpdateAll();
	ConstraintIJ::simUpdateAll();
}

void DirectionCosineConstraintIJ::preAccIC()
{
	aAijIeJe->preAccIC();
	ConstraintIJ::preAccIC();
}
