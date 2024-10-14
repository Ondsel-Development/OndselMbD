/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "EndFramect.h"
#include "Symbolic.h"
#include "EulerParametersDot.h"
#include "EulerParametersDDot.h"

namespace MbD {

	class EndFrameqct : public EndFramect
	{
		//prOeOpE pprOeOpEpE pAOepE ppAOepEpE
	public:
		EndFrameqct() {}
		EndFrameqct(const char* str) : EndFramect(str) {}
		static std::shared_ptr<EndFrameqct> With();
		static std::shared_ptr<EndFrameqct> With(const char* str);
		void initialize() override;

		void initializeGlobally() override;
		FMatFColDsptr ppAjOepEpE(size_t j) const;
		void calcPostDynCorrectorIteration() override;
		FMatDsptr pAjOepE(size_t j) const;
		FMatDsptr pAjOepET(size_t j) const;
		FMatDsptr ppriOeOpEpE(size_t i) const;
		size_t iqX();
		size_t iqE();
		FRowDsptr priOeOpE(size_t i) const;
		FColDsptr qXdot();
		std::shared_ptr<EulerParametersDot<double>> qEdot();
		FColDsptr qXddot();
		FColDsptr qEddot();
		FColDsptr rpep();
		FColFMatDsptr pAOppE();
		FMatDsptr aBOp();
		bool isEndFrameqc() override;
		FMatDsptr pvOeOpE();
		FColDsptr omeOeO();
		FMatDsptr pomeOeOpE();
		FMatDsptr pomeOeOpEdot();
		void initializeLocally() override;
		void initprmemptBlks();
		void initpprmemptptBlks();
		virtual void initpPhiThePsiptBlks();
		virtual void initppPhiThePsiptptBlks();
		void postInput() override;
		double time = 0.0;
		FRowDsptr ppriOeOpEpt(size_t i) const;
		FMatDsptr ppAjOepETpt(size_t j) const;

		FMatDsptr prOeOpE;
		FMatFColDsptr pprOeOpEpE;
		FColFMatDsptr pAOepE;
		FMatFMatDsptr ppAOepEpE;
		FMatDsptr pprOeOpEpt;
		FColFMatDsptr ppAOepEpt;
	};
}

