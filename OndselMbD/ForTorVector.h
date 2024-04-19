/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "ForceTorqueItem.h"
#include "ForTorActReactComp.h"

namespace MbD {
	class ForTorVector : public ForceTorqueItem
	{
		//components
	public:
		ForTorVector() {}
		static std::shared_ptr<ForTorVector> With();
		
		void useEquationNumbers() override;

		std::shared_ptr<FullColumn<std::shared_ptr<ForTorActReactComp>>> components;
	};
}
