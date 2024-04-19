/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "TranslationConstraintIqctJqc.h"
#include "DispCompIeqctJeqcKeqct.h"
#include "EndFrameqct.h"

using namespace MbD;

std::shared_ptr<TranslationConstraintIJ> MbD::TranslationConstraintIJ::With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi)
{
	std::shared_ptr<TranslationConstraintIJ> inst;
	if (std::dynamic_pointer_cast<EndFrameqct>(frmi)) {
		inst = std::make_shared<TranslationConstraintIqctJqc>(frmi, frmj, axisi);
	}
	else {
		inst = std::make_shared<TranslationConstraintIqcJqc>(frmi, frmj, axisi);
	}
	inst->initialize();
	return inst;
}

void TranslationConstraintIJ::initialize()
{
	ConstraintIJ::initialize();
	initriIeJeIe();
}

void TranslationConstraintIJ::initializeLocally()
{
	riIeJeIe->initializeLocally();
}

void TranslationConstraintIJ::initializeGlobally()
{
	riIeJeIe->initializeGlobally();
}

void TranslationConstraintIJ::initriIeJeIe()
{
	riIeJeIe = DispCompIecJecKec::With(frmI, frmJ, frmI, axisI);
}

void TranslationConstraintIJ::postInput()
{
	riIeJeIe->postInput();
	Constraint::postInput();
}

void TranslationConstraintIJ::calcPostDynCorrectorIteration()
{
	aG = riIeJeIe->value() - aConstant;
}

void TranslationConstraintIJ::prePosIC()
{
	riIeJeIe->prePosIC();
	Constraint::prePosIC();
}

ConstraintType TranslationConstraintIJ::type()
{
	return displacement;
}

void MbD::TranslationConstraintIJ::postDynPredictor()
{
	riIeJeIe->postDynPredictor();
	Constraint::postDynPredictor();
}

void MbD::TranslationConstraintIJ::postDynCorrectorIteration()
{
	riIeJeIe->postDynCorrectorIteration();
	Constraint::postDynCorrectorIteration();
}

void MbD::TranslationConstraintIJ::preDynOutput()
{
	riIeJeIe->preDynOutput();
	Constraint::preDynOutput();
}

void MbD::TranslationConstraintIJ::postDynOutput()
{
	riIeJeIe->postDynOutput();
	Constraint::postDynOutput();
}

void TranslationConstraintIJ::postPosICIteration()
{
	riIeJeIe->postPosICIteration();
	Item::postPosICIteration();
}

void TranslationConstraintIJ::preVelIC()
{
	riIeJeIe->preVelIC();
	Item::preVelIC();
}

void MbD::TranslationConstraintIJ::simUpdateAll()
{
	riIeJeIe->simUpdateAll();
	Constraint::simUpdateAll();
}

void TranslationConstraintIJ::preAccIC()
{
	riIeJeIe->preAccIC();
	Constraint::preAccIC();
}
