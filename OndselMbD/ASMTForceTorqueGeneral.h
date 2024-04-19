/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "ASMTForceTorque.h"

namespace MbD {
	class ASMTForceTorqueGeneral : public ASMTForceTorque
	{
		//
	public:
		static std::shared_ptr<ASMTForceTorqueGeneral> With();

		void createMbD(std::shared_ptr<System> mbdSys, std::shared_ptr<Units> mbdUnits) override;


	};
}

