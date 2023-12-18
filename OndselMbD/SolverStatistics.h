/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once
#include <limits>

namespace MbD {
	class SolverStatistics
	{
	public:
		int iterNo = -1;
		int corIterNo = -1;
		double h = std::numeric_limits<double>::min();
		int istep = -1;
		int order = -1;
		double t = std::numeric_limits<double>::min();
		double truncError = std::numeric_limits<double>::min();
	};
}

