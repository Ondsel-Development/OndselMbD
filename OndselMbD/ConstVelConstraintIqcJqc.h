/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "ConstVelConstraintIqcJc.h"

namespace MbD {
	class ConstVelConstraintIqcJqc : public ConstVelConstraintIqcJc
	{
		//pGpEJ ppGpEIpEJ ppGpEJpEJ iqEJ 
	public:
		ConstVelConstraintIqcJqc(EndFrmsptr frmi, EndFrmsptr frmj) : ConstVelConstraintIqcJc(frmi, frmj) {}
		static std::shared_ptr<ConstVelConstraintIqcJqc> With(EndFrmsptr frmi, EndFrmsptr frmj);
		void initialize() override;

		void calcPostDynCorrectorIteration() override;
		void fillAccICIterError(FColDsptr col) override;
		void fillPosICError(FColDsptr col) override;
		void fillPosICJacob(SpMatDsptr mat) override;
		void fillPosKineJacob(SpMatDsptr mat) override;
		void fillVelICJacob(SpMatDsptr mat) override;
		void initA01IeJe() override;
		void initA10IeJe() override;
		void useEquationNumbers() override;
		void fillpFpy(SpMatDsptr mat) override;
		void fillpFpydot(SpMatDsptr mat) override;

		FRowDsptr pGpEJ;
		FMatDsptr ppGpEIpEJ;
		FMatDsptr ppGpEJpEJ;
		size_t iqEJ = SIZE_MAX;
	};
}

