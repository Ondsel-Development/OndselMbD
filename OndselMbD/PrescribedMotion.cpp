/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include <iostream>	
#include <memory>
#include <typeinfo>
#include <assert.h>

#include "PrescribedMotion.h"
#include "EndFramect.h"
#include "EndFrameqct.h"
#include "Constant.h"

using namespace MbD;

std::shared_ptr<PrescribedMotion> MbD::PrescribedMotion::With(const char* str)
{
	auto inst = std::make_shared<PrescribedMotion>(str);
	inst->initialize();
	return inst;
}

void PrescribedMotion::initialize()
{
	JointIJ::initialize();
	xBlk = std::make_shared<Constant>(0.0);
	yBlk = std::make_shared<Constant>(0.0);
	zBlk = std::make_shared<Constant>(0.0);
	phiBlk = std::make_shared<Constant>(0.0);
	theBlk = std::make_shared<Constant>(0.0);
	psiBlk = std::make_shared<Constant>(0.0);
}

void MbD::PrescribedMotion::initMotions()
{
	auto xyzBlkList = std::initializer_list<Symsptr>{ xBlk, yBlk, zBlk };
	auto xyzRotBlkList = std::initializer_list<Symsptr>{ phiBlk, theBlk, psiBlk };

	auto efrmIct = std::dynamic_pointer_cast<EndFramect>(efrmI);
	auto efrmIqct = std::dynamic_pointer_cast<EndFrameqct>(efrmI);
	if (efrmIct && !efrmIqct) {
		efrmIct->rmemBlks = (std::make_shared<FullColumn<Symsptr>>(xyzBlkList));
		efrmIct->phiThePsiBlks = (std::make_shared<FullColumn<Symsptr>>(xyzRotBlkList));
	}
	else if (!efrmIct && efrmIqct) {
		efrmIqct->rmemBlks = (std::make_shared<FullColumn<Symsptr>>(xyzBlkList));
		efrmIqct->phiThePsiBlks = (std::make_shared<FullColumn<Symsptr>>(xyzRotBlkList));
	}
}

void PrescribedMotion::connectsItoJ(EndFrmsptr frmi, EndFrmsptr frmj)
{
	JointIJ::connectsItoJ(frmi, frmj);
	efrmI->initEndFrameqct();
}
