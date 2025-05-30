/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "AccNewtonRaphson.h"

namespace MbD {
	class AccICNewtonRaphson : public AccNewtonRaphson
	{
		//IC acceleration with fully or under constrained system
	public:
		static std::shared_ptr<AccICNewtonRaphson> With();

		void run() override;
		void iterate() override;
		bool isConverged() override;
		void preRun() override;


	};
}

