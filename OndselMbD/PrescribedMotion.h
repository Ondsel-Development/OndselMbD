/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once
#include <memory>

#include "Joint.h"

namespace MbD {
	class Symbolic;
	using Symsptr = std::shared_ptr<Symbolic>;
	class EndFramec;

	class PrescribedMotion : public Joint
	{
		//xBlk yBlk zBlk phiBlk theBlk psiBlk 
	public:
		PrescribedMotion() {}
		PrescribedMotion(const char* str);
		static std::shared_ptr<PrescribedMotion> With(const char* str);
		void initialize() override;

		void connectsItoJ(EndFrmsptr frmI, EndFrmsptr frmJ) override;
		virtual void initMotions();

		Symsptr xBlk;
		Symsptr yBlk;
		Symsptr zBlk;
		Symsptr phiBlk;
		Symsptr theBlk;
		Symsptr psiBlk;
	};
}

