/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "ASMTItem.h"

namespace MbD {
	class ASMTSpatialItem : public ASMTItem
	{
		//
	public:
		static std::shared_ptr<ASMTSpatialItem> With();
		void initialize() override;

		void setPosition3D(FColDsptr position3D);
		void setRotationMatrix(FMatDsptr rotationMatrix);
		void readPosition3D(std::vector<std::string>& lines);
		void readRotationMatrix(std::vector<std::string>& lines);

		// Overloads to simplify syntax.
		void getPosition3D(double& a, double& b, double& c);
		void getQuarternions(double& q0, double& q1, double& q2, double& q3);
		void setPosition3D(double a, double b, double c);
		void setQuarternions(double q0, double q1, double q2, double q3);
		void setRotationMatrix(double v11, double v12, double v13,
			double v21, double v22, double v23,
			double v31, double v32, double v33);
		void storeOnLevel(std::ofstream& os, size_t level) override;
		void storeOnLevelPosition(std::ofstream& os, size_t level);
		void storeOnLevelRotationMatrix(std::ofstream& os, size_t level);
		FColDsptr getPosition3D(size_t i);
		FMatDsptr getRotationMatrix(size_t i);
		FMatDsptr aAFf();
		FMatDsptr aAOf();
		FColDsptr rFfF();
		FColDsptr rOfO();
		virtual FMatDsptr aAFf(size_t i);
		virtual FMatDsptr aAOf(size_t i);
		virtual FColDsptr rFfF(size_t i);
		virtual FColDsptr rOfO(size_t i);
		virtual FColDsptr vFfF(size_t i);
		virtual FColDsptr vOfO(size_t i);
		virtual FColDsptr omeFfF(size_t i);
		virtual FColDsptr omeOfO(size_t i);

		FColDsptr position3D = std::make_shared<FullColumn<double>>(3);
		FMatDsptr rotationMatrix = FullMatrix<double>::With(ListListD{
				{ 1, 0, 0 },
				{ 0, 1, 0 },
				{ 0, 0, 1 }
			});
		FRowDsptr xs, ys, zs, bryxs, bryys, bryzs;
		FRowDsptr inxs, inys, inzs, inbryxs, inbryys, inbryzs;

	};
}

