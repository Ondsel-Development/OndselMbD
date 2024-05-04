/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "KinematicIJ.h"

namespace MbD {
	class KinematicDotIeJe : public KinematicIJ
	{
		//
	public:
		KinematicDotIeJe() {}
		KinematicDotIeJe(EndFrmsptr frmi, EndFrmsptr frmj) : KinematicIJ(frmi, frmj) {}
		static std::shared_ptr<KinematicDotIeJe> With();
		static std::shared_ptr<KinematicDotIeJe> With(EndFrmsptr frmi, EndFrmsptr frmj);

		bool isKineIJ() override;
		bool isKinedotIJ() override;
		virtual FRowDsptr pvaluepEdotI();
		virtual FRowDsptr pvaluepEdotJ();
		virtual FRowDsptr pvaluepEdotK();
		virtual FRowDsptr pvaluepXdotI();
		virtual FRowDsptr pvaluepXdotJ();
		virtual FRowDsptr pvaluepXdotK();

	};
}

