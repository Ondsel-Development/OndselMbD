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
