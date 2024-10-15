/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "EndFramec.h"
#include "Symbolic.h"
#include "EulerParametersDot.h"
#include "EulerParametersDDot.h"
#include "FullColumn.h"     //FColDsptr is defined
#include "FullMatrix.h"     //FMatDsptr is defined

namespace MbD {
	class EndFrameqct;

	class EndFrameqc : public EndFramec
	{
		//prOeOpE pprOeOpEpE pAOepE ppAOepEpE
	public:
		EndFrameqc() {}
		EndFrameqc(const char* str) : EndFramec(str) {}
		static std::shared_ptr<EndFrameqc> With();
		static std::shared_ptr<EndFrameqc> With(const char* str);
		void initialize() override;

		void initializeGlobally() override;
		void initEndFrameqct() override;
		void initEndFrameqct2() override;
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
		FColDsptr rpep() override;
		FColFMatDsptr pAOppE();
		FMatDsptr aBOp();
		bool isEndFrameqc() override;
		FMatDsptr pvOeOpE();
		FColDsptr omeOeO();
		FMatDsptr pomeOeOpE();
		FMatDsptr pomeOeOpEdot();
		std::shared_ptr<EndFrameqc> followEndFrame(EndFrmsptr frmi) override;

		FMatDsptr prOeOpE;
		FMatFColDsptr pprOeOpEpE;
		FColFMatDsptr pAOepE;
		FMatFMatDsptr ppAOepEpE;
		std::shared_ptr<EndFrameqct> endFrameqct;
	};
}

