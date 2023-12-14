/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include <memory>

#include "FullMatrix.h"

namespace MbD {
	class DifferenceOperator
	{
		//iStep order taylorMatrix operatorMatrix time timeNodes 
	public:
		void calcOperatorMatrix();
		virtual void initialize();
		virtual void initializeLocally();
		virtual void setiStep(int i);
		virtual void setorder(int o);
		virtual void formTaylorMatrix();
		virtual void instantiateTaylorMatrix();
		virtual void formTaylorRowwithTimeNodederivative(int i, int ii, int k);
		void settime(double t);
		void formDegenerateTaylorRow(int i);
		double currentStepSize();
		int direction();
		bool isConstantStepFor(int nsteps);
		bool isDecreasingStepFor(int nsteps);
		bool isIncreasingStepFor(int nsteps);
		FColDsptr valueWith(std::shared_ptr<std::vector<FColDsptr>> ypast);
		FColDsptr derivativewith(int deriv, std::shared_ptr<std::vector<FColDsptr>> series);
		virtual FColDsptr derivativeatpresentpast(int n, double t, FColDsptr y, std::shared_ptr<std::vector<FColDsptr>> ypast);
		void noop();

		int iStep = 0, order = 0;
		FMatDsptr taylorMatrix, operatorMatrix;
		double time = 0.0;
		std::shared_ptr<std::vector<double>> timeNodes;	//"Row of past times in order of increasing past."
		static FRowDsptr OneOverFactorials;
	};
}

