/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "ForceTorqueBasic.h"
#include "Part.h"

namespace MbD {
	class ForceBasiccVector : public ForceTorqueBasic
	{
		//iqX prOeOpET 
	public:
		static std::shared_ptr<ForceBasiccVector> With();
		static std::shared_ptr<ForceBasiccVector> With(EndFrmsptr efrmI);

		void calcPostDynCorrectorIteration() override;
		void fillAccICIterErroraFTO(FColDsptr col, FColDsptr aFTO) override;
		void fillAccICIterJacobpFTOplam(SpMatDsptr mat, SpMatDsptr pFTOplam) override;
		void fillDynErroraFTO(FColDsptr col, FColDsptr aFTO) override;
		void fillpFpyaFTO(SpMatDsptr mat, FColDsptr aFTO) override;
		void fillpFpypFTOpEjpartj(SpMatDsptr mat, FMatDsptr pFTOpEj, SpatialContainerFrame* partj) override;
		void fillpFpypFTOpXjpartj(SpMatDsptr mat, FMatDsptr pFTOpXj, SpatialContainerFrame* partj) override;
		void fillpFpypFTOpXjpFTOpEjpartj(SpMatDsptr mat, FMatDsptr pFTOpXj, FMatDsptr pFTOpEj, SpatialContainerFrame* partj) override;
		void fillpFpydotpFTOpEdotjpartj(SpMatDsptr mat, FMatDsptr pFTOpEdotj, SpatialContainerFrame* partj) override;
		void fillpFpydotpFTOpmudot(SpMatDsptr mat, SpMatDsptr pFTOpmudot) override;
		void fillpFpydotpFTOpXdotjpartj(SpMatDsptr mat, FMatDsptr pFTOpXdotj, SpatialContainerFrame* partj) override;
		void fillpFpydotpFTOpXdotjpFTOpEdotjpartj(SpMatDsptr mat, FMatDsptr pFTOpXdotj, FMatDsptr pFTOpEdotj, SpatialContainerFrame* partj) override;
		void useEquationNumbers() override;
	};
}
