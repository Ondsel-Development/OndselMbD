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
#include "MarkerFrame.h"
#include "EndFrameqct2.h"

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
	pprOeOpEpE = markerFrame->pprOmOpEpE;
	ppAOepEpE = markerFrame->ppAOmpEpE;
}

void EndFrameqc::initEndFrameqct()
{
	endFrameqct = EndFrameqct::With(this->name.data());
	endFrameqct->prOeOpE = prOeOpE;
	endFrameqct->pprOeOpEpE = pprOeOpEpE;
	endFrameqct->pAOepE = pAOepE;
	endFrameqct->ppAOepEpE = ppAOepEpE;
	endFrameqct->setMarkerFrame(markerFrame);
}

void MbD::EndFrameqc::initEndFrameqct2()
{
	endFrameqct = EndFrameqct2::With(this->name.data());
	endFrameqct->prOeOpE = prOeOpE;
	endFrameqct->pprOeOpEpE = pprOeOpEpE;
	endFrameqct->pAOepE = pAOepE;
	endFrameqct->ppAOepEpE = ppAOepEpE;
	endFrameqct->setMarkerFrame(markerFrame);
}

FMatFColDsptr EndFrameqc::ppAjOepEpE(size_t jj)
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
	prOeOpE = markerFrame->prOmOpE;
	pAOepE = markerFrame->pAOmpE;
}

FMatDsptr EndFrameqc::pAjOepET(size_t axis)
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

FMatDsptr EndFrameqc::ppriOeOpEpE(size_t ii)
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
	return markerFrame->iqX();
}

size_t EndFrameqc::iqE()
{
	return markerFrame->iqE();
}

FRowDsptr EndFrameqc::priOeOpE(size_t i)
{
	return prOeOpE->at(i);
}

FColDsptr EndFrameqc::qXdot()
{
	return markerFrame->qXdot();
}

std::shared_ptr<EulerParametersDot<double>> EndFrameqc::qEdot()
{
	return markerFrame->qEdot();
}

FColDsptr EndFrameqc::qXddot()
{
	return markerFrame->qXddot();
}

FColDsptr EndFrameqc::qEddot()
{
	return markerFrame->qEddot();
}

FColDsptr EndFrameqc::rpep()
{
	return markerFrame->rpmp;
}

FColFMatDsptr EndFrameqc::pAOppE()
{
	return markerFrame->pAOppE();
}

FMatDsptr EndFrameqc::aBOp()
{
	return markerFrame->aBOp();
}

bool MbD::EndFrameqc::isEndFrameqc()
{
	return true;
}

FMatDsptr MbD::EndFrameqc::pvOeOpE()
{
	return markerFrame->pvOmOpE();
}
