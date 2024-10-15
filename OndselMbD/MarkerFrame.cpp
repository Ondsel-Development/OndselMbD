/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include<algorithm>

#include "MarkerFrame.h"
#include "SpatialContainerFrame.h"
#include "PartFrame.h"
 //#include "EndFramec.h"
#include "EndFrameqct.h"
#include "EulerParameters.h"

using namespace MbD;

std::shared_ptr<MarkerFrame> MbD::MarkerFrame::With(const char* str)
{
	auto inst = std::make_shared<MarkerFrame>(str);
	inst->initialize();
	return inst;
}

void MarkerFrame::initialize()
{
	endFrames = std::make_shared<std::vector<EndFrmsptr>>();
}

System* MarkerFrame::root()
{
	return partFrame->root();
}

void MarkerFrame::initializeLocally()
{
	assert(false);
}

void MarkerFrame::initializeGlobally()
{
	endFramesDo([](EndFrmsptr endFrame) { endFrame->initializeGlobally(); });
}

void MarkerFrame::postInput()
{
	CartesianFrame::postInput();
	endFramesDo([](EndFrmsptr endFrame) { endFrame->postInput(); });
}

void MarkerFrame::calcPostDynCorrectorIteration()
{
	assert(false);
}

void MarkerFrame::prePosIC()
{
	CartesianFrame::prePosIC();
	endFramesDo([](EndFrmsptr endFrame) { endFrame->prePosIC(); });
}

void MbD::MarkerFrame::prePosKine()
{
	CartesianFrame::prePosKine();
	endFramesDo([](EndFrmsptr endFrame) { endFrame->prePosKine(); });
}

void MbD::MarkerFrame::preStatic()
{
	assert(false);
}

FColDsptr MbD::MarkerFrame::omeOmO() const
{
	return partFrame->omeOpO();
}

void MarkerFrame::endFramesDo(const std::function<void(EndFrmsptr)>& f) const
{
	std::for_each(endFrames->begin(), endFrames->end(), f);
}

void MarkerFrame::fillqsu(FColDsptr col)
{
	endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->fillqsu(col); });
}

void MarkerFrame::fillqsuWeights(DiagMatDsptr diagMat)
{
	endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->fillqsuWeights(diagMat); });
}

void MbD::MarkerFrame::fillqsuddotlam(FColDsptr col)
{
	endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->fillqsuddotlam(col); });
}

void MarkerFrame::fillqsulam(FColDsptr col)
{
	endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->fillqsulam(col); });
}

void MbD::MarkerFrame::fillpqsumu(FColDsptr col)
{
	endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->fillpqsumu(col); });
}

void MbD::MarkerFrame::fillpqsumudot(FColDsptr col)
{
	endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->fillpqsumudot(col); });
}

void MarkerFrame::fillqsudot(FColDsptr col)
{
	endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->fillqsudot(col); });
}

void MbD::MarkerFrame::fillqsudotPlam(FColDsptr col)
{
	assert(false);
}

void MbD::MarkerFrame::fillqsudotPlamDeriv(FColDsptr col)
{
	assert(false);
}

void MarkerFrame::fillqsudotWeights(DiagMatDsptr diagMat)
{
	endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->fillqsudotWeights(diagMat); });
}

void MarkerFrame::setqsu(FColDsptr col)
{
	endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->setqsu(col); });
}

void MarkerFrame::setqsulam(FColDsptr col)
{
	endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->setqsulam(col); });
}

void MbD::MarkerFrame::simUpdateAll()
{
	CartesianFrame::simUpdateAll();
	endFramesDo([](EndFrmsptr endFrame) { endFrame->simUpdateAll(); });
}

void MarkerFrame::setqsudot(FColDsptr col)
{
	endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->setqsudot(col); });
}

void MarkerFrame::setqsudotlam(FColDsptr col)
{
	endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->setqsudotlam(col); });
}

void MbD::MarkerFrame::setqsudotPlam(FColDsptr col)
{
	assert(false);
}

void MbD::MarkerFrame::setqsudotPlamDeriv(FColDsptr col)
{
	assert(false);
}

void MarkerFrame::postPosICIteration()
{
	CartesianFrame::postPosICIteration();
	endFramesDo([](EndFrmsptr endFrame) { endFrame->postPosICIteration(); });
}

void MbD::MarkerFrame::postStaticIteration()
{
	assert(false);
}

void MarkerFrame::postPosIC()
{
	endFramesDo([](EndFrmsptr endFrame) { endFrame->postPosIC(); });
}

void MarkerFrame::preDyn()
{
	endFramesDo([](EndFrmsptr endFrame) { endFrame->preDyn(); });
}

