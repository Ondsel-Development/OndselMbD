/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "BasicIntegrator.h"
#include "FullColumn.h"
#include "SparseMatrix.h"
#include "Extrapolator.h"
#include "DAECorrector.h"
#include "BackwardDifference.h"

namespace MbD {
	class BasicDAEIntegrator : public BasicIntegrator
	{
		//y ydot dy ypast ydotpast aF pFpy pFpydot alp aG extrapolator newtonRaphson corAbsTol corRelTol corOK integAbsTol integRelTol truncError 
	public:
		void initialize() override;
		void initializeGlobally() override;
		void firstStep() override;
		bool isRedoingFirstStep();
		bool isRedoingStep();
		void nextStep() override;
		//void reportStepStats();
		//void reportTrialStepStats();
		void runInitialConditionTypeSolution() override;
		void selectFirstStepSize();
		void selectStepSize();
		void predictFirstStep();
		void correctFirstStep();
		void changeTime();
		double selectBasicStepSize();
		double integErrorNormFromwrt(FColDsptr err, FColDsptr ref);
		double rmswrtrelativeTolabsoluteTol(FColDsptr vector, FColDsptr baseVector, FColDsptr relativeTol, FColDsptr absoluteTol);
		void predictValuesAtFirstStep();
		void predictValuesAtNextStep();
		void incrementTime() override;
		void correctValuesAtFirstStep();
		void correctValuesAtNextStep();
		void preDAECorrector();
		void postDAECorrector();
		FColDsptr fillF();
		int iterMax() override;
		SpMatDsptr calcG();
		virtual std::shared_ptr<LinearMultiStepMethod> correctorBDF();
		void calcOperatorMatrix() override;
		void setorder(int o) override;
		void settime(double t) override;
		void iStep(int i) override;
		double corErrorNormFromwrt(FColDsptr error, FColDsptr ref);
		void updateForDAECorrector();
		virtual FColDsptr yDeriv(int order);
		void calcTruncError();
		virtual FColDsptr dyOrderPlusOnedt();
		bool isConvergedForand(int iterNo, std::shared_ptr<std::vector<double>> dxNorms);
		void postFirstStep();
		void postStep();
		void predict();
		void correct();
		void selectStepSizeNormal();

		FColDsptr y, ydot, dy, aF, corAbsTol, corRelTol, integAbsTol, integRelTol;
		std::shared_ptr<std::vector<FColDsptr>> ypast, ydotpast;
		SpMatDsptr pFpy, pFpydot, matG;
		double alp, truncError;
		bool corOK;
		std::shared_ptr<Extrapolator> extrapolator;
		std::shared_ptr<DAECorrector> newtonRaphson;
	};
}
