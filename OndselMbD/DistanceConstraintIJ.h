/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "ConstraintIJ.h"
#include "DistIecJec.h"

namespace MbD {
	class DistanceConstraintIJ : public ConstraintIJ
	{
		//distIeJe
	public:
		DistanceConstraintIJ(EndFrmsptr frmi, EndFrmsptr frmj) : ConstraintIJ(frmi, frmj) {}
		static std::shared_ptr<DistanceConstraintIJ> With(EndFrmsptr frmi, EndFrmsptr frmj);
		void initialize() override;

		void calcPostDynCorrectorIteration() override;
		virtual void init_distIeJe();
		void initializeGlobally() override;
		void initializeLocally() override;
		void postInput() override;
		void postPosICIteration() override;
		void preAccIC() override;
		void prePosIC() override;
		void preVelIC() override;
		void simUpdateAll() override;
		ConstraintType type() override;
		void postDynPredictor() override;
		void postDynCorrectorIteration() override;
		void preDynOutput() override;
		void postDynOutput() override;

		std::shared_ptr<DistIecJec> distIeJe;

	};
}

