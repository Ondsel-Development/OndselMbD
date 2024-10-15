/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

 //#include <memory>
 //#include <vector>
 //#include <functional>

#include "SpatialContainerFrame.h"
#include "EndFrameqc.h"
#include "FullColumn.h"
#include "EulerParameters.h"
#include "EulerParametersDot.h"
#include "MarkerFrame.h"

namespace MbD {
	class Part;
	class MarkerFrame;
	class EulerConstraint;
	class AbsConstraint;

	class AssemblyFrame : public SpatialContainerFrame
	{
		//ToDo: part iqX iqE qX qE qXdot qEdot qXddot qEddot aGeu aGabs markerFrames 
	public:
		AssemblyFrame() {}
		AssemblyFrame(const char* str);
		static std::shared_ptr<AssemblyFrame> With();
		static std::shared_ptr<AssemblyFrame> With(const char* str);

		System* root() override;
		void initializeLocally() override;
		void initializeGlobally() override;
		void postInput() override;
		void calcPostDynCorrectorIteration() override;
		void setAssembly(System* x);
		System* getAssembly();

		void setPart(Part* x);

		//Needed because s may be used
		void fillqsu(FColDsptr col) override;
		void fillqsuWeights(DiagMatDsptr diagMat) override;
		void fillqsuddotlam(FColDsptr col) override;
		void fillqsulam(FColDsptr col) override;
		void fillpqsumu(FColDsptr col) override;
		void fillpqsumudot(FColDsptr col) override;
		void fillqsudot(FColDsptr col) override;
		void fillqsudotWeights(DiagMatDsptr diagMat) override;
		void useEquationNumbers() override;
		void setqsu(FColDsptr col) override;
		void setqsulam(FColDsptr col) override;
		void setqsudotlam(FColDsptr col) override;
		void setqsudot(FColDsptr col) override;
		void setqsuddotlam(FColDsptr col) override;
		void postPosICIteration() override;
		void fillPosICError(FColDsptr col) override;
		void fillPosICJacob(SpMatDsptr mat) override;
		void postPosIC() override;
		void preDyn() override;
		void storeDynState() override;
		void fillPosKineError(FColDsptr col) override;
		void preVelIC() override;
		void postVelIC() override;
		void fillVelICError(FColDsptr col) override;
		void fillVelICJacob(SpMatDsptr mat) override;
		void preAccIC() override;
		void fillAccICIterError(FColDsptr col) override;
		void fillAccICIterJacob(SpMatDsptr mat) override;
		void fillPosKineJacob(SpMatDsptr mat) override;
		void postDynStep() override;
		void setpqsumu(FColDsptr col) override;
		void setpqsumudot(FColDsptr col) override;
		void setpqsumuddot(FColDsptr col) override;
		void postDynPredictor() override;
		void fillDynError(FColDsptr col) override;
		void fillpFpy(SpMatDsptr mat) override;
		void fillpFpydot(SpMatDsptr mat) override;
		void postDynCorrectorIteration() override;
		void preDynOutput() override;
		void postDynOutput() override;
		double suggestSmallerOrAcceptDynStepSize(double hnew) override;

		System* assembly = nullptr; //Use raw pointer when pointing backwards.
	};
}

