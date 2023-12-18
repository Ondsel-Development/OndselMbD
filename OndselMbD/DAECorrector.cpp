/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "DAECorrector.h"
#include "BasicDAEIntegrator.h"
#include "CREATE.h"
#include "GESpMatParPvMarkoFast.h"
#include "GESpMatParPvPrecise.h"
#include "SystemSolver.h"

using namespace MbD;

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
