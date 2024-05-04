/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "RackPinConstraintIqcJc.h"

namespace MbD {
	class RackPinConstraintIqcJqc : public RackPinConstraintIqcJc
	{
		//pGpXJ pGpEJ ppGpEIpXJ ppGpEIpEJ ppGpEJpEJ iqXJ iqEJ 
	public:
		RackPinConstraintIqcJqc(EndFrmsptr frmi, EndFrmsptr frmj) : RackPinConstraintIqcJc(frmi, frmj) {}
		static std::shared_ptr<RackPinConstraintIqcJqc> With(EndFrmsptr frmi, EndFrmsptr frmj);
		void initialize() override;

		void initxIeJeIe() override;
		void initthezIeJe() override;
		void calc_pGpEJ();
		void calc_pGpXJ();
		void calc_ppGpEIpEJ();
		void calc_ppGpEIpXJ();
		void calc_ppGpEJpEJ();
		void calcPostDynCorrectorIteration() override;
		void fillAccICIterError(FColDsptr col) override;
		void fillPosICError(FColDsptr col) override;
		void fillPosICJacob(SpMatDsptr mat) override;
		void fillPosKineJacob(SpMatDsptr mat) override;
		void fillVelICJacob(SpMatDsptr mat) override;
		void useEquationNumbers() override;
		void fillpFpy(SpMatDsptr mat) override;
		void fillpFpydot(SpMatDsptr mat) override;

		FRowDsptr pGpXJ, pGpEJ;
		FMatDsptr ppGpEIpXJ, ppGpEIpEJ, ppGpEJpEJ;
		size_t iqXJ = SIZE_MAX, iqEJ = SIZE_MAX;
	};
}

