/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include <assert.h>

#include "Solver.h"
#include <string>

using namespace MbD;

std::shared_ptr<Solver> MbD::Solver::With()
{
	auto inst = std::make_shared<Solver>();
	inst->initialize();
	return inst;
}

void Solver::initialize()
{
	//Do nothing.
}

void MbD::Solver::noop()
{
	//No Operations
}

void Solver::initializeLocally()
{
	//Do nothing.
}

void Solver::initializeGlobally()
{
	//Do nothing.
}

void Solver::assignEquationNumbers()
{
	assert(false);
}

void Solver::run()
{
	assert(false);
}

void Solver::preRun()
{
	assert(false);
}

void Solver::finalize()
{
	//Do nothing.
}

void Solver::reportStats()
{
	assert(false);
}

void Solver::postRun()
{
	assert(false);
}

void Solver::logString(std::string&)
{
	assert(false);
}

void Solver::logString(const char* chars)
{
	std::string str = chars;
	this->logString(str);
}

void MbD::Solver::setSystem(Solver*)
{
	//Subclasses must implement.
	assert(false);
}

void MbD::Solver::handleSingularMatrix()
{
	assert(false);
}
