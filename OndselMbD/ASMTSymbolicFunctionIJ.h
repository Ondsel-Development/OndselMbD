/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include "ASMTSymbolicFunction.h"
#include "KinematicIeJe.h"

namespace MbD {
	class ASMTSymbolicFunctionIJ : public ASMTSymbolicFunction
	{
		//
	public:
		ASMTSymbolicFunctionIJ() {}
		ASMTSymbolicFunctionIJ(std::shared_ptr<ASMTItemIJ> itemIJ);
		static std::shared_ptr<ASMTSymbolicFunctionIJ> With();

		virtual std::shared_ptr<KinematicIeJe> mbdClassNew();
		virtual void withFrmIfrmJ(EndFrmsptr eFrmI, EndFrmsptr eFrmJ);
		void createMbD(std::shared_ptr<System> mbdSys, std::shared_ptr<Units> mbdUnits) override;

		std::shared_ptr<ASMTItemIJ> geoIJ;
	};
}
