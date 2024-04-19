/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include<algorithm>

#include "PartFrame.h"
#include "MarkerFrame.h"
 //#include "EndFramec.h"
#include "EndFrameqct.h"
#include "EulerParameters.h"

using namespace MbD;

MarkerFrame::MarkerFrame(const char* str) : CartesianFrame(str)
{
	//Do nothing.
}

std::shared_ptr<MarkerFrame> MbD::MarkerFrame::With(const char* str)
{
	auto inst = std::make_shared<MarkerFrame>(str);
	inst->initialize();
	return inst;
}

void MarkerFrame::initialize()
{
	prOmOpE = FullMatrix<double>::With(3, 4);
	pAOmpE = std::make_shared<FullColumn<FMatDsptr>>(4);
	endFrames = std::make_shared<std::vector<EndFrmsptr>>();
	auto endFrm = EndFrameqc::With();
	this->addEndFrame(endFrm);
}

System* MarkerFrame::root()
{
	return partFrame->root();
}

void MarkerFrame::initializeLocally()
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

void MarkerFrame::prePosIC()
{
	CartesianFrame::prePosIC();
	endFramesDo([](EndFrmsptr endFrame) { endFrame->prePosIC(); });
}

void MbD::MarkerFrame::preStatic()
{
	assert(false);
}

size_t MarkerFrame::iqX() const
{
	return partFrame->iqX;
}

FColDsptr MbD::MarkerFrame::omeOmO() const
{
	return partFrame->omeOpO();
}

FMatDsptr MbD::MarkerFrame::pAdotjOmpE(size_t jj)
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

FMatDsptr MbD::MarkerFrame::pAdotjOmpET(size_t jj)
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

size_t MarkerFrame::iqE() const
{
	return partFrame->iqE;
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

FColDsptr MarkerFrame::qXdot() const
{
	return partFrame->qXdot;
}

FColDsptr MbD::MarkerFrame::rmemOFrOeO(FColDsptr rOeOCol) const
{
	return aAOm->transposeTimesFullColumn(rOeOCol->minusFullColumn(rOmO));
}

FColDsptr MbD::MarkerFrame::rOeOOFrmem(FColDsptr rmemCol) const
{
	return rOmO->plusFullColumn(aAOm->timesFullColumn(rmemCol));
}

std::shared_ptr<EulerParametersDot<double>> MarkerFrame::qEdot() const
{
	return partFrame->qEdot;
}

FColDsptr MbD::MarkerFrame::qX() const
{
	return partFrame->qX;
}

FColDsptr MarkerFrame::qXddot() const
{
	return partFrame->qXddot;
}

FColDsptr MarkerFrame::qEddot() const
{
	return partFrame->qEddot;
}

void MarkerFrame::setqsuddotlam(FColDsptr col)
{
	endFramesDo([&](const EndFrmsptr& endFrame) { endFrame->setqsuddotlam(col); });
}

FColFMatDsptr MarkerFrame::pAOppE()
{
	return partFrame->pAOppE();
}

FMatDsptr MarkerFrame::aBOp()
{
	return partFrame->aBOp();
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

FMatDsptr MbD::MarkerFrame::pvOmOpE()
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

FColDsptr MbD::MarkerFrame::vOmO() const
{
	return partFrame->vOpO()->plusFullColumn(partFrame->aAdotOp()->timesFullColumn(rpmp));
}

FColDsptr MbD::MarkerFrame::vOeO_of_rmem() const
{
	assert(false);
	return FColDsptr();
}

FColDsptr MbD::MarkerFrame::aOmO() const
{
	return partFrame->aOpO()->plusFullColumn(partFrame->aAddotOp()->timesFullColumn(rpmp));
}

void MarkerFrame::setPartFrame(PartFrame* partFrm)
{
	partFrame = partFrm;
}

FMatDsptr MbD::MarkerFrame::pomeOmOpE()
{
	return partFrame->pomeOpOpE();
}

FMatDsptr MbD::MarkerFrame::pomeOmOpEdot()
{
	return partFrame->pomeOpOpEdot();
}

PartFrame* MarkerFrame::getPartFrame() const {
	return partFrame;
}

void MarkerFrame::setrpmp(FColDsptr x) const
{
	rpmp->copyFrom(x);
}

FColDsptr MbD::MarkerFrame::aAdotjOm(size_t j)
{
	return partFrame->aAdotOp()->timesFullColumn(aApm->column(j));
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
