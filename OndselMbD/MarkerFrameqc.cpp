/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include<algorithm>

#include "MarkerFrameqc.h"
#include "MarkerFrame.h"
#include "PartFrame.h"
 //#include "EndFramec.h"
#include "EndFrameqct.h"
#include "EulerParameters.h"

using namespace MbD;

MarkerFrameqc::MarkerFrameqc(const char* str) : MarkerFrame(str)
{
	//Do nothing.
}

std::shared_ptr<MarkerFrameqc> MbD::MarkerFrameqc::With(const char* str)
{
	auto inst = std::make_shared<MarkerFrameqc>(str);
	inst->initialize();
	return inst;
}

void MarkerFrameqc::initialize()
{
	MarkerFrame::initialize();
	prOmOpE = FullMatrix<double>::With(3, 4);
	pAOmpE = std::make_shared<FullColumn<FMatDsptr>>(4);
}

System* MarkerFrameqc::root()
{
	auto prtFrmPtr = static_cast<PartFrame*>(partFrame);
	return partFrame->root();
}

void MarkerFrameqc::initializeLocally()
{
	pprOmOpEpE = EulerParameters<double>::ppApEpEtimesColumn(rpmp);
	ppAOmpEpE = EulerParameters<double>::ppApEpEtimesMatrix(aApm);
	for (size_t i = 0; i < endFrames->size(); i++)
	{
		auto eFrmqc = std::dynamic_pointer_cast<EndFrameqc>(endFrames->at(i));
		if (eFrmqc) {
			if (eFrmqc->endFrameqct) {
				endFrames->at(i) = eFrmqc->endFrameqct;
			}
		}
	}
	endFramesDo([](EndFrmsptr endFrame) { endFrame->initializeLocally(); });
}
/// <summary>
/// 
/// </summary>
void MarkerFrameqc::initializeGlobally()
{
	endFramesDo([](EndFrmsptr endFrame) { endFrame->initializeGlobally(); });
}

void MarkerFrameqc::postInput()
{
	CartesianFrame::postInput();
	endFramesDo([](EndFrmsptr endFrame) { endFrame->postInput(); });
}

void MarkerFrameqc::calcPostDynCorrectorIteration()
{
	auto rOpO = partFrame->rOpO();
	auto aAOp = partFrame->aAOp();
	rOmO = rOpO->plusFullColumn(aAOp->timesFullColumn(rpmp));
	aAOm = aAOp->timesFullMatrix(aApm);
	auto pAOppE = partFrame->pAOppE();
	for (size_t i = 0; i < 4; i++)
	{
		auto& pAOppEi = pAOppE->at(i);
		prOmOpE->atandputFullColumn(0, i, pAOppEi->timesFullColumn(rpmp));
		pAOmpE->at(i) = pAOppEi->timesFullMatrix(aApm);
	}
}

void MbD::MarkerFrameqc::preStatic()
{
	assert(false);
}

size_t MarkerFrameqc::iqX() const
{
	auto prtFrmPtr = static_cast<PartFrame*>(partFrame);
	return prtFrmPtr->iqX;
}

FColDsptr MbD::MarkerFrameqc::omeOmO() const
{
	return partFrame->omeOpO();
}

FMatDsptr MbD::MarkerFrameqc::pAdotjOmpE(size_t jj)
{
	auto pAdotOppE = partFrame->pAdotOppE();
	auto aAjjpm = aApm->column(jj);
	auto answer = FullMatrix<double>::With(3, 4);
	for (size_t j = 0; j < 4; j++) {
		auto pAdotOppEj = pAdotOppE->at(j);
		auto pAdotjjpmpEj = pAdotOppEj->timesFullColumn(aAjjpm);
		answer->atandputFullColumn(0, j, pAdotjjpmpEj);
	}
	return answer;
}

FMatDsptr MbD::MarkerFrameqc::pAdotjOmpET(size_t jj)
{
	auto pAdotOppE = partFrame->pAdotOppE();
	auto aAjjpm = aApm->column(jj);
	auto answer = FullMatrix<double>::With(4, 3);
	for (size_t i = 0; i < 4; i++) {
		auto answeri = answer->at(i);
		auto pAdotOppEi = pAdotOppE->at(i);
		auto pAdotjjpmpEi = pAdotOppEi->timesFullColumn(aAjjpm);
		for (size_t j = 0; j < 3; j++) {
			answeri->atput(j, (pAdotjjpmpEi->at(j)));
		}
	}
	return answer;
}

