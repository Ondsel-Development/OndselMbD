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
	class RedundantConstraint : public Constraint
	{
		//
	public:
		static std::shared_ptr<RedundantConstraint> With();

		void removeRedundantConstraints(std::shared_ptr<std::vector<size_t>> redundantEqnNos) override;
		bool isRedundant() override;
		std::string classname() override;
		ConstraintType type() override;
		void fillqsuddotlam(FColDsptr col) override;
		void fillqsulam(FColDsptr col) override;
		void fillpqsumu(FColDsptr col) override;
		void fillpqsumudot(FColDsptr col) override;
		void postInput() override;
		void prePosIC() override;
		void fillEssenConstraints(std::shared_ptr<Constraint> sptr, std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> essenConstraints) override;
		void fillDispConstraints(std::shared_ptr<Constraint> sptr, std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> dispConstraints) override;
		void fillPerpenConstraints(std::shared_ptr<Constraint> sptr, std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> perpenConstraints) override;
		void fillConstraints(std::shared_ptr<Constraint> sptr, std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> redunConstraints) override;
		void fillRedundantConstraints(std::shared_ptr<Constraint> sptr, std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> allConstraints) override;
		void setqsulam(FColDsptr col) override;
		void setqsudotlam(FColDsptr col) override;
		void fillPosICError(FColDsptr col) override;
		void fillPosKineError(FColDsptr col) override;
		void fillPosKineJacob(SpMatDsptr mat) override;
		void preVelIC() override;
		void preAccIC() override;
		void fillAccICIterError(FColDsptr col) override;
		void setqsuddotlam(FColDsptr col) override;
		void discontinuityAtaddTypeTo(double t, std::shared_ptr<std::vector<DiscontinuityType>> disconTypes) override;
		void setpqsumu(FColDsptr col) override;
		void setpqsumudot(FColDsptr col) override;
		void setpqsumuddot(FColDsptr col) override;
		void postDynPredictor() override;
		void postPosICIteration() override;
		void fillDynError(FColDsptr col) override;
		void fillpFpy(SpMatDsptr mat) override;
		void fillpFpydot(SpMatDsptr mat) override;
		void postDynCorrectorIteration() override;
		void preDynOutput() override;
		void postDynOutput() override;
		void addToJointTorqueI(FColDsptr col) override;

		std::shared_ptr<Constraint> constraint;
	};
}

