/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "MatrixLDU.h"

using namespace MbD;

std::shared_ptr<MatrixLDU> MbD::MatrixLDU::With()
{
	auto inst = std::make_shared<MatrixLDU>();
	inst->initialize();
	return inst;
}

FColDsptr MatrixLDU::forAndBackSubsaveOriginal(FColDsptr fullCol, bool saveOriginal)
{
	if (saveOriginal) {
		rightHandSideB = fullCol->copy();
	}
	else {
		rightHandSideB = fullCol;
	}
	this->applyRowOrderOnRightHandSideB();
	this->forwardSubstituteIntoL();
	this->backSubstituteIntoDU();
	return answerX;
}
