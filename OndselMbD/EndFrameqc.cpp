/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <memory>

#include "EndFrameqc.h"
#include "EndFrameqct.h"
#include "Variable.h"
#include "MarkerFrameqc.h"
#include "EndFrameqct2.h"
#include "EndFrameqccq.h"

using namespace MbD;

std::shared_ptr<EndFrameqc> MbD::EndFrameqc::With()
{
	auto inst = std::make_shared<EndFrameqc>();
	inst->initialize();
	return inst;
}

std::shared_ptr<EndFrameqc> MbD::EndFrameqc::With(const char* str)
{
	auto inst = std::make_shared<EndFrameqc>(str);
	inst->initialize();
	return inst;
}

void EndFrameqc::initialize()
{
	prOeOpE = FullMatrix<double>::With(3, 4);
	pprOeOpEpE = std::make_shared<FullMatrix<FColDsptr>>(4, 4);
	pAOepE = std::make_shared<FullColumn<FMatDsptr>>(4);
	ppAOepEpE = std::make_shared<FullMatrix<FMatDsptr>>(4, 4);
}

void EndFrameqc::initializeGlobally()
{
	//rOeO = rOmO + aAOm*rmem
	//aAOe = aAOm*aAme;
	auto mkrFrmqc = static_cast<MarkerFrameqc*>(markerFrame);
	for (size_t i = 0; i < 4; i++) {
		for (size_t j = 0; j < 4; j++) {
			auto& pprOmOpEipEj = mkrFrmqc->pprOmOpEpE->at(i)->at(j);
			auto& ppAOmpEipEj = mkrFrmqc->ppAOmpEpE->at(i)->at(j);
			pprOeOpEpE->atandput(i, j, pprOmOpEipEj->plusFullColumn(ppAOmpEipEj->timesFullColumn(rmem)));
			ppAOepEpE->atandput(i, j, ppAOmpEipEj->timesFullMatrix(aAme));
		}
	}
}

void EndFrameqc::initEndFrameqct()
{
	endFrameqct = EndFrameqct::With(name.data());
	endFrameqct->prOeOpE = prOeOpE;
	endFrameqct->pprOeOpEpE = pprOeOpEpE;
	endFrameqct->pAOepE = pAOepE;
	endFrameqct->ppAOepEpE = ppAOepEpE;
	endFrameqct->setMarkerFrame(markerFrame);
}

void MbD::EndFrameqc::initEndFrameqct2()
{
	endFrameqct = EndFrameqct2::With(name.data());
	endFrameqct->prOeOpE = prOeOpE;
	endFrameqct->pprOeOpEpE = pprOeOpEpE;
	endFrameqct->pAOepE = pAOepE;
	endFrameqct->ppAOepEpE = ppAOepEpE;
	endFrameqct->setMarkerFrame(markerFrame);
}

FMatFColDsptr EndFrameqc::ppAjOepEpE(size_t jj) const
{
	auto answer = std::make_shared<FullMatrix<FColDsptr>>(4, 4);
	for (size_t i = 0; i < 4; i++) {
		auto& answeri = answer->at(i);
		auto& ppAOepEipE = ppAOepEpE->at(i);
		for (size_t j = i; j < 4; j++) {
			answeri->at(j) = ppAOepEipE->at(j)->column(jj);
		}
	}
	answer->symLowerWithUpper();
	return answer;
}

void EndFrameqc::calcPostDynCorrectorIteration()
{
	EndFramec::calcPostDynCorrectorIteration();
	auto mkrFrmqc = static_cast<MarkerFrameqc*>(markerFrame);
	//rOeO = rOmO + aAOm*rmem
	//aAOe = aAOm*aAme;
	for (size_t i = 0; i < 4; i++) {
		auto prOmOpEi = mkrFrmqc->prOmOpE->column(i);
		auto& pAOmpEi = mkrFrmqc->pAOmpE->at(i);
		prOeOpE->atandputFullColumn(0, i, prOmOpEi->plusFullColumn(pAOmpEi->timesFullColumn(rmem)));
		pAOepE->atput(i, pAOmpEi->timesFullMatrix(aAme));
	}
}

