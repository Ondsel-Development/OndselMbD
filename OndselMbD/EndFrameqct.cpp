/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <memory>

#include "EndFrameqct.h"
#include "Variable.h"
#include "MarkerFrameqc.h"
#include "EndFrameqct2.h"
#include "EndFrameqccq.h"
#include "EndFrameqct.h"
#include "MarkerFrameqc.h"
#include "System.h"
#include "Symbolic.h"
#include "Time.h"
#include "EulerParameters.h"
#include "EulerAngleszxz.h"
#include "EulerAngleszxzDot.h"
#include "EulerAngleszxzDDot.h"

using namespace MbD;

std::shared_ptr<EndFrameqct> MbD::EndFrameqct::With()
{
	auto inst = std::make_shared<EndFrameqct>();
	inst->initialize();
	return inst;
}

std::shared_ptr<EndFrameqct> MbD::EndFrameqct::With(const char* str)
{
	auto inst = std::make_shared<EndFrameqct>(str);
	inst->initialize();
	return inst;
}

void EndFrameqct::initialize()
{
	EndFramect::initialize();
	pprOeOpEpt = FullMatrix<double>::With(3, 4);
	ppAOepEpt = std::make_shared<FullColumn<FMatDsptr>>(4);
	prOeOpE = FullMatrix<double>::With(3, 4);
	pprOeOpEpE = std::make_shared<FullMatrix<FColDsptr>>(4, 4);
	pAOepE = std::make_shared<FullColumn<FMatDsptr>>(4);
	ppAOepEpE = std::make_shared<FullMatrix<FMatDsptr>>(4, 4);
}

