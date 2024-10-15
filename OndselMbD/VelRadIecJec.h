/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "KinematicDotIeJe.h"

namespace MbD {
	class VelRadIecJec : public KinematicDotIeJe
	{
		//rIeJe rIeJeO uIeJeO vIeJe vIeJeO 
	public:
		VelRadIecJec() {}
		VelRadIecJec(EndFrmsptr frmi, EndFrmsptr frmj) : KinematicDotIeJe(frmi, frmj) {}
		static std::shared_ptr<VelRadIecJec> With(EndFrmsptr frmi, EndFrmsptr frmj);

		void calcPostDynCorrectorIteration() override;
		double value() override;

		double rIeJe{0.0}, vIeJe{0.0};
		FColDsptr rIeJeO, uIeJeO, vIeJeO;

	};
}

