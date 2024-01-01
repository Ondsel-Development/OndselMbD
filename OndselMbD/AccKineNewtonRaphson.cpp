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
