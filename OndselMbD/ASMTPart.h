/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "ASMTSpatialContainer.h"

namespace MbD {
	class PosVelAccData;

	class ASMTPart : public ASMTSpatialContainer
	{
		//
	public:
		static std::shared_ptr<ASMTPart> With();

		void parseASMT(std::vector<std::string>& lines) override;
		void readFeatureOrder(std::vector<std::string>& lines);
		void readPrincipalMassMarker(std::vector<std::string>& lines);
		void readPartSeries(std::vector<std::string>& lines);
		FColDsptr vOcmO() override;
		FColDsptr omeOpO() override;
		ASMTPart* part() override;
		void createMbD() override;
		void storeOnLevel(std::ofstream& os, size_t level) override;
		void storeOnLevelMassMarker(std::ofstream& os, size_t level) const;
		void storeOnTimeSeries(std::ofstream& os) override;

		//std::shared_ptr<std::vector<std::shared_ptr<ASMTFeature>>> featureOrder;
		std::shared_ptr<std::vector<std::shared_ptr<PosVelAccData>>> partSeries;
		bool isFixed = false;

	};
}

