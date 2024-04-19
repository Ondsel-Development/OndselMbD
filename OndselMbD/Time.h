/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "IndependentVariable.h"

namespace MbD {
	class Time : public IndependentVariable
	{
	public:
		Time();
		static std::shared_ptr<Time> With();
		void initialize() override;

	};
}

