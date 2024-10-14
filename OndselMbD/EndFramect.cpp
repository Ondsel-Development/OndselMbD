/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "EndFramect.h"
#include "MarkerFrame.h"
#include "System.h"
#include "Symbolic.h"
#include "Time.h"
#include "EulerAngleszxz.h"
#include "EulerAngleszxzDot.h"
#include "EulerAngleszxzDDot.h"

using namespace MbD;

std::shared_ptr<EndFramect> MbD::EndFramect::With(const char* str)
{
	auto inst = std::make_shared<EndFramect>(str);
	inst->initialize();
	return inst;
}

void EndFramect::initialize()
{
	EndFramec::initialize();
	rmem = std::make_shared<FullColumn<double>>(3);
	prmempt = std::make_shared<FullColumn<double>>(3);
	pprmemptpt = std::make_shared<FullColumn<double>>(3);
	aAme = FullMatrix<double>::identitysptr(3);
	pAmept = FullMatrix<double>::With(3, 3);
	ppAmeptpt = FullMatrix<double>::With(3, 3);
	pprOeOptpt = std::make_shared<FullColumn<double>>(3);
	ppAOeptpt = FullMatrix<double>::With(3, 3);
}

void EndFramect::initializeLocally()
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

void EndFramect::initializeGlobally()
{
	if (rmemBlks) {
		initprmemptBlks();
		initpprmemptptBlks();
	}
	if (phiThePsiBlks) {
		initpPhiThePsiptBlks();
		initppPhiThePsiptptBlks();
	}
}

void EndFramect::initprmemptBlks()
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

void EndFramect::initpprmemptptBlks()
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

void EndFramect::initpPhiThePsiptBlks()
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

void EndFramect::initppPhiThePsiptptBlks()
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

void EndFramect::postInput()
{
	evalrmem();
	evalAme();
	Item::postInput();
}

void EndFramect::prePosIC()
{
	time = root()->mbdTimeValue();
	evalrmem();
	evalAme();
	EndFramec::prePosIC();
}

void EndFramect::evalrmem() const
{
	if (rmemBlks) {
		for (size_t i = 0; i < 3; i++)
		{
			auto& expression = rmemBlks->at(i);
			double value = expression->getValue();
			rmem->at(i) = value;
		}
	}
}

void EndFramect::evalAme()
{
	if (phiThePsiBlks) {
		auto phiThePsi = EulerAngleszxz<double>::With();
		for (size_t i = 0; i < 3; i++)
		{
			auto& expression = phiThePsiBlks->at(i);
			auto value = expression->getValue();
			phiThePsi->at(i) = value;
		}
		phiThePsi->calc();
		aAme = phiThePsi->aA;
	}
}

void EndFramect::preVelIC()
{
	time = root()->mbdTimeValue();
	evalrmem();
	evalAme();
	Item::preVelIC();
	evalprmempt();
	evalpAmept();
	auto& aAOm = markerFrame->aAOm;
	prOeOpt = aAOm->timesFullColumn(prmempt);
	pAOept = aAOm->timesFullMatrix(pAmept);
}

FColDsptr EndFramect::pAjOept(size_t j)
{
	return pAOept->column(j);
}

FColDsptr EndFramect::ppAjOeptpt(size_t j)
{
	return ppAOeptpt->column(j);
}

double EndFramect::priOeOpt(size_t i)
{
	return prOeOpt->at(i);
}

double EndFramect::ppriOeOptpt(size_t i)
{
	return pprOeOptpt->at(i);
}

void EndFramect::evalprmempt()
{
	if (rmemBlks) {
		for (size_t i = 0; i < 3; i++)
		{
			auto& derivative = prmemptBlks->at(i);
			auto value = derivative->getValue();
			prmempt->at(i) = value;
		}
	}
}

void EndFramect::evalpAmept()
{
	if (phiThePsiBlks) {
		auto phiThePsi = EulerAngleszxz<double>::With();
		auto phiThePsiDot = EulerAngleszxzDot<double>::With();
		phiThePsiDot->phiThePsi = phiThePsi;
		for (size_t i = 0; i < 3; i++)
		{
			auto& expression = phiThePsiBlks->at(i);
			auto& derivative = pPhiThePsiptBlks->at(i);
			auto value = expression->getValue();
			auto valueDot = derivative->getValue();
			phiThePsi->at(i) = value;
			phiThePsiDot->at(i) = valueDot;
		}
		phiThePsi->calc();
		phiThePsiDot->calc();
		pAmept = phiThePsiDot->aAdot;
	}
}

void EndFramect::evalpprmemptpt()
{
	if (rmemBlks) {
		for (size_t i = 0; i < 3; i++)
		{
			auto& secondDerivative = pprmemptptBlks->at(i);
			auto value = secondDerivative->getValue();
			pprmemptpt->atput(i, value);
		}
	}
}

void EndFramect::evalppAmeptpt()
{
	if (phiThePsiBlks) {
		auto phiThePsi = EulerAngleszxz<double>::With();
		auto phiThePsiDot = EulerAngleszxzDot<double>::With();
		phiThePsiDot->phiThePsi = phiThePsi;
		auto phiThePsiDDot = EulerAngleszxzDDot<double>::With();
		phiThePsiDDot->phiThePsiDot = phiThePsiDot;
		for (size_t i = 0; i < 3; i++)
		{
			auto& expression = phiThePsiBlks->at(i);
			auto& derivative = pPhiThePsiptBlks->at(i);
			auto& secondDerivative = ppPhiThePsiptptBlks->at(i);
			auto value = expression->getValue();
			auto valueDot = derivative->getValue();
			auto valueDDot = secondDerivative->getValue();
			phiThePsi->atput(i, value);
			phiThePsiDot->atput(i, valueDot);
			phiThePsiDDot->atput(i, valueDDot);
		}
		phiThePsi->calc();
		phiThePsiDot->calc();
		phiThePsiDDot->calc();
		ppAmeptpt = phiThePsiDDot->aAddot;
	}
}

//FColDsptr EndFramect::rpep()
//{
//	return FColDsptr();
//}

void EndFramect::preAccIC()
{
	time = root()->mbdTimeValue();
	evalrmem();
	evalAme();
	Item::preVelIC();
	evalprmempt();
	evalpAmept();
	auto& aAOm = markerFrame->aAOm;
	prOeOpt = aAOm->timesFullColumn(prmempt);
	pAOept = aAOm->timesFullMatrix(pAmept);
	Item::preAccIC();
	evalpprmemptpt();
	evalppAmeptpt();
	aAOm = markerFrame->aAOm;
	pprOeOptpt = aAOm->timesFullColumn(pprmemptpt);
	ppAOeptpt = aAOm->timesFullMatrix(ppAmeptpt);
}

void MbD::EndFramect::postDynPredictor()
{
	time = root()->mbdTimeValue();
	evalrmem();
	evalAme();
	EndFramec::postDynPredictor();
}

void MbD::EndFramect::preDynOutput()
{
	time = root()->mbdTimeValue();
	evalrmem();
	evalAme();
	EndFramec::preDynOutput();
}

void MbD::EndFramect::postDynOutput()
{
	time = root()->mbdTimeValue();
	evalrmem();
	evalAme();
	EndFramec::postDynOutput();
}
