/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "ExternalSystem.h"
#include "CADSystem.h"
#include "ASMTAssembly.h"
#include "System.h"
#include "SolverStatistics.h"

using namespace MbD;

std::shared_ptr<ExternalSystem> MbD::ExternalSystem::With()
{
	auto inst = std::make_shared<ExternalSystem>();
	inst->initialize();
	return inst;
}

void MbD::ExternalSystem::initialize()
{
	//Do nothing.
}

void MbD::ExternalSystem::preMbDrun(std::shared_ptr<System> mbdSys)
{
	if (cadSystem) {
		cadSystem->preMbDrun(mbdSys);
	}
	else if (asmtAssembly) {
		asmtAssembly->preMbDrun(mbdSys);
	}
	else {
		assert(false);
	}
}

void MbD::ExternalSystem::updateFromMbD()
{
	if (cadSystem) {
		cadSystem->updateFromMbD();
	}
	else if (asmtAssembly) {
		asmtAssembly->updateFromMbD();
	}
	else {
		assert(false);
	}
}

void MbD::ExternalSystem::outputFor(AnalysisType type)
{
	if (cadSystem) {
		cadSystem->updateFromMbD();
	}
	else if (asmtAssembly) {
		asmtAssembly->updateFromMbD();
		asmtAssembly->compareResults(type);
		asmtAssembly->outputResults(type);
	}
	else {
		assert(false);
	}
}

void MbD::ExternalSystem::logString(std::string& str)
{
	std::cout << str << std::endl;
}

void MbD::ExternalSystem::logString(double)
{
	assert(false);
}

void MbD::ExternalSystem::runOndselPiston()
{
	assert(false);
}

void MbD::ExternalSystem::runPiston()
{
	assert(false);
}

void MbD::ExternalSystem::postMbDrun()
{
	//Do nothing
}

void MbD::ExternalSystem::useDynTrialStepStats(std::shared_ptr<SolverStatistics> stats)
{
	//83 , t=1.97948 , o=5 , h=0.0263736 , it=2 , e=0.0522701
	std::stringstream ss;
	ss << stats->istep << " t=" << stats->t << " o=" << stats->order << " h=" << stats->h << " it=" << stats->corIterNo + 1 << " e=" << stats->truncError;
	auto str = ss.str();
	logString(str);

}

void MbD::ExternalSystem::useKineTrialStepStats(std::shared_ptr<SolverStatistics> stats)
{
	std::stringstream ss;
	ss << stats->istep << " t=" << stats->t << " h=" << stats->h;
	auto str = ss.str();
	logString(str);
}
