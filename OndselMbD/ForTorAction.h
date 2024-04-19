/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "ForceTorqueItem.h"
#include "MarkerFrame.h"

namespace MbD {
	class ForTorBasic;
	class ForTorFunction;

	class ForTorAction : public ForceTorqueItem
	{
		//
	public:
		ForTorAction() {}
		ForTorAction(size_t count);
		static std::shared_ptr<ForTorAction> With(size_t count);
		void initialize() override;

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

		std::shared_ptr<ForTorBasic> forTorBasicI;
		std::shared_ptr<ForTorFunction> forTorFunction;
	};
}
