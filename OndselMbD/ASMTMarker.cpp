/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "ASMTMarker.h"
#include "ASMTPart.h"
#include "ASMTAssembly.h"
#include "FullMatrix.h"
#include "ASMTRefItem.h"
#include "ASMTPart.h"
#include "Part.h"
#include "PartFrame.h"
#include "AssemblyFrame.h"
#include "MarkerFrame.h"
#include "MarkerFramec.h"
#include "MarkerFrameqc.h"
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
    auto asmtPrt = dynamic_cast<ASMTPart*>(partOrAssembly());
    auto asmtAsm = dynamic_cast<ASMTAssembly*>(partOrAssembly());
    if (asmtPrt && !asmtAsm) {
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
    else if (!asmtPrt && asmtAsm) {
        auto refItem = static_cast<ASMTRefItem*>(container);
        auto& rPrefP = refItem->position3D;
        auto& aAPref = refItem->rotationMatrix;
        auto& rrefmref = position3D;
        auto rPmP = rPrefP->plusFullColumn(aAPref->timesFullColumn(rrefmref));
        return rPmP;
    }
}

FMatDsptr MbD::ASMTMarker::aApm()
{
    auto asmtPrt = dynamic_cast<ASMTPart*>(partOrAssembly());
    auto asmtAsm = dynamic_cast<ASMTAssembly*>(partOrAssembly());
    if (asmtPrt && !asmtAsm) {
        //p is cm
        auto refItem = static_cast<ASMTRefItem*>(container);
        auto& aAPref = refItem->rotationMatrix;
        auto& aArefm = rotationMatrix;
        auto& principalMassMarker = static_cast<ASMTPart*>(refItem->container)->principalMassMarker;
        auto& aAPcm = principalMassMarker->rotationMatrix;
        auto aApm = aAPcm->transposeTimesFullMatrix(aAPref->timesFullMatrix(aArefm));
        return aApm;
    }
    else if (!asmtPrt && asmtAsm) {
        auto refItem = static_cast<ASMTRefItem*>(container);
        auto& aAPref = refItem->rotationMatrix;
        auto& aArefm = rotationMatrix;
        auto aAPm = aAPref->timesFullMatrix(aArefm);
        return aAPm;
    }
}

void ASMTMarker::createMbD()
{
    //ASMTMarker === MarkerFrame
    //ASMTRefPoint is for CAD side and not MbD side
    auto asmtPrt = dynamic_cast<ASMTPart*>(partOrAssembly());
    auto asmtAsm = dynamic_cast<ASMTAssembly*>(partOrAssembly());
    std::shared_ptr<MarkerFrame> mkr;
    std::shared_ptr<EndFramec> efrm;
    std::shared_ptr<SpatialContainerFrame> scfrm;
    if (asmtPrt && !asmtAsm) {
        scfrm = std::static_pointer_cast<Part>(asmtPrt->mbdObject)->partFrame;
        mkr = MarkerFrameqc::With(name.c_str());
        efrm = EndFrameqc::With();
    }
    else if (!asmtPrt && asmtAsm) {
        scfrm = std::static_pointer_cast<System>(asmtAsm->mbdObject)->asmFrame;
        mkr = MarkerFramec::With(name.c_str());
        efrm = EndFramec::With();
    }
    scfrm->addMarkerFrame(mkr);
    mkr->rpmp = rpmp()->times(asmtUnits()->length);
    mkr->aApm = aApm();
    mkr->addEndFrame(efrm);
    mbdObject = efrm;
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
