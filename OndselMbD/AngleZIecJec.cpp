/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "corecrt_math_defines.h"

#include "AngleZIecJec.h"
#include "Numeric.h"

using namespace MbD;

void MbD::AngleZIecJec::initialize()
{
	KinematicIJ::initialize();
	init_aAijIeJe();
}

void MbD::AngleZIecJec::calcPostDynCorrectorIteration()
{
	auto cthez = aA00IeJe->value();
	auto sthez = aA10IeJe->value();
	auto sumOfSquares = cthez * cthez + (sthez * sthez);
	auto diffOfSquares = sthez * sthez - (cthez * cthez);
	auto sumOfSquaresSquared = sumOfSquares * sumOfSquares;
	auto thez0to2pi = Numeric::arcTan0to2piYoverX(sthez, cthez);
	thez = std::round((thez - thez0to2pi) / (2.0 * OS_M_PI)) * (2.0 * OS_M_PI) + thez0to2pi;
	cosOverSSq = cthez / sumOfSquares;
	sinOverSSq = sthez / sumOfSquares;
	twoCosSinOverSSqSq = 2.0 * cthez * sthez / sumOfSquaresSquared;
	dSqOverSSqSq = diffOfSquares / sumOfSquaresSquared;
}

void MbD::AngleZIecJec::init_aAijIeJe()
{
	//Subclasses must implement.
	assert(false);
}

void MbD::AngleZIecJec::initializeGlobally()
{
	aA00IeJe->initializeGlobally();
	aA10IeJe->initializeGlobally();
}

void MbD::AngleZIecJec::initializeLocally()
{
	aA00IeJe->initializeLocally();
	aA10IeJe->initializeLocally();
}

void MbD::AngleZIecJec::postInput()
{
	aA00IeJe->postInput();
	aA10IeJe->postInput();
	if (thez == std::numeric_limits<double>::min()) {
		auto cthez = aA00IeJe->value();
		auto sthez = aA10IeJe->value();
		if (cthez > 0.0) {
			thez = std::atan2(sthez, cthez);
		}
		else {
			thez = Numeric::arcTan0to2piYoverX(sthez, cthez);
		}
	}
	KinematicIJ::postInput();
}

void MbD::AngleZIecJec::postPosICIteration()
{
	aA00IeJe->postPosICIteration();
	aA10IeJe->postPosICIteration();
	KinematicIJ::postPosICIteration();
}

void MbD::AngleZIecJec::preAccIC()
{
	aA00IeJe->preAccIC();
	aA10IeJe->preAccIC();
	KinematicIJ::preAccIC();
}

void MbD::AngleZIecJec::prePosIC()
{
	aA00IeJe->prePosIC();
	aA10IeJe->prePosIC();
	assert(thez != std::numeric_limits<double>::min());
	KinematicIJ::prePosIC();
}

void MbD::AngleZIecJec::preVelIC()
{
	aA00IeJe->preVelIC();
	aA10IeJe->preVelIC();
	KinematicIJ::preVelIC();
}

void MbD::AngleZIecJec::simUpdateAll()
{
	aA00IeJe->simUpdateAll();
	aA10IeJe->simUpdateAll();
	KinematicIJ::simUpdateAll();
}

double MbD::AngleZIecJec::value()
{
	return thez;
}

void MbD::AngleZIecJec::postDynPredictor()
{
	aA00IeJe->postDynPredictor();
	aA10IeJe->postDynPredictor();
	KinematicIJ::postDynPredictor();
}

void MbD::AngleZIecJec::postDynCorrectorIteration()
{
	aA00IeJe->postDynCorrectorIteration();
	aA10IeJe->postDynCorrectorIteration();
	KinematicIJ::postDynCorrectorIteration();
}

void MbD::AngleZIecJec::preDynOutput()
{
	aA00IeJe->preDynOutput();
	aA10IeJe->preDynOutput();
	KinematicIJ::preDynOutput();
}

void MbD::AngleZIecJec::postDynOutput()
{
	aA00IeJe->postDynOutput();
	aA10IeJe->postDynOutput();
	KinematicIJ::postDynOutput();
}
