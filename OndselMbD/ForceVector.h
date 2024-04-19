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
	class ForceVector : public ForTorVector
	{
		//
	public:
		ForceVector(EndFrmsptr frmi, EndFrmsptr frmj);
		ForceVector(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk);
		static std::shared_ptr<ForceVector> With(EndFrmsptr frmi, EndFrmsptr frmj);
		static std::shared_ptr<ForceVector> With(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk);

	};
}