FMatDsptr MbD::EndFrameqc::pAjOepE(size_t jj) const
{
	auto answer = FullMatrix<double>::With(3, 4);
	for (size_t i = 0; i < 3; i++)
	{
		auto& answeri = answer->at(i);
		for (size_t j = 0; j < 4; j++)
		{
			auto& pAOepEj = pAOepE->at(j);
			auto answerij = pAOepEj->at(i)->at(jj);
			answeri->atput(j, answerij);
		}
	}
	return answer;
}

FMatDsptr EndFrameqc::pAjOepET(size_t axis) const
{
	auto answer = FullMatrix<double>::With(4, 3);
	for (size_t i = 0; i < 4; i++) {
		auto& answeri = answer->at(i);
		auto& pAOepEi = pAOepE->at(i);
		for (size_t j = 0; j < 3; j++) {
			auto& answerij = pAOepEi->at(j)->at(axis);
			answeri->at(j) = answerij;
		}
	}
	return answer;
}

FMatDsptr EndFrameqc::ppriOeOpEpE(size_t ii) const
{
	auto answer = FullMatrix<double>::With(4, 4);
	for (size_t i = 0; i < 4; i++) {
		auto& answeri = answer->at(i);
		auto& pprOeOpEipE = pprOeOpEpE->at(i);
		for (size_t j = 0; j < 4; j++) {
			auto& answerij = pprOeOpEipE->at(j)->at(ii);
			answeri->at(j) = answerij;
		}
	}
	return answer;
}

size_t EndFrameqc::iqX()
{
	return static_cast<MarkerFrameqc*>(markerFrame)->iqX();
}

size_t EndFrameqc::iqE()
{
	return static_cast<MarkerFrameqc*>(markerFrame)->iqE();
}

FRowDsptr EndFrameqc::priOeOpE(size_t i) const
{
	return prOeOpE->at(i);
}

FColDsptr EndFrameqc::qXdot()
{
	return static_cast<MarkerFrameqc*>(markerFrame)->qXdot();
}

std::shared_ptr<EulerParametersDot<double>> EndFrameqc::qEdot()
{
	return static_cast<MarkerFrameqc*>(markerFrame)->qEdot();
}

FColDsptr EndFrameqc::qXddot()
{
	return static_cast<MarkerFrameqc*>(markerFrame)->qXddot();
}

FColDsptr EndFrameqc::qEddot()
{
	return static_cast<MarkerFrameqc*>(markerFrame)->qEddot();
}

FColDsptr EndFrameqc::rpep()
{
	auto mkrFrmqc = static_cast<MarkerFrameqc*>(markerFrame);
	auto& rpmp = mkrFrmqc->rpmp;
	auto& aApm = mkrFrmqc->aApm;
	auto rpep = rpmp->plusFullColumn(aApm->timesFullColumn(rmem));
	return rpep;
}

FColFMatDsptr EndFrameqc::pAOppE()
{
	return static_cast<MarkerFrameqc*>(markerFrame)->pAOppE();
}

FMatDsptr EndFrameqc::aBOp()
{
	return static_cast<MarkerFrameqc*>(markerFrame)->aBOp();
}

bool MbD::EndFrameqc::isEndFrameqc()
{
	return true;
}

FMatDsptr MbD::EndFrameqc::pvOeOpE()
{
	return static_cast<MarkerFrameqc*>(markerFrame)->pvOmOpE();
}

FColDsptr MbD::EndFrameqc::omeOeO()
{
	return static_cast<MarkerFrameqc*>(markerFrame)->omeOmO();
}

FMatDsptr MbD::EndFrameqc::pomeOeOpE()
{
	return static_cast<MarkerFrameqc*>(markerFrame)->pomeOmOpE();
}

FMatDsptr MbD::EndFrameqc::pomeOeOpEdot()
{
	return static_cast<MarkerFrameqc*>(markerFrame)->pomeOmOpEdot();
}

std::shared_ptr<EndFrameqc> MbD::EndFrameqc::followEndFrame(EndFrmsptr frmi)
{
	auto endFrm = EndFrameqccq::With();
	endFrm->name = name;
	static_cast<MarkerFrameqc*>(markerFrame)->addEndFrame(endFrm);
	endFrm->targetFrame = frmi;
	return endFrm;
}

