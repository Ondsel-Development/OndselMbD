/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "ForTorActionComp.h"

namespace MbD {
	class ForTorActionKComp : public ForTorActionComp
	{
		//
	public:
		static std::shared_ptr<ForTorActionKComp> With();
		
		void calcPostDynCorrectorIteration() override;
		void fillAccICIterError(FColDsptr col) override;
		void fillAccICIterJacob(SpMatDsptr mat) override;
		void fillDynError(FColDsptr col) override;
		void fillpFpy(SpMatDsptr mat) override;
		void fillpFpypFTpfunctionfunction(SpMatDsptr mat, Symsptr pFTpfunction, Symsptr function);
		void fillpFpydot(SpMatDsptr mat) override;
		void fillpFpydotpFTpfunctionfunction(SpMatDsptr mat, Symsptr pFTpfunction, Symsptr function);
		void forceOnFrmIandFrmJ(EndFrmsptr eFrmI, EndFrmsptr eFrmJ) override;
		void torqueOnFrmIandFrmJ(EndFrmsptr eFrmI, EndFrmsptr eFrmJ) override;
		FColDsptr getFTIeO() const override;

		PartFrame* pfrmK;
		FColDsptr aFTIeO;
		EndFrmsptr efrmK;
		FColDsptr aAjOKe;


		ForTorActionKComp() = default;
	};
}
