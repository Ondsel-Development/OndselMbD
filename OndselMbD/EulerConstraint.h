/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

//#include <memory>
//#include <vector>

#include "Constraint.h"
#include "FullRow.h"	//FRowDsptr is defined

namespace MbD {
	class EulerConstraint : public Constraint
	{
		//pGpE iqE 
	public:
		EulerConstraint() {}
		EulerConstraint(const char* str);
		static std::shared_ptr<EulerConstraint> With();
		static std::shared_ptr<EulerConstraint> With(const char* str);
		void initialize() override;

		void calcPostDynCorrectorIteration() override;
		void useEquationNumbers() override;
		void fillPosICError(FColDsptr col) override;
		void fillPosICJacob(SpMatDsptr mat) override;
		void fillPosKineJacob(SpMatDsptr mat) override;
		void fillVelICJacob(SpMatDsptr mat) override;
		void fillAccICIterError(FColDsptr col) override;
		void fillpFpy(SpMatDsptr mat) override;
		void fillpFpydot(SpMatDsptr mat) override;

		FRowDsptr pGpE;		//partial derivative of G wrt pE
		size_t iqE = SIZE_MAX;
	};
}

