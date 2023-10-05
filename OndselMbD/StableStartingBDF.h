/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselMbD.                                       *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "StableBackwardDifference.h"

namespace MbD {


#pragma once
	class StableStartingBDF : public StableBackwardDifference
	{
		//
	public:
		void initialize() override;
		void initializeLocally() override;
		FColDsptr derivativeatpresentpastpresentDerivativepastDerivative(int n, double time, FColDsptr y, std::shared_ptr<std::vector<FColDsptr>> ypast,
			FColDsptr ydot, std::shared_ptr<std::vector<FColDsptr>> ydotpast);
		double pvdotpv() override;
		void formTaylorMatrix() override;
		void setorder(int o) override;
		void setiStep(int i) override;
		FColDsptr derivativepresentpastpresentDerivativepastDerivative(int n,
			FColDsptr y, std::shared_ptr<std::vector<FColDsptr>> ypast,
			FColDsptr ydot, std::shared_ptr<std::vector<FColDsptr>> ydotpast);
		FColDsptr derivativewith(int deriv, std::shared_ptr<std::vector<FColDsptr>> series);


	};
}
