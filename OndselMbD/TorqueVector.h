/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "ForTorVector.h"

namespace MbD {
	class TorqueVector : public ForTorVector
	{
		//
	public:
		TorqueVector(EndFrmsptr frmi, EndFrmsptr frmj);
		TorqueVector(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk);
		static std::shared_ptr<TorqueVector> With(EndFrmsptr frmi, EndFrmsptr frmj);
		static std::shared_ptr<TorqueVector> With(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk);

	};
}
