/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "AccICNewtonRaphson.h"
#include "SystemSolver.h"

using namespace MbD;

std::shared_ptr<AccICNewtonRaphson> MbD::AccICNewtonRaphson::With()
{
	auto inst = std::make_shared<AccICNewtonRaphson>();
	inst->initialize();
	return inst;
}

void MbD::AccICNewtonRaphson::run()
{
	//Keep for debugging
	preRun();
	initializeLocally();
	initializeGlobally();
	iterate();
	postRun();
}

void MbD::AccICNewtonRaphson::iterate()
{
	//Keep for debugging
	iterNo = SIZE_MAX;
	fillY();
	calcyNorm();
	yNorms->push_back(yNorm);

	while (true) {
		incrementIterNo();
		fillPyPx();
		//outputSpreadsheet();
		solveEquations();
		calcDXNormImproveRootCalcYNorm();
		if (isConverged()) {
			//std::cout << "iterNo = " << iterNo << std::endl;
			break;
		}
	}
}

bool AccICNewtonRaphson::isConverged()
{
	return isConvergedToNumericalLimit();
}

void AccICNewtonRaphson::preRun()
{
	std::string str("MbD: Solving for acceleration initial conditions.");
	system->logString(str);
	AccNewtonRaphson::preRun();
}
