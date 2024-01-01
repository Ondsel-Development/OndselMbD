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
	iterNo = -1;
	this->fillY();
	this->calcyNorm();
	yNorms->push_back(yNorm);

	while (true) {
		this->incrementIterNo();
		this->fillPyPx();
		//std::cout << *pypx << std::endl;
		//outputSpreadsheet();
		this->solveEquations();
		this->calcDXNormImproveRootCalcYNorm();
		if (this->isConverged()) {
			//std::cout << "iterNo = " << iterNo << std::endl;
			break;
		}
	}
}

bool AccICNewtonRaphson::isConverged()
{
	return this->isConvergedToNumericalLimit();
}

void AccICNewtonRaphson::preRun()
{
	std::string str("MbD: Solving for acceleration initial conditions.");
	system->logString(str);
	AccNewtonRaphson::preRun();
}
