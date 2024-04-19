/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "ASMTItemIJ.h"

namespace MbD {
	class ForceFunctionParser;

	class ASMTForceTorque : public ASMTItemIJ
	{
		//
	public:
		static std::shared_ptr<ASMTForceTorque> With();

		void updateFromMbD() override;
		void compareResults(AnalysisType type) override;
		void outputResults(AnalysisType type) override;
		void readForceTorqueSeries(std::vector<std::string>& lines);
		void createMbD(std::shared_ptr<System> mbdSys, std::shared_ptr<Units> mbdUnits) override;
		std::shared_ptr<ForceFunctionParser> functionParser();

	};
}