void EndFrameqct::initializeGlobally()
{
	EndFramect::initializeGlobally();
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

FMatFColDsptr EndFrameqct::ppAjOepEpE(size_t jj) const
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

FMatDsptr MbD::EndFrameqct::pAjOepE(size_t jj) const
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

FMatDsptr EndFrameqct::pAjOepET(size_t axis) const
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

FMatDsptr EndFrameqct::ppriOeOpEpE(size_t ii) const
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

size_t EndFrameqct::iqX()
{
	return markerFrame->iqX();
}

size_t EndFrameqct::iqE()
{
	return markerFrame->iqE();
}

FRowDsptr EndFrameqct::priOeOpE(size_t i) const
{
	return prOeOpE->at(i);
}

FColDsptr EndFrameqct::qXdot()
{
	auto mkrFrmqc = static_cast<MarkerFrameqc*>(markerFrame);
	return mkrFrmqc->qXdot();
}

std::shared_ptr<EulerParametersDot<double>> EndFrameqct::qEdot()
{
	auto mkrFrmqc = static_cast<MarkerFrameqc*>(markerFrame);
	return mkrFrmqc->qEdot();
}

FColDsptr EndFrameqct::qXddot()
{
	auto mkrFrmqc = static_cast<MarkerFrameqc*>(markerFrame);
	return mkrFrmqc->qXddot();
}

FColDsptr EndFrameqct::qEddot()
{
	auto mkrFrmqc = static_cast<MarkerFrameqc*>(markerFrame);
	return mkrFrmqc->qEddot();
}

FColFMatDsptr EndFrameqct::pAOppE()
{
	auto mkrFrmqc = static_cast<MarkerFrameqc*>(markerFrame);
	return mkrFrmqc->pAOppE();
}

FMatDsptr EndFrameqct::aBOp()
{
	return markerFrame->aBOp();
}

bool MbD::EndFrameqct::isEndFrameqc()
{
	return true;
}

FMatDsptr MbD::EndFrameqct::pvOeOpE()
{
	auto mkrFrmqc = static_cast<MarkerFrameqc*>(markerFrame);
	return mkrFrmqc->pvOmOpE();
}

FColDsptr MbD::EndFrameqct::omeOeO()
{
	return markerFrame->omeOmO();
}

FMatDsptr MbD::EndFrameqct::pomeOeOpE()
{
	return markerFrame->pomeOmOpE();
}

FMatDsptr MbD::EndFrameqct::pomeOeOpEdot()
{
	return markerFrame->pomeOmOpEdot();
}

void EndFrameqct::initializeLocally()
{
	if (!rmemBlks) {
		rmem->zeroSelf();
		prmempt->zeroSelf();
		pprmemptpt->zeroSelf();
	}
	if (!phiThePsiBlks) {
		aAme->identity();
		pAmept->zeroSelf();
		ppAmeptpt->zeroSelf();
	}
}

void EndFrameqct::initprmemptBlks()
{
	auto& mbdTime = root()->time;
	prmemptBlks = std::make_shared< FullColumn<Symsptr>>(3);
	for (size_t i = 0; i < 3; i++) {
		auto& disp = rmemBlks->at(i);
		auto var = disp->differentiateWRT(mbdTime);
		auto vel = var->simplified(var);
		prmemptBlks->at(i) = vel;
	}
}

void EndFrameqct::initpprmemptptBlks()
{
	auto& mbdTime = root()->time;
	pprmemptptBlks = std::make_shared< FullColumn<Symsptr>>(3);
	for (size_t i = 0; i < 3; i++) {
		auto& vel = prmemptBlks->at(i);
		auto var = vel->differentiateWRT(mbdTime);
		auto acc = var->simplified(var);
		pprmemptptBlks->at(i) = acc;
	}
}

void EndFrameqct::initpPhiThePsiptBlks()
{
	auto& mbdTime = root()->time;
	pPhiThePsiptBlks = std::make_shared< FullColumn<Symsptr>>(3);
	for (size_t i = 0; i < 3; i++) {
		auto& angle = phiThePsiBlks->at(i);
		auto var = angle->differentiateWRT(mbdTime);
		//std::cout << "var " << *var << std::endl;
		auto vel = var->simplified(var);
		//std::cout << "vel " << *vel << std::endl;
		pPhiThePsiptBlks->at(i) = vel;
		//std::cout << *angle << std::endl;
		//std::cout << *vel << std::endl;
	}
}

void EndFrameqct::initppPhiThePsiptptBlks()
{
	auto& mbdTime = root()->time;
	ppPhiThePsiptptBlks = std::make_shared< FullColumn<Symsptr>>(3);
	for (size_t i = 0; i < 3; i++) {
		auto& angleVel = pPhiThePsiptBlks->at(i);
		auto var = angleVel->differentiateWRT(mbdTime);
		auto angleAcc = var->simplified(var);
		ppPhiThePsiptptBlks->at(i) = angleAcc;
		//std::cout << *angleVel << std::endl;
		//std::cout << *angleAcc << std::endl;
	}
}

void EndFrameqct::postInput()
{
	evalrmem();
	evalAme();
	Item::postInput();
}

void EndFrameqct::calcPostDynCorrectorIteration()
{
	EndFramect::calcPostDynCorrectorIteration();
	auto mkrFrmqc = static_cast<MarkerFrameqc*>(markerFrame);
	auto& rOmO = markerFrame->rOmO;
	auto& aAOm = markerFrame->aAOm;
	rOeO = rOmO->plusFullColumn(aAOm->timesFullColumn(rmem));
	auto& prOmOpE = mkrFrmqc->prOmOpE;
	auto& pAOmpE = mkrFrmqc->pAOmpE;
	for (size_t i = 0; i < 3; i++)
	{
		auto& prOmOpEi = prOmOpE->at(i);
		auto& prOeOpEi = prOeOpE->at(i);
		for (size_t j = 0; j < 4; j++)
		{
			auto prOeOpEij = prOmOpEi->at(j) + pAOmpE->at(j)->at(i)->timesFullColumn(rmem);
			prOeOpEi->at(j) = prOeOpEij;
		}
	}
	auto rpep = markerFrame->rpmp->plusFullColumn(markerFrame->aApm->timesFullColumn(rmem));
	pprOeOpEpE = EulerParameters<double>::ppApEpEtimesColumn(rpep);
	aAOe = aAOm->timesFullMatrix(aAme);
	for (size_t i = 0; i < 4; i++)
	{
		pAOepE->at(i) = pAOmpE->at(i)->timesFullMatrix(aAme);
	}
	auto aApe = markerFrame->aApm->timesFullMatrix(aAme);
	ppAOepEpE = EulerParameters<double>::ppApEpEtimesMatrix(aApe);
}

FRowDsptr EndFrameqct::ppriOeOpEpt(size_t i) const
{
	return pprOeOpEpt->at(i);
}

FColDsptr EndFrameqct::rpep()
{
	auto& rpmp = markerFrame->rpmp;
	auto& aApm = markerFrame->aApm;
	auto rpep = rpmp->plusFullColumn(aApm->timesFullColumn(rmem));
	return rpep;
}

FMatDsptr MbD::EndFrameqct::ppAjOepETpt(size_t jj) const
{
	auto answer = FullMatrix<double>::With(4, 3);
	for (size_t i = 0; i < 4; i++)
	{
		auto& answeri = answer->at(i);
		auto& ppAOepEipt = ppAOepEpt->at(i);
		for (size_t j = 0; j < 3; j++)
		{
			auto& answerij = ppAOepEipt->at(j)->at(jj);
			answeri->atput(j, answerij);
		}
	}
	return answer;
}