/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "ASMTConstraintSet.h"
#include "ASMTAssembly.h"
#include "ASMTMarker.h"
#include "JointIJ.h"
#include "FullMatrix.h"
#include "EndFrameqc.h"
#include "Part.h"

using namespace MbD;

std::shared_ptr<ASMTConstraintSet> MbD::ASMTConstraintSet::With()
{
	auto inst = std::make_shared<ASMTConstraintSet>();
	inst->initialize();
	return inst;
}

void MbD::ASMTConstraintSet::createMbD()
{
	auto mbdJt = mbdClassNew();
	mbdObject = mbdJt;
	mbdJt->name = fullName("");
	auto mrkI = std::static_pointer_cast<EndFramec>(markerI->mbdObject);
	auto mrkJ = std::static_pointer_cast<EndFramec>(markerJ->mbdObject);
	mbdJt->connectsItoJ(mrkI, mrkJ);
	mbdSys()->addJoint(mbdJt);
}

std::shared_ptr<JointIJ> MbD::ASMTConstraintSet::mbdClassNew()
{
	//Should not create abstract class.
	assert(false);
	return std::shared_ptr<JointIJ>();
}

void MbD::ASMTConstraintSet::updateFromMbD()
{
	//"
	//MbD returns aFIeO and aTIeO.
	//GEO needs aFImO and aTImO.
	//For Motion rImIeO is not zero and is changing.
	//aFImO = aFIeO.
	//aTImO = aTIeO + (rImIeO cross : aFIeO).
	//"
	auto mbdUnts = mbdUnits();
	auto mbdJoint = std::static_pointer_cast<JointIJ>(mbdObject);
	auto aFIeO = mbdJoint->aFX()->times(mbdUnts->force);
	auto aTIeO = mbdJoint->aTX()->times(mbdUnts->torque);
	auto rImIeO = mbdJoint->efrmI->rmeO()->times(mbdUnts->length);
	auto aFIO = aFIeO;
	auto aTIO = aTIeO->plusFullColumn(rImIeO->cross(aFIeO));
	cFIO->push_back(aFIO);
	cTIO->push_back(aTIO);
}

void MbD::ASMTConstraintSet::compareResults(AnalysisType)
{
	if (infxs == nullptr || infxs->empty()) return;
	auto mbdUnts = mbdUnits();
	//auto factor = 1.0e-6;
	//auto forceTol = mbdUnts->force * factor;
	//auto torqueTol = mbdUnts->torque * factor;
	//auto i = fxs->size() - 1;
	//assert(Numeric::equaltol(fxs->at(i), infxs->at(i), forceTol));
	//assert(Numeric::equaltol(fys->at(i), infys->at(i), forceTol));
	//assert(Numeric::equaltol(fzs->at(i), infzs->at(i), forceTol));
	//assert(Numeric::equaltol(txs->at(i), intxs->at(i), torqueTol));
	//assert(Numeric::equaltol(tys->at(i), intys->at(i), torqueTol));
	//assert(Numeric::equaltol(tzs->at(i), intzs->at(i), torqueTol));
}

void MbD::ASMTConstraintSet::outputResults(AnalysisType)
{
	assert(false);
}

void MbD::ASMTConstraintSet::updateFromInputState()
{
	//Do nothing.
}