void MarkerFrame::storeDynState()
{
	endFramesDo([](EndFrmsptr endFrame) { endFrame->storeDynState(); });
}

void MarkerFrame::preVelIC()
{
	CartesianFrame::preVelIC();
	endFramesDo([](EndFrmsptr endFrame) { endFrame->preVelIC(); });
}

void MarkerFrame::postVelIC()
{
	endFramesDo([](EndFrmsptr endFrame) { endFrame->postVelIC(); });
}

void MarkerFrame::preAccIC()
{
	CartesianFrame::preAccIC();
	endFramesDo([](EndFrmsptr endFrame) { endFrame->preAccIC(); });
}

void MbD::MarkerFrame::preDynOutput()
{
	CartesianFrame::preDynOutput();
	endFramesDo([](EndFrmsptr endFrame) { endFrame->preDynOutput(); });
}

FColDsptr MbD::MarkerFrame::rmemOFrOeO(FColDsptr rOeOCol) const
{
	return aAOm->transposeTimesFullColumn(rOeOCol->minusFullColumn(rOmO));
}

FColDsptr MbD::MarkerFrame::rOeOOFrmem(FColDsptr rmemCol) const
{
	return rOmO->plusFullColumn(aAOm->timesFullColumn(rmemCol));
}

void MarkerFrame::setqsuddotlam(FColDsptr col)
{
	endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->setqsuddotlam(col); });
}

void MarkerFrame::postDynStep()
{
	endFramesDo([](EndFrmsptr endFrame) { endFrame->postDynStep(); });
}

void MbD::MarkerFrame::setpqsumu(FColDsptr col)
{
	endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->setpqsumu(col); });
}

void MbD::MarkerFrame::setpqsumudot(FColDsptr col)
{
	endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->setpqsumudot(col); });
}

void MbD::MarkerFrame::setpqsumuddot(FColDsptr col)
{
	endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->setpqsumuddot(col); });
}

void MbD::MarkerFrame::postDynPredictor()
{
	CartesianFrame::postDynPredictor();
	endFramesDo([](EndFrmsptr endFrame) { endFrame->postDynPredictor(); });
}

void MbD::MarkerFrame::postDynOutput()
{
	CartesianFrame::postDynOutput();
	endFramesDo([](EndFrmsptr endFrame) { endFrame->postDynOutput(); });
}

void MbD::MarkerFrame::postDynCorrectorIteration()
{
	CartesianFrame::postDynCorrectorIteration();
	endFramesDo([](EndFrmsptr endFrame) { endFrame->postDynCorrectorIteration(); });
}

FColDsptr MbD::MarkerFrame::vOmO() const
{
	assert(false);
	return FColDsptr();
}

FColDsptr MbD::MarkerFrame::vOeO_of_rmem() const
{
	assert(false);
	return FColDsptr();
}

FColDsptr MbD::MarkerFrame::aOmO() const
{
	PartFrame* prtFrmPtr = dynamic_cast<PartFrame*>(partFrame);
	if (prtFrmPtr) {
		return prtFrmPtr->aOpO()->plusFullColumn(partFrame->aAddotOp()->timesFullColumn(rpmp));
	}
	return FColDsptr();
}

void MarkerFrame::setPartFrame(SpatialContainerFrame* partFrm)
{
	partFrame = partFrm;
}

FMatDsptr MbD::MarkerFrame::pomeOmOpE()
{
	PartFrame* prtFrmPtr = dynamic_cast<PartFrame*>(partFrame);
	if (prtFrmPtr) {
		return prtFrmPtr->pomeOpOpE();
	}
	return FMatDsptr();
}

FMatDsptr MbD::MarkerFrame::pomeOmOpEdot()
{
	PartFrame* prtFrmPtr = dynamic_cast<PartFrame*>(partFrame);
	if (prtFrmPtr) {
		return prtFrmPtr->pomeOpOpEdot();
	}
	return FMatDsptr();
}

SpatialContainerFrame* MarkerFrame::getPartFrame() const {
	return partFrame;
}

void MarkerFrame::setrpmp(FColDsptr x) const
{
	rpmp->copyFrom(x);
}

FColDsptr MbD::MarkerFrame::aAdotjOm(size_t j)
{
	PartFrame* prtFrmPtr = dynamic_cast<PartFrame*>(partFrame);
	if (prtFrmPtr) {
		return prtFrmPtr->aAdotOp()->timesFullColumn(aApm->column(j));
	}
	return FColDsptr();
}

void MarkerFrame::setaApm(FMatDsptr mat) const
{
	aApm->copyFrom(mat);
}

void MarkerFrame::addEndFrame(EndFrmsptr endFrm)
{
	endFrm->setMarkerFrame(this);
	endFrames->push_back(endFrm);
}
