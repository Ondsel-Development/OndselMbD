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
	class DispCompIecJecKec : public KinematicIJ
	{
		//efrmK axisK riIeJeKe aAjOKe rIeJeO 
	public:
		DispCompIecJecKec() {}
		DispCompIecJecKec(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk, size_t axisk) : KinematicIJ(frmi, frmj), efrmK(frmk), axisK(axisk) {}
		static std::shared_ptr<DispCompIecJecKec> With(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk, size_t axisk);
		void withFrmIfrmJfrmKaxis(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk, size_t axis) override;

		SpatialContainerFrame* partFrameK();
		double value() override;

		EndFrmsptr efrmK;
		size_t axisK;
		double riIeJeKe;
		FColDsptr aAjOKe;
		FColDsptr rIeJeO;
	};
}

