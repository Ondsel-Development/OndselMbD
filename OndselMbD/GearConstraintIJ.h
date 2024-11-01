/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "ConstraintIJ.h"
#include "OrbitAngleZIecJec.h"

namespace MbD {
	class GearConstraintIJ : public ConstraintIJ
	{
		//orbitIeJe orbitJeIe radiusI radiusJ 
	public:
		GearConstraintIJ(EndFrmsptr frmi, EndFrmsptr frmj) : ConstraintIJ(frmi, frmj) {}
		static std::shared_ptr<GearConstraintIJ> With(EndFrmsptr frmi, EndFrmsptr frmj);
		void initialize() override;

		void calcPostDynCorrectorIteration() override;
		void initializeGlobally() override;
		void initializeLocally() override;
		virtual void initorbitsIJ();
		void postInput() override;
		void postPosICIteration() override;
		void preAccIC() override;
		void prePosIC() override;
		void preVelIC() override;
		double ratio();
		void simUpdateAll() override;
		void postDynPredictor() override;
		void postDynCorrectorIteration() override;
		void preDynOutput() override;
		void postDynOutput() override;

		std::shared_ptr<OrbitAngleZIecJec> orbitIeJe, orbitJeIe;
		double radiusI, radiusJ;
	};
}

