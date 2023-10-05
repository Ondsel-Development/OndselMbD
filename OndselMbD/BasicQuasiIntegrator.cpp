/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselMbD.                                       *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <cassert>

#include "BasicQuasiIntegrator.h"
#include "IntegratorInterface.h"

using namespace MbD;

void BasicQuasiIntegrator::firstStep()
{
	istep = 0;
	preFirstStep();
	iTry = 1;
	orderNew = 1;
	selectFirstStepSize();
	incrementTime();
	runInitialConditionTypeSolution();
	//reportTrialStepStats();
	postFirstStep();
	//reportStepStats();
}

bool BasicQuasiIntegrator::isRedoingFirstStep()
{
	return false;
}

void BasicQuasiIntegrator::nextStep()
{
	preStep();
	iTry = 1;
	selectOrder();
	selectStepSize();
	incrementTime();
	runInitialConditionTypeSolution();
	//reportTrialStepStats();
	postStep();
	//reportStepStats();
}

void BasicQuasiIntegrator::runInitialConditionTypeSolution()
{
	system->runInitialConditionTypeSolution();
}

void BasicQuasiIntegrator::selectFirstStepSize()
{
	if (iTry == 1) {
		hnew = direction * (system->tout - t);
	}
	else {
		hnew = 0.25 * h;
	}
	hnew = system->suggestSmallerOrAcceptFirstStepSize(hnew);
}

void BasicQuasiIntegrator::selectStepSize()
{
	if (iTry == 1) {
		hnew = direction * (system->tout - t);
	}
	else {
		hnew = 0.25 * h;
	}
	hnew = system->suggestSmallerOrAcceptStepSize(hnew);
}

void MbD::BasicQuasiIntegrator::postFirstStep()
{
	assert(false);
}

void MbD::BasicQuasiIntegrator::postStep()
{
	assert(false);
}
