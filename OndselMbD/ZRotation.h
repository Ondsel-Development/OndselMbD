/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "PrescribedMotion.h"

namespace MbD {
	class ZRotation : public PrescribedMotion
	{
		//
	public:
		ZRotation() {}
		ZRotation(const char* str);
		static std::shared_ptr<ZRotation> With();
		static std::shared_ptr<ZRotation> With(const char* str);

		void initializeGlobally() override;
	};
}

