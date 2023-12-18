/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include <string>
#include <memory>

#include "SolverStatistics.h"

namespace MbD {
	class Solver
	{
		//statistics
	public:
		void noop();
		virtual ~Solver() {}
		virtual void initialize();
		virtual void initializeLocally();
		virtual void initializeGlobally();
		virtual void assignEquationNumbers();
		virtual void run();
		virtual void preRun();
		virtual void finalize();
		virtual void reportStats();
		virtual void postRun();
		virtual void logString(std::string& str);
		void logString(const char* chars);
		virtual void setSystem(Solver* sys) = 0;
		virtual void handleSingularMatrix();

		std::shared_ptr<SolverStatistics> statistics = std::make_shared<SolverStatistics>();
	};
}

