/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "AccICKineNewtonRaphson.h"
#include "SystemSolver.h"

using namespace MbD;

std::shared_ptr<AccICKineNewtonRaphson> MbD::AccICKineNewtonRaphson::With()
{
	auto inst = std::make_shared<AccICKineNewtonRaphson>();
	inst->initialize();
	return inst;
}

void MbD::AccICKineNewtonRaphson::run()
{
	//Keep for debugging
	preRun();
	initializeLocally();
	initializeGlobally();
	iterate();
	postRun();
}

void MbD::AccICKineNewtonRaphson::iterate()
{
	//Keep for debugging
	iterNo = SIZE_MAX;
	this->fillY();
	calcyNorm();
	yNorms->push_back(yNorm);

	while (true) {
		incrementIterNo();
		fillPyPx();
		//std::cout << *pypx << std::endl;
		outputSpreadsheet();
		solveEquations();
		calcDXNormImproveRootCalcYNorm();
		if (this->isConverged()) {
			//std::cout << "iterNo = " << iterNo << std::endl;
			break;
		}
	}
}

void AccICKineNewtonRaphson::initializeGlobally()
{
	AccNewtonRaphson::initializeGlobally();
	iterMax = system->iterMaxAccKine;
	dxTol = system->errorTolAccKine;
}

void AccICKineNewtonRaphson::preRun()
{
	std::string str("MbD: Solving for quasi kinematic acceleration.");
	system->logString(str);
	AccNewtonRaphson::preRun();
}
