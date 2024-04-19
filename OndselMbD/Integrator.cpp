/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "Integrator.h"
#include <cassert>

using namespace MbD;

std::shared_ptr<Integrator> MbD::Integrator::With()
{
	auto inst = std::make_shared<Integrator>();
	inst->initialize();
	return inst;
}

void Integrator::setSystem(Solver*)
{
	assert(false);
}

void MbD::Integrator::firstStep()
{
	assert(false);
}

void MbD::Integrator::preFirstStep()
{
	assert(false);
}

void MbD::Integrator::postFirstStep()
{
	assert(false);
}

void MbD::Integrator::subsequentSteps()
{
	assert(false);
}

void MbD::Integrator::nextStep()
{
	assert(false);
}

void MbD::Integrator::preStep()
{
	assert(false);
}

void MbD::Integrator::postStep()
{
	assert(false);
}

void MbD::Integrator::runInitialConditionTypeSolution()
{
	assert(false);
}

void MbD::Integrator::iStep(size_t i)
{
	assert(false);
}

void MbD::Integrator::selectOrder()
{
	assert(false);
}

void MbD::Integrator::selectStepSize()
{
	assert(false);
}

size_t MbD::Integrator::iterMax()
{
	assert(false);
	return 0;
}
