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

		void setaAap(FMatDsptr mat);
		FColDsptr getqE();
		void setAssembly(System* x);
		System* getAssembly();

		void setPart(Part* x);
		Part* getPart();
		EndFrmsptr endFrame(std::string name);
		void aGabsDo(const std::function <void(std::shared_ptr<Constraint>)>& f);
		void markerFramesDo(const std::function <void(std::shared_ptr<MarkerFrame>)>& f) const;
		void removeRedundantConstraints(std::shared_ptr<std::vector<size_t>> redundantEqnNos) override;
		void reactivateRedundantConstraints() override;
		void constraintsReport() override;

		FColDsptr rOpO() override;
		FMatDsptr aAOp() override;
		FMatDsptr aC() override;
		FMatDsptr aCdot() override;
		FColDsptr alpOpO() override;
		FColFMatDsptr pAOppE() override;
		FColFMatDsptr pAdotOppE() override;
		FMatDsptr pomeOpOpE() override;
		FMatDsptr pomeOpOpEdot() override;
		FColDsptr vOpO() override;
		FMatDsptr aAdotOp() override;
		FColDsptr aOpO() override;
		FMatDsptr aAddotOp() override;
		void fillEssenConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> essenConstraints) override;
		void fillRedundantConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> redunConstraints) override;
		void fillConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> allConstraints) override;
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
		FMatDsptr aBOp();
		void fillPosKineJacob(SpMatDsptr mat) override;
		double suggestSmallerOrAcceptDynStepSize(double hnew) override;
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
		FColDsptr omeOpO() override;

		System* assembly = nullptr; //Use raw pointer when pointing backwards.
	};
}

