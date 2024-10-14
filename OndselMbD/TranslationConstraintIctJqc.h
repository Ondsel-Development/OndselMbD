/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "TranslationConstraintIcJqc.h"

namespace MbD {
	class TranslationConstraintIctJqc : public TranslationConstraintIcJqc
	{
		//pGpt ppGpXIpt ppGpEIpt ppGpXJpt ppGpEJpt ppGptpt 
	public:
		TranslationConstraintIctJqc(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi) : TranslationConstraintIcJqc(frmi, frmj, axisi) {}
		static std::shared_ptr<TranslationConstraintIctJqc> With(EndFrmsptr frmi, EndFrmsptr frmj, size_t axisi);

		void fillAccICIterError(FColDsptr col) override;
		void fillVelICError(FColDsptr col) override;
		void initriIeJeIe() override;
		void preAccIC() override;
		void preVelIC() override;
		ConstraintType type() override;

		double pGpt;
		FRowDsptr ppGpXIpt;
		FRowDsptr ppGpEIpt;
		FRowDsptr ppGpXJpt;
		FRowDsptr ppGpEJpt;
		double ppGptpt;
	};
}

