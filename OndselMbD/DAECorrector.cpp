/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <fstream>	

#include "DAECorrector.h"
#include "BasicDAEIntegrator.h"
#include "CREATE.h"
#include "GESpMatParPvMarkoFast.h"
#include "GESpMatParPvPrecise.h"
#include "SystemSolver.h"

using namespace MbD;

void MbD::DAECorrector::iterate()
{
	//Keep for debugging
	iterNo = SIZE_MAX;
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

void MbD::DAECorrector::fillPyPx()
{
	pypx = daeSystem->calcG();
}

void MbD::DAECorrector::fillY()
{
	y = daeSystem->fillF();
}

void MbD::DAECorrector::passRootToSystem()
{
	daeSystem->y = x;
}

void MbD::DAECorrector::calcdxNorm()
{
	dxNorm = daeSystem->corErrorNormFromwrt(dx, x);
}

void MbD::DAECorrector::basicSolveEquations()
{
	dx = matrixSolver->solvewithsaveOriginal(pypx, y->negated(), false);
}

void MbD::DAECorrector::handleSingularMatrix()
{	
	std::string str = typeid(*matrixSolver).name();
	if (str == "class MbD::GESpMatParPvMarkoFast") {
		matrixSolver = CREATE<GESpMatParPvPrecise>::With();
		this->solveEquations();
	}
	else {
		str = typeid(*matrixSolver).name();
		if (str == "class MbD::GESpMatParPvPrecise") {
			matrixSolver->throwSingularMatrixError("");
		}
		else {
			assert(false);
		}
	}
}

void MbD::DAECorrector::initializeGlobally()
{
	iterMax = daeSystem->iterMax();
	x = daeSystem->y;
	matrixSolver = CREATE<GESpMatParPvMarkoFast>::With();
}

void MbD::DAECorrector::run()
{
	preRun();
	initializeLocally();
	initializeGlobally();
	iterate();
	finalize();
	reportStats();
	postRun();
}

void MbD::DAECorrector::preRun()
{
	//auto basicDAEIntegrator = static_cast<BasicDAEIntegrator*>(system);
	daeSystem->preDAECorrector();
}

void MbD::DAECorrector::askSystemToUpdate()
{
	daeSystem->updateForDAECorrector();
}

bool MbD::DAECorrector::isConverged()
{
	return daeSystem->isConvergedForand(iterNo, dxNorms);
}

void MbD::DAECorrector::postRun()
{
	daeSystem->postDAECorrector();
}

void MbD::DAECorrector::setSystem(Solver* sys)
{
	daeSystem = static_cast<BasicDAEIntegrator*>(sys);
}

void MbD::DAECorrector::reportStats()
{
	statistics->iterNo = iterNo;
	daeSystem->useDAECorrectorStats(statistics);
}

void MbD::DAECorrector::outputSpreadsheet()
{
	std::ofstream os("../testapp/spreadsheetcpp.csv");
	os << std::setprecision(std::numeric_limits<double>::max_digits10);
	for (size_t i = 0; i < pypx->nrow(); i++)
	{
		auto rowi = pypx->at(i);
		for (size_t j = 0; j < pypx->ncol(); j++)
		{
			if (j > 0) os << '\t';
			if (rowi->find(j) == rowi->end()) {
				os << 0.0;
			}
			else {
				os << rowi->at(j);
			}
		}
		os << "\t\t" << y->at(i) << std::endl;
	}
}
