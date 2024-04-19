/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "ForTorBasic.h"

namespace MbD {
	class TorqueBasicComp : public ForTorBasic
	{
		//
	public:
		static std::shared_ptr<TorqueBasicComp> With();

		FColDsptr twoBaxisT;
	};
}
