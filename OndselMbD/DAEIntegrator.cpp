/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <memory>

#include "DAEIntegrator.h"
#include "Item.h"
#include "SystemSolver.h"
#include "CREATE.h"
#include "BasicQuasiIntegrator.h"
#include "SingularMatrixError.h"
#include "SimulationStoppingError.h"
#include "TooSmallStepSizeError.h"
#include "TooManyTriesError.h"
#include "SingularMatrixError.h"
#include "DiscontinuityError.h"
#include "StartingBasicDAEIntegrator.h"
#include "NormalBasicDAEIntegrator.h"

using namespace MbD;

void MbD::DAEIntegrator::initializeGlobally()
{
	IntegratorInterface::initializeGlobally();
	assignEquationNumbers();
	system->partsJointsMotionsForcesTorquesDo([](std::shared_ptr<Item> item) { item->useEquationNumbers(); });
}

void MbD::DAEIntegrator::preFirstStep()
{
	system->partsJointsMotionsForcesTorquesDo([](std::shared_ptr<Item> item) { item->preDynFirstStep(); });
}

void MbD::DAEIntegrator::checkForOutputThrough(double t)
{
	assert(false);
}

void MbD::DAEIntegrator::preRun()
{
	assert(false);
}

void MbD::DAEIntegrator::initialize()
{
	Solver::initialize();
	integrator = CREATE<StartingBasicDAEIntegrator>::With();
	integrator->setSystem(this);
}

void MbD::DAEIntegrator::preStep()
{
	system->partsJointsMotionsForcesTorquesDo([](std::shared_ptr<Item> item) { item->preDynStep(); });
}

double MbD::DAEIntegrator::suggestSmallerOrAcceptStepSize(double hnew)
{
	assert(false);	//May not be used?
	return 0.0;
	//auto hnew2 = system->suggestSmallerOrAcceptStepSize(hnew);
	//if (hnew2 > hmax) {
	//	hnew2 = hmax;
	//	Solver::logString("MbD: Step size is at user specified maximum.");
	//}
	//if (hnew2 < hmin) {
	//	std::stringstream ss;
	//	ss << "MbD: Step size " << hnew2 << " < " << hmin << "  user specified minimum.";
	//	auto str = ss.str();
	//	system->logString(str);
	//	throw TooSmallStepSizeError("");
	//}
	//return hnew2;
}

void MbD::DAEIntegrator::postRun()
{
	assert(false);
}

void MbD::DAEIntegrator::runInitialConditionTypeSolution()
{
	assert(false);
}

void MbD::DAEIntegrator::iStep(size_t i)
{
	assert(false);
}

void MbD::DAEIntegrator::selectOrder()
{
	assert(false);
}

void MbD::DAEIntegrator::checkForDiscontinuity()
{
	assert(false);
}

double MbD::DAEIntegrator::suggestSmallerOrAcceptFirstStepSize(double hnew)
{
	assert(false);
	return 0.0;
}

FColDsptr MbD::DAEIntegrator::integrationRelativeTolerance()
{
	//"Answer column of tolerances used by the integration error estimator."
	//"Algebraic variables are not included in the error estimator."

	auto relTol = system->integrationRelativeTolerance();
	auto col = std::make_shared<FullColumn<double>>(neqn);
	for (size_t i = 0; i < neqn - ncon; i++)
	{
		col->atiput(i, relTol);
	}
	for (size_t i = neqn - ncon; i < neqn; i++)
	{
		col->atiput(i, std::numeric_limits<double>::min());
	}
	return col;
}

FColDsptr MbD::DAEIntegrator::integrationAbsoluteTolerance()
{
	auto absTol = system->integrationAbsoluteTolerance();
	auto col = std::make_shared<FullColumn<double>>(neqn);
	for (size_t i = 0; i < neqn - ncon; i++)
	{
		col->atiput(i, absTol);
	}
	for (size_t i = neqn - ncon; i < neqn; i++)
	{
		col->atiput(i, std::numeric_limits<double>::min());
	}
	return col;
}

FColDsptr MbD::DAEIntegrator::correctorRelativeTolerance()
{
	auto corRelTol = system->integrationRelativeTolerance();
	auto col = std::make_shared<FullColumn<double>>(neqn);
	for (size_t i = 0; i < neqn; i++)
	{
		col->atiput(i, corRelTol);
	}
	return col;
}

FColDsptr MbD::DAEIntegrator::correctorAbsoluteTolerance()
{
	auto corAbsTol = system->integrationRelativeTolerance();
	auto col = std::make_shared<FullColumn<double>>(neqn);
	for (size_t i = 0; i < neqn; i++)
	{
		col->atiput(i, corAbsTol);
	}
	return col;
}

void MbD::DAEIntegrator::y(FColDsptr col)
{
	assert(false);
	//system->y(col);
}

void MbD::DAEIntegrator::ydot(FColDsptr col)
{
	assert(false);
	//system->ydot(col);
}

void MbD::DAEIntegrator::preDAEOutput()
{
	assert(false);
}

void MbD::DAEIntegrator::postDAEOutput()
{
	assert(false);
}

void MbD::DAEIntegrator::useTrialStepStats(std::shared_ptr<SolverStatistics> stats)
{
	assert(false);
	//system->useDAETrialStepStats(stats);
}

void MbD::DAEIntegrator::useDAEStepStats(std::shared_ptr<SolverStatistics> stats)
{
	system->useDAEStepStats(stats);
}

void MbD::DAEIntegrator::run()
{
	this->preRun();
	this->initializeLocally();
	this->initializeGlobally();
	if (hout > (4 * std::numeric_limits<double>::epsilon()) && (direction * tout < (direction * (tend + (0.1 * direction * hout))))) {
		integrator->run();
		auto startingintegrator = std::dynamic_pointer_cast<StartingBasicDAEIntegrator>(integrator);
		auto normalIntegrator = std::make_shared<NormalBasicDAEIntegrator>(startingintegrator);
		integrator = normalIntegrator;
		integrator->run();
	}
	this->finalize();
	this->reportStats();
	this->postRun();
}