size_t MarkerFrameqc::iqE() const
{
	auto prtFrmPtr = static_cast<PartFrame*>(partFrame);
	return prtFrmPtr->iqE;
}

void MarkerFrameqc::fillqsu(FColDsptr col)
{
	endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->fillqsu(col); });
}

void MarkerFrameqc::fillqsuWeights(DiagMatDsptr diagMat)
{
	endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->fillqsuWeights(diagMat); });
}

void MbD::MarkerFrameqc::fillqsuddotlam(FColDsptr col)
{
	endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->fillqsuddotlam(col); });
}

void MarkerFrameqc::fillqsulam(FColDsptr col)
{
	endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->fillqsulam(col); });
}

void MbD::MarkerFrameqc::fillpqsumu(FColDsptr col)
{
	endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->fillpqsumu(col); });
}

void MbD::MarkerFrameqc::fillpqsumudot(FColDsptr col)
{
	endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->fillpqsumudot(col); });
}

void MarkerFrameqc::fillqsudot(FColDsptr col)
{
	endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->fillqsudot(col); });
}

void MbD::MarkerFrameqc::fillqsudotPlam(FColDsptr col)
{
	assert(false);
}

void MbD::MarkerFrameqc::fillqsudotPlamDeriv(FColDsptr col)
{
	assert(false);
}

void MarkerFrameqc::fillqsudotWeights(DiagMatDsptr diagMat)
{
	endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->fillqsudotWeights(diagMat); });
}

void MarkerFrameqc::setqsu(FColDsptr col)
{
	endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->setqsu(col); });
}

void MarkerFrameqc::setqsulam(FColDsptr col)
{
	endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->setqsulam(col); });
}

void MbD::MarkerFrameqc::simUpdateAll()
{
	CartesianFrame::simUpdateAll();
	endFramesDo([](EndFrmsptr endFrame) { endFrame->simUpdateAll(); });
}

void MarkerFrameqc::setqsudot(FColDsptr col)
{
	endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->setqsudot(col); });
}

void MarkerFrameqc::setqsudotlam(FColDsptr col)
{
	endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->setqsudotlam(col); });
}

void MbD::MarkerFrameqc::setqsudotPlam(FColDsptr col)
{
	assert(false);
}

void MbD::MarkerFrameqc::setqsudotPlamDeriv(FColDsptr col)
{
	assert(false);
}

void MarkerFrameqc::postPosICIteration()
{
	CartesianFrame::postPosICIteration();
	endFramesDo([](EndFrmsptr endFrame) { endFrame->postPosICIteration(); });
}

void MbD::MarkerFrameqc::postStaticIteration()
{
	assert(false);
}

void MarkerFrameqc::postPosIC()
{
	endFramesDo([](EndFrmsptr endFrame) { endFrame->postPosIC(); });
}

void MarkerFrameqc::preDyn()
{
	endFramesDo([](EndFrmsptr endFrame) { endFrame->preDyn(); });
}

void MarkerFrameqc::storeDynState()
{
	endFramesDo([](EndFrmsptr endFrame) { endFrame->storeDynState(); });
}

void MarkerFrameqc::preVelIC()
{
	CartesianFrame::preVelIC();
	endFramesDo([](EndFrmsptr endFrame) { endFrame->preVelIC(); });
}

void MarkerFrameqc::postVelIC()
{
	endFramesDo([](EndFrmsptr endFrame) { endFrame->postVelIC(); });
}

void MarkerFrameqc::preAccIC()
{
	CartesianFrame::preAccIC();
	endFramesDo([](EndFrmsptr endFrame) { endFrame->preAccIC(); });
}

void MbD::MarkerFrameqc::preDynOutput()
{
	CartesianFrame::preDynOutput();
	endFramesDo([](EndFrmsptr endFrame) { endFrame->preDynOutput(); });
}

FColDsptr MarkerFrameqc::qXdot() const
{
	auto prtFrmPtr = static_cast<PartFrame*>(partFrame);
	return prtFrmPtr->qXdot;
}

FColDsptr MbD::MarkerFrameqc::rmemOFrOeO(FColDsptr rOeOCol) const
{
	return aAOm->transposeTimesFullColumn(rOeOCol->minusFullColumn(rOmO));
}

FColDsptr MbD::MarkerFrameqc::rOeOOFrmem(FColDsptr rmemCol) const
{
	return rOmO->plusFullColumn(aAOm->timesFullColumn(rmemCol));
}

