/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "AngleZIecJec.h"

namespace MbD {
	class AngleZIeqcJec : public AngleZIecJec
	{
		//pthezpEI ppthezpEIpEI pcthezpEI psthezpEI 
	public:
		AngleZIeqcJec() {}
		AngleZIeqcJec(EndFrmsptr frmi, EndFrmsptr frmj) : AngleZIecJec(frmi, frmj) {}
		static std::shared_ptr<AngleZIeqcJec> With();
		static std::shared_ptr<AngleZIeqcJec> With(EndFrmsptr frmi, EndFrmsptr frmj);
		void initialize() override;

		void calcPostDynCorrectorIteration() override;
		void init_aAijIeJe() override;
		FMatDsptr ppvaluepEIpEI() override;
		FRowDsptr pvaluepEI() override;

		FRowDsptr pthezpEI, pcthezpEI, psthezpEI;
		FMatDsptr ppthezpEIpEI;
	};
}

