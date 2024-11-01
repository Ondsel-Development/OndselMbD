/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "corecrt_math_defines.h"

#include "OrbitAngleZIecJec.h"
#include "Numeric.h"

using namespace MbD;

std::shared_ptr<OrbitAngleZIecJec> MbD::OrbitAngleZIecJec::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
	auto inst = std::make_shared<OrbitAngleZIecJec>(frmi, frmj);
	inst->initialize();
	return inst;
}

void MbD::OrbitAngleZIecJec::initialize()
{
	KinematicIJ::initialize();
	init_xyIeJeIe();
}

void MbD::OrbitAngleZIecJec::calcPostDynCorrectorIteration()
{
	auto x = xIeJeIe->value();
	auto y = yIeJeIe->value();
	auto sumOfSquares = x * x + (y * y);
	auto diffOfSquares = y * y - (x * x);
	auto sumOfSquaresSquared = sumOfSquares * sumOfSquares;
	auto thez0to2pi = Numeric::arcTan0to2piYoverX(y, x);
	thez = std::round((thez - thez0to2pi) / (2.0 * OS_M_PI)) * (2.0 * OS_M_PI) + thez0to2pi;
	cosOverSSq = x / sumOfSquares;
	sinOverSSq = y / sumOfSquares;
	twoCosSinOverSSqSq = 2.0 * x * y / sumOfSquaresSquared;
	dSqOverSSqSq = diffOfSquares / sumOfSquaresSquared;
}

void MbD::OrbitAngleZIecJec::init_xyIeJeIe()
{
	//Subclasses must implement.
	assert(false);
}

void MbD::OrbitAngleZIecJec::initializeGlobally()
{
	xIeJeIe->initializeGlobally();
	yIeJeIe->initializeGlobally();
}

void MbD::OrbitAngleZIecJec::initializeLocally()
{
	xIeJeIe->initializeLocally();
	yIeJeIe->initializeLocally();
}

void MbD::OrbitAngleZIecJec::postInput()
{
	xIeJeIe->postInput();
	yIeJeIe->postInput();
	if (thez == std::numeric_limits<double>::min()) {
		auto x = xIeJeIe->value();
		auto y = yIeJeIe->value();
		if (x > 0.0) {
			thez = std::atan2(y, x);
		}
		else {
			thez = Numeric::arcTan0to2piYoverX(y, x);
		}
	}
	KinematicIJ::postInput();
}

void MbD::OrbitAngleZIecJec::postPosICIteration()
{
	xIeJeIe->postPosICIteration();
	yIeJeIe->postPosICIteration();
	KinematicIJ::postPosICIteration();
}

void MbD::OrbitAngleZIecJec::preAccIC()
{
	if (thez == std::numeric_limits<double>::min()) prePosIC();
	xIeJeIe->preAccIC();
	yIeJeIe->preAccIC();
	KinematicIJ::preAccIC();
}

void MbD::OrbitAngleZIecJec::prePosIC()
{
	xIeJeIe->prePosIC();
	yIeJeIe->prePosIC();
	assert(thez != std::numeric_limits<double>::min());
	KinematicIJ::prePosIC();
}

void MbD::OrbitAngleZIecJec::preVelIC()
{
	xIeJeIe->preVelIC();
	yIeJeIe->preVelIC();
	KinematicIJ::preVelIC();
}

void MbD::OrbitAngleZIecJec::simUpdateAll()
{
	xIeJeIe->simUpdateAll();
	yIeJeIe->simUpdateAll();
	KinematicIJ::simUpdateAll();
}

double MbD::OrbitAngleZIecJec::value()
{
	return thez;
}

void MbD::OrbitAngleZIecJec::postDynPredictor()
{
	xIeJeIe->postDynPredictor();
	yIeJeIe->postDynPredictor();
	KinematicIJ::postDynPredictor();
}

void MbD::OrbitAngleZIecJec::postDynCorrectorIteration()
{
	xIeJeIe->postDynCorrectorIteration();
	yIeJeIe->postDynCorrectorIteration();
	KinematicIJ::postDynCorrectorIteration();
}

void MbD::OrbitAngleZIecJec::preDynOutput()
{
	xIeJeIe->preDynOutput();
	yIeJeIe->preDynOutput();
	KinematicIJ::preDynOutput();
}

void MbD::OrbitAngleZIecJec::postDynOutput()
{
	xIeJeIe->postDynOutput();
	yIeJeIe->postDynOutput();
	KinematicIJ::postDynOutput();
}