std::shared_ptr<EulerParametersDot<double>> MarkerFrameqc::qEdot() const
{
	auto prtFrmPtr = static_cast<PartFrame*>(partFrame);
	return prtFrmPtr->qEdot;
}

FColDsptr MbD::MarkerFrameqc::qX() const
{
	auto prtFrmPtr = static_cast<PartFrame*>(partFrame);
	return prtFrmPtr->qX;
}

FColDsptr MarkerFrameqc::qXddot() const
{
	auto prtFrmPtr = static_cast<PartFrame*>(partFrame);
	return prtFrmPtr->qXddot;
}

FColDsptr MarkerFrameqc::qEddot() const
{
	auto prtFrmPtr = static_cast<PartFrame*>(partFrame);
	return prtFrmPtr->qEddot;
}

void MarkerFrameqc::setqsuddotlam(FColDsptr col)
{
	endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->setqsuddotlam(col); });
}

FColFMatDsptr MarkerFrameqc::pAOppE()
{
	return partFrame->pAOppE();
}

FMatDsptr MarkerFrameqc::aBOp()
{
	return partFrame->aBOp();
}

void MarkerFrameqc::postDynStep()
{
	endFramesDo([](EndFrmsptr endFrame) { endFrame->postDynStep(); });
}

void MbD::MarkerFrameqc::setpqsumu(FColDsptr col)
{
	endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->setpqsumu(col); });
}

void MbD::MarkerFrameqc::setpqsumudot(FColDsptr col)
{
	endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->setpqsumudot(col); });
}

void MbD::MarkerFrameqc::setpqsumuddot(FColDsptr col)
{
	endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->setpqsumuddot(col); });
}

void MbD::MarkerFrameqc::postDynPredictor()
{
	CartesianFrame::postDynPredictor();
	endFramesDo([](EndFrmsptr endFrame) { endFrame->postDynPredictor(); });
}

void MbD::MarkerFrameqc::postDynOutput()
{
	CartesianFrame::postDynOutput();
	endFramesDo([](EndFrmsptr endFrame) { endFrame->postDynOutput(); });
}

void MbD::MarkerFrameqc::postDynCorrectorIteration()
{
	CartesianFrame::postDynCorrectorIteration();
	endFramesDo([](EndFrmsptr endFrame) { endFrame->postDynCorrectorIteration(); });
}

FMatDsptr MbD::MarkerFrameqc::pvOmOpE()
{
	auto answer = FullMatrix<double>::With(3, 4);
	auto pAdotOppE = partFrame->pAdotOppE();
	for (size_t i = 0; i < 3; i++) {
		auto answeri = answer->at(i);
		for (size_t j = 0; j < 4; j++) {
			auto pAdotOpipEj = pAdotOppE->at(j)->at(i);
			answeri->atput(j, pAdotOpipEj->dot(rpmp));
		}
	}
	return answer;
}

FColDsptr MbD::MarkerFrameqc::vOmO() const
{
	return partFrame->vOpO()->plusFullColumn(partFrame->aAdotOp()->timesFullColumn(rpmp));
}

FColDsptr MbD::MarkerFrameqc::vOeO_of_rmem() const
{
	assert(false);
	return FColDsptr();
}

FColDsptr MbD::MarkerFrameqc::aOmO() const
{
	return partFrame->aOpO()->plusFullColumn(partFrame->aAddotOp()->timesFullColumn(rpmp));
}

void MarkerFrameqc::setPartFrame(SpatialContainerFrame* partFrm)
{
	partFrame = partFrm;
}

FMatDsptr MbD::MarkerFrameqc::pomeOmOpE()
{
	return partFrame->pomeOpOpE();
}

FMatDsptr MbD::MarkerFrameqc::pomeOmOpEdot()
{
	return partFrame->pomeOpOpEdot();
}

SpatialContainerFrame* MarkerFrameqc::getPartFrame() const {
	return partFrame;
}

void MarkerFrameqc::setrpmp(FColDsptr x) const
{
	rpmp->copyFrom(x);
}

FColDsptr MbD::MarkerFrameqc::aAdotjOm(size_t j)
{
	return partFrame->aAdotOp()->timesFullColumn(aApm->column(j));
}

void MarkerFrameqc::setaApm(FMatDsptr mat) const
{
	aApm->copyFrom(mat);
}

void MarkerFrameqc::addEndFrame(EndFrmsptr endFrm)
{
	endFrm->setMarkerFrame(this);
	endFrames->push_back(endFrm);
}
