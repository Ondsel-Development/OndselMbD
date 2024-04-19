/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "AccKineNewtonRaphson.h"
#include "SystemSolver.h"

using namespace MbD;

std::shared_ptr<AccKineNewtonRaphson> MbD::AccKineNewtonRaphson::With()
{
	auto inst = std::make_shared<AccKineNewtonRaphson>();
	inst->initialize();
	return inst;
}

void MbD::AccKineNewtonRaphson::run()
{
	//Keep for debugging
	preRun();
	initializeLocally();
	initializeGlobally();
	iterate();
	postRun();
}

void MbD::AccKineNewtonRaphson::iterate()
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

void AccKineNewtonRaphson::initializeGlobally()
{
	AccNewtonRaphson::initializeGlobally();
	iterMax = system->iterMaxAccKine;
	dxTol = system->errorTolAccKine;
}

void AccKineNewtonRaphson::preRun()
{
	std::string str("MbD: Solving for kinematic acceleration.");
	system->logString(str);
	AccNewtonRaphson::preRun();
}
