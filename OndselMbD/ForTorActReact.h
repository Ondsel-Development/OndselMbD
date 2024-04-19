/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "ForceTorqueItem.h"
#include "ForTorAction.h"
#include "ForTorBasic.h"

namespace MbD {
	class ForTorActReact : public ForceTorqueItem
	{
		//
	public:
		static std::shared_ptr<ForTorActReact> With();
		
		FColDsptr getFTIeO() const override;
		std::shared_ptr<ForTorFunction> getforTorFunction();
		void setforTorFunction(std::shared_ptr<ForTorFunction> forTorFunction);
		void initializeGlobally() override;
		void initializeLocally() override;
		void postAccICIteration() override;
		void postCollisionCorrectorIteration() override;
		void postCollisionPredictor() override;
		void postDynCorrectorIteration() override;
		void postDynOutput() override;
		void postDynPredictor() override;
		void postInput() override;
		void postStaticIteration() override;
		void preAccIC() override;
		void preDynOutput() override;
		void preStatic() override;
		void simUpdateAll() override;
		void useEquationNumbers() override;

		std::shared_ptr<ForTorAction> forTorAction;
		std::shared_ptr<ForTorBasic> forTorBasicJ;
	};
}
