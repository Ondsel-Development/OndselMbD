/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "DirectionCosineConstraintIqcJc.h"

namespace MbD {
	class DirectionCosineConstraintIqcJqc : public DirectionCosineConstraintIqcJc
	{
		//pGpEJ ppGpEIpEJ ppGpEJpEJ iqEJ 
	public:
		DirectionCosineConstraintIqcJqc(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj) : DirectionCosineConstraintIqcJc(frmi, frmj, axisi, axisj) {}
		static std::shared_ptr<DirectionCosineConstraintIqcJqc> With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi, size_t axisj);

		void calcPostDynCorrectorIteration() override;
		void fillAccICIterError(FColDsptr col) override;
		void fillPosICError(FColDsptr col) override;
		void fillPosICJacob(SpMatDsptr mat) override;
		void fillPosKineJacob(SpMatDsptr mat) override;
		void fillVelICJacob(SpMatDsptr mat) override;
		void initaAijIeJe() override;
		void useEquationNumbers() override;
		void fillpFpy(SpMatDsptr mat) override;
		void fillpFpydot(SpMatDsptr mat) override;

		FRowDsptr pGpEJ;
		FMatDsptr ppGpEIpEJ;
		FMatDsptr ppGpEJpEJ;
		size_t iqEJ = SIZE_MAX;
	};
}

