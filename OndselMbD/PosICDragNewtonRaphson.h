/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "AnyPosICNewtonRaphson.h"

namespace MbD {
	class Part;

	class PosICDragNewtonRaphson : public AnyPosICNewtonRaphson
	{
		//Kinematics with under constrained system
	public:
		static std::shared_ptr<PosICDragNewtonRaphson> With();
		void initializeGlobally() override;
		void assignEquationNumbers() override;
		bool isConverged() override;
		void setdragParts(std::shared_ptr<std::vector<std::shared_ptr<Part>>> dragParts);

		std::shared_ptr<std::vector<std::shared_ptr<Part>>> dragParts;
	};
}

