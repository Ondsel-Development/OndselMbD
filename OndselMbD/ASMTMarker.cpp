/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "ASMTMarker.h"
#include "FullMatrix.h"
#include "ASMTRefItem.h"
#include "ASMTPart.h"
#include "Part.h"
#include "PartFrame.h"
#include "MarkerFrame.h"
#include "ASMTPrincipalMassMarker.h"
#include "Units.h"

using namespace MbD;

std::shared_ptr<ASMTMarker> MbD::ASMTMarker::With()
{
	auto inst = std::make_shared<ASMTMarker>();
	inst->initialize();
	return inst;
}

void MbD::ASMTMarker::parseASMT(std::vector<std::string>& lines)
{
	readName(lines);
	readPosition3D(lines);
	readRotationMatrix(lines);
}

FColDsptr MbD::ASMTMarker::rpmp()
{
	//p is cm
	auto refItem = static_cast<ASMTRefItem*>(container);
	auto& rPrefP = refItem->position3D;
	auto& aAPref = refItem->rotationMatrix;
	auto& rrefmref = position3D;
	auto rPmP = rPrefP->plusFullColumn(aAPref->timesFullColumn(rrefmref));
	auto& principalMassMarker = static_cast<ASMTPart*>(refItem->container)->principalMassMarker;
	auto& rPcmP = principalMassMarker->position3D;
	auto& aAPcm = principalMassMarker->rotationMatrix;
	auto rpmp = aAPcm->transposeTimesFullColumn(rPmP->minusFullColumn(rPcmP));
	return rpmp;
}

FMatDsptr MbD::ASMTMarker::aApm()
{
	//p is cm
	auto refItem = static_cast<ASMTRefItem*>(container);
	auto& aAPref = refItem->rotationMatrix;
	auto& aArefm = rotationMatrix;
	auto& principalMassMarker = static_cast<ASMTPart*>(refItem->container)->principalMassMarker;
	auto& aAPcm = principalMassMarker->rotationMatrix;
	auto aApm = aAPcm->transposeTimesFullMatrix(aAPref->timesFullMatrix(aArefm));
	return aApm;
}

void ASMTMarker::createMbD()
{
	auto mkr = MarkerFrame::With(name.c_str());
	auto prt = std::static_pointer_cast<Part>(partOrAssembly()->mbdObject);
	prt->partFrame->addMarkerFrame(mkr);

	mkr->rpmp = rpmp()->times(asmtUnits()->length);
	mkr->aApm = aApm();
	mbdObject = mkr->endFrames->at(0);
}

void MbD::ASMTMarker::storeOnLevel(std::ofstream& os, size_t level)
{
	storeOnLevelString(os, level, "Marker");
	storeOnLevelString(os, level + 1, "Name");
	storeOnLevelString(os, level + 2, name);
	ASMTSpatialItem::storeOnLevel(os, level);
}

void MbD::ASMTMarker::updateFromInputState()
{
	//Do nothing.
}
