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
	class DispCompIecJecIe : public KinematicIJ
	{
		//axis riIeJeIe aAjOIe rIeJeO 
	public:
		DispCompIecJecIe() {}
		DispCompIecJecIe(EndFrmsptr frmi, EndFrmsptr frmj, size_t axis) : KinematicIJ(frmi, frmj), axis(axis) {}
		static std::shared_ptr<DispCompIecJecIe> With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axis);
		void withFrmIfrmJaxis(EndFrmsptr frmi, EndFrmsptr frmj, size_t axis) override;

		void calc_value() override;
		void calcPostDynCorrectorIteration() override;
		double value() override;

		size_t axis;
		double riIeJeIe;
		FColDsptr aAjOIe, rIeJeO;
	};
}

