/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "ForceTorqueItem.h"
#include "ForceVector.h"
#include "TorqueVector.h"

namespace MbD {
	class ForceTorqueGeneral : public ForceTorqueItem
	{
		//forceVector torqueVector 
	public:
		ForceTorqueGeneral(EndFrmsptr frmi, EndFrmsptr frmj);
		ForceTorqueGeneral(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk);
		static std::shared_ptr<ForceTorqueGeneral> With(EndFrmsptr frmi, EndFrmsptr frmj);
		static std::shared_ptr<ForceTorqueGeneral> With(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk);

		FColDsptr aFX() const override;
		FColDsptr aTX() const override;
		void fillAccICIterError(FColDsptr col) override;
		void fillAccICIterJacob(SpMatDsptr mat) override;
		void fillDynError(FColDsptr col) override;
		void fillpFpy(SpMatDsptr mat) override;
		void fillpFpydot(SpMatDsptr mat) override;
		void fillStaticError(FColDsptr col) override;
		void fillStaticJacob(SpMatDsptr mat) override;
		void forceFunctions(FColDsptr col);
		void initializeGlobally() override;
		void initializeLocally() override;
		void postAccICIteration() override;
		void postCollisionCorrectorIteration() override;
		void postCollisionPredictor() override;
		void postDynCorrectorIteration() override;
		void postDynOutput() override;
		void postDynPredictor() override;
		void postInput() override;
		void postStaticIteration() override;
		void preAccIC() override;
		void preDynOutput() override;
		void preStatic() override;
		void simUpdateAll() override;
		void torqueFunctions(FColDsptr col);
		void useEquationNumbers() override;

		std::shared_ptr<ForceVector> forceVector;
		std::shared_ptr<TorqueVector> torqueVector;
	};
}

