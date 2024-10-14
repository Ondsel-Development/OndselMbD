/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include<algorithm>

#include "SpatialContainerFrame.h"
#include "PartFrame.h"
#include "MarkerFramec.h"
 //#include "EndFramec.h"
#include "EndFramect.h"
#include "EulerParameters.h"

using namespace MbD;

MarkerFramec::MarkerFramec(const char* str) : MarkerFrame(str)
{
	//Do nothing.
}

std::shared_ptr<MarkerFramec> MbD::MarkerFramec::With(const char* str)
{
	auto inst = std::make_shared<MarkerFramec>(str);
	inst->initialize();
	return inst;
}

System* MarkerFramec::root()
{
	return partFrame->root();
}

void MarkerFramec::initializeLocally()
{
	for (size_t i = 0; i < endFrames->size(); i++)
	{
		auto eFrmc = std::dynamic_pointer_cast<EndFramec>(endFrames->at(i));
		if (eFrmc) {
			if (eFrmc->endFramect) {
				endFrames->at(i) = eFrmc->endFramect;
			}
		}
	}
	endFramesDo([](EndFrmsptr endFrame) { endFrame->initializeLocally(); });
}

void MarkerFramec::initializeGlobally()
{
	endFramesDo([](EndFrmsptr endFrame) { endFrame->initializeGlobally(); });
}

void MarkerFramec::postInput()
{
	CartesianFrame::postInput();
	endFramesDo([](EndFrmsptr endFrame) { endFrame->postInput(); });
}

void MarkerFramec::calcPostDynCorrectorIteration()
{
	PartFrame* prtFrmPtr = dynamic_cast<PartFrame*>(partFrame);
	if (prtFrmPtr) {
		auto rOpO = prtFrmPtr->rOpO();
		auto aAOp = prtFrmPtr->aAOp();
		rOmO = rOpO->plusFullColumn(aAOp->timesFullColumn(rpmp));
		aAOm = aAOp->timesFullMatrix(aApm);
		auto pAOppE = prtFrmPtr->pAOppE();
	}
}

void MbD::MarkerFramec::preStatic()
{
	assert(false);
}

FColDsptr MbD::MarkerFramec::omeOmO() const
{
	return partFrame->omeOpO();
}

size_t MarkerFramec::iqX() const
{
	PartFrame* prtFrmPtr = dynamic_cast<PartFrame*>(partFrame);
	if (prtFrmPtr) {
		return prtFrmPtr->iqX;
	}
	return SIZE_MAX;
}

size_t MarkerFramec::iqE() const
{
	PartFrame* prtFrmPtr = dynamic_cast<PartFrame*>(partFrame);
	if (prtFrmPtr) {
		return prtFrmPtr->iqE;
	}
	return SIZE_MAX;
}

void MarkerFramec::fillqsu(FColDsptr col)
{
	endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->fillqsu(col); });
}

void MarkerFramec::fillqsuWeights(DiagMatDsptr diagMat)
{
	endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->fillqsuWeights(diagMat); });
}

void MbD::MarkerFramec::fillqsuddotlam(FColDsptr col)
{
	endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->fillqsuddotlam(col); });
}

void MarkerFramec::fillqsulam(FColDsptr col)
{
	endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->fillqsulam(col); });
}

void MbD::MarkerFramec::fillpqsumu(FColDsptr col)
{
	endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->fillpqsumu(col); });
}

void MbD::MarkerFramec::fillpqsumudot(FColDsptr col)
{
	endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->fillpqsumudot(col); });
}

void MarkerFramec::fillqsudot(FColDsptr col)
{
	endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->fillqsudot(col); });
}

void MbD::MarkerFramec::fillqsudotPlam(FColDsptr col)
{
	assert(false);
}

void MbD::MarkerFramec::fillqsudotPlamDeriv(FColDsptr col)
{
	assert(false);
}

void MarkerFramec::fillqsudotWeights(DiagMatDsptr diagMat)
{
	endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->fillqsudotWeights(diagMat); });
}

void MarkerFramec::setqsu(FColDsptr col)
{
	endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->setqsu(col); });
}

void MarkerFramec::setqsulam(FColDsptr col)
{
	endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->setqsulam(col); });
}

void MbD::MarkerFramec::simUpdateAll()
{
	CartesianFrame::simUpdateAll();
	endFramesDo([](EndFrmsptr endFrame) { endFrame->simUpdateAll(); });
}

void MarkerFramec::setqsudot(FColDsptr col)
{
	endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->setqsudot(col); });
}

void MarkerFramec::setqsudotlam(FColDsptr col)
{
	endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->setqsudotlam(col); });
}

void MbD::MarkerFramec::setqsudotPlam(FColDsptr col)
{
	assert(false);
}

void MbD::MarkerFramec::setqsudotPlamDeriv(FColDsptr col)
{
	assert(false);
}

void MarkerFramec::postPosICIteration()
{
	CartesianFrame::postPosICIteration();
	endFramesDo([](EndFrmsptr endFrame) { endFrame->postPosICIteration(); });
}

