/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "Constraint.h"
namespace MbD {
	class AbsConstraint : public Constraint
	{
		//axis iqXminusOnePlusAxis 
	public:
		AbsConstraint(size_t axis);
		static std::shared_ptr<AbsConstraint> With(size_t axis);

		void calcPostDynCorrectorIteration() override;
		void fillAccICIterError(FColDsptr col) override;
		void fillPosICError(FColDsptr col) override;
		void fillPosICJacob(SpMatDsptr mat) override;
		void fillPosKineJacob(SpMatDsptr mat) override;
		void fillVelICJacob(SpMatDsptr mat) override;
		void useEquationNumbers() override;
		void fillpFpy(SpMatDsptr mat) override;
		void fillpFpydot(SpMatDsptr mat) override;

		size_t axis = SIZE_MAX;
		size_t iqXminusOnePlusAxis = SIZE_MAX;
	};
}

