/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "ForTorActReactComp.h"

namespace MbD {
	class ForTorActReactKComp : public ForTorActReactComp
	{
		//
	public:
		static std::shared_ptr<ForTorActReactKComp> With();
		
		void postDynPredictor() override;

	};
}