void MbD::MarkerFramec::postStaticIteration()
{
	assert(false);
}

void MarkerFramec::postPosIC()
{
	endFramesDo([](EndFrmsptr endFrame) { endFrame->postPosIC(); });
}

void MarkerFramec::preDyn()
{
	endFramesDo([](EndFrmsptr endFrame) { endFrame->preDyn(); });
}

void MarkerFramec::storeDynState()
{
	endFramesDo([](EndFrmsptr endFrame) { endFrame->storeDynState(); });
}

void MarkerFramec::preVelIC()
{
	CartesianFrame::preVelIC();
	endFramesDo([](EndFrmsptr endFrame) { endFrame->preVelIC(); });
}

void MarkerFramec::postVelIC()
{
	endFramesDo([](EndFrmsptr endFrame) { endFrame->postVelIC(); });
}

void MarkerFramec::preAccIC()
{
	CartesianFrame::preAccIC();
	endFramesDo([](EndFrmsptr endFrame) { endFrame->preAccIC(); });
}

void MbD::MarkerFramec::preDynOutput()
{
	CartesianFrame::preDynOutput();
	endFramesDo([](EndFrmsptr endFrame) { endFrame->preDynOutput(); });
}

FColDsptr MbD::MarkerFramec::rmemOFrOeO(FColDsptr rOeOCol) const
{
	return aAOm->transposeTimesFullColumn(rOeOCol->minusFullColumn(rOmO));
}

FColDsptr MbD::MarkerFramec::rOeOOFrmem(FColDsptr rmemCol) const
{
	return rOmO->plusFullColumn(aAOm->timesFullColumn(rmemCol));
}

void MarkerFramec::setqsuddotlam(FColDsptr col)
{
	endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->setqsuddotlam(col); });
}

FMatDsptr MarkerFramec::aBOp()
{
	PartFrame* prtFrmPtr = dynamic_cast<PartFrame*>(partFrame);
	if (prtFrmPtr) {
		return prtFrmPtr->aBOp();
	}
	return FMatDsptr();
}

void MarkerFramec::postDynStep()
{
	endFramesDo([](EndFrmsptr endFrame) { endFrame->postDynStep(); });
}

void MbD::MarkerFramec::setpqsumu(FColDsptr col)
{
	endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->setpqsumu(col); });
}

void MbD::MarkerFramec::setpqsumudot(FColDsptr col)
{
	endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->setpqsumudot(col); });
}

void MbD::MarkerFramec::setpqsumuddot(FColDsptr col)
{
	endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->setpqsumuddot(col); });
}

void MbD::MarkerFramec::postDynPredictor()
{
	CartesianFrame::postDynPredictor();
	endFramesDo([](EndFrmsptr endFrame) { endFrame->postDynPredictor(); });
}

void MbD::MarkerFramec::postDynOutput()
{
	CartesianFrame::postDynOutput();
	endFramesDo([](EndFrmsptr endFrame) { endFrame->postDynOutput(); });
}

void MbD::MarkerFramec::postDynCorrectorIteration()
{
	CartesianFrame::postDynCorrectorIteration();
	endFramesDo([](EndFrmsptr endFrame) { endFrame->postDynCorrectorIteration(); });
}

FColDsptr MbD::MarkerFramec::vOmO() const
{
	PartFrame* prtFrmPtr = dynamic_cast<PartFrame*>(partFrame);
	if (prtFrmPtr) {
		return prtFrmPtr->vOpO()->plusFullColumn(partFrame->aAdotOp()->timesFullColumn(rpmp));
	}
	return FColDsptr();
}

FColDsptr MbD::MarkerFramec::vOeO_of_rmem() const
{
	assert(false);
	return FColDsptr();
}

FColDsptr MbD::MarkerFramec::aOmO() const
{
	PartFrame* prtFrmPtr = dynamic_cast<PartFrame*>(partFrame);
	if (prtFrmPtr) {
		return prtFrmPtr->aOpO()->plusFullColumn(partFrame->aAddotOp()->timesFullColumn(rpmp));
	}
	return FColDsptr();
}

void MarkerFramec::setPartFrame(SpatialContainerFrame* partFrm)
{
	partFrame = partFrm;
}

SpatialContainerFrame* MarkerFramec::getPartFrame() const {
	return partFrame;
}

void MarkerFramec::setrpmp(FColDsptr x) const
{
	rpmp->copyFrom(x);
}

FColDsptr MbD::MarkerFramec::aAdotjOm(size_t j)
{
	PartFrame* prtFrmPtr = dynamic_cast<PartFrame*>(partFrame);
	if (prtFrmPtr) {
		return prtFrmPtr->aAdotOp()->timesFullColumn(aApm->column(j));
	}
	return FColDsptr();
}

void MarkerFramec::setaApm(FMatDsptr mat) const
{
	aApm->copyFrom(mat);
}

void MarkerFramec::addEndFrame(EndFrmsptr endFrm)
{
	endFrm->setMarkerFrame(this);
	endFrames->push_back(endFrm);
}
