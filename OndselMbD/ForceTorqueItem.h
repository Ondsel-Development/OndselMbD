/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "Item.h"
#include "ForceFunctionParser.h"

namespace MbD {
	class ForceTorqueItem : public Item
	{
		//
	public:
		ForceTorqueItem() {}
		ForceTorqueItem(EndFrmsptr frmi, EndFrmsptr frmj) : frmI(frmi), frmJ(frmj) {}
		static std::shared_ptr<ForceTorqueItem> With(EndFrmsptr frmi, EndFrmsptr frmj);
		
		virtual void forceOnFrmIandFrmJ(EndFrmsptr eFrmI, EndFrmsptr eFrmJ);
		virtual void torqueOnFrmIandFrmJ(EndFrmsptr eFrmI, EndFrmsptr eFrmJ);
		void fillStaticError(FColDsptr col) override;
		void fillStaticJacob(SpMatDsptr mat) override;
		void postAccICIteration() override;
		void postCollisionCorrectorIteration() override;
		void postCollisionPredictor() override;
		virtual FColDsptr aFX() const;
		virtual FColDsptr aTX() const;
		virtual FColDsptr getFTIeO() const;

		EndFrmsptr frmI, frmJ;
	};
}

