/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "DistxyIecJec.h"

using namespace MbD;

MbD::DistxyIecJec::DistxyIecJec(EndFrmsptr frmi, EndFrmsptr frmj) : KinematicIJ(frmi, frmj)
{
	assert(false);
}

std::shared_ptr<DistxyIecJec> MbD::DistxyIecJec::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
	auto inst = std::make_shared<DistxyIecJec>(frmi, frmj);
	inst->initialize();
	return inst;
}

void MbD::DistxyIecJec::initialize()
{
	KinematicIJ::initialize();
	init_xyIeJeIe();
}

void MbD::DistxyIecJec::calcPostDynCorrectorIteration()
{
	auto x = xIeJeIe->value();
	auto y = yIeJeIe->value();
	distxy = std::sqrt(x * x + (y * y));
}

void MbD::DistxyIecJec::initializeGlobally()
{
	xIeJeIe->initializeGlobally();
	yIeJeIe->initializeGlobally();
}

void MbD::DistxyIecJec::initializeLocally()
{
	xIeJeIe->initializeLocally();
	yIeJeIe->initializeLocally();
}

void MbD::DistxyIecJec::init_xyIeJeIe()
{
	assert(false);
}

void MbD::DistxyIecJec::postInput()
{
	xIeJeIe->postInput();
	yIeJeIe->postInput();
	KinematicIJ::postInput();
}

void MbD::DistxyIecJec::postPosICIteration()
{
	xIeJeIe->postPosICIteration();
	yIeJeIe->postPosICIteration();
	KinematicIJ::postPosICIteration();
}

void MbD::DistxyIecJec::preAccIC()
{
	xIeJeIe->preAccIC();
	yIeJeIe->preAccIC();
	KinematicIJ::preAccIC();
}

void MbD::DistxyIecJec::prePosIC()
{
	xIeJeIe->prePosIC();
	yIeJeIe->prePosIC();
	KinematicIJ::prePosIC();
}

void MbD::DistxyIecJec::preVelIC()
{
	xIeJeIe->preVelIC();
	yIeJeIe->preVelIC();
	KinematicIJ::preVelIC();
}

void MbD::DistxyIecJec::simUpdateAll()
{
	xIeJeIe->simUpdateAll();
	yIeJeIe->simUpdateAll();
	KinematicIJ::simUpdateAll();
}

double MbD::DistxyIecJec::value()
{
	return distxy;
}
