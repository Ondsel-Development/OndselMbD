/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include<algorithm>

#include "SpatialContainerFrame.h"
#include "Part.h"
#include "EulerConstraint.h"
#include "AbsConstraint.h"
#include "MarkerFrame.h"
#include "EulerParameters.h"
#include "EulerParametersDot.h"
#include "RedundantConstraint.h"
#include "System.h"

using namespace MbD;

SpatialContainerFrame::SpatialContainerFrame(const char* str) : CartesianFrame(str)
{
	assert(false);
}

std::shared_ptr<SpatialContainerFrame> MbD::SpatialContainerFrame::With()
{
	auto inst = std::make_shared<SpatialContainerFrame>();
	inst->initialize();
	return inst;
}

std::shared_ptr<SpatialContainerFrame> MbD::SpatialContainerFrame::With(const char* str)
{
	auto inst = std::make_shared<SpatialContainerFrame>(str);
	inst->initialize();
	return inst;
}

void SpatialContainerFrame::initialize()
{
	markerFrames = std::make_shared<std::vector<std::shared_ptr<MarkerFrame>>>();
}

void SpatialContainerFrame::initializeLocally()
{
	markerFramesDo([](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->initializeLocally(); });
}

void SpatialContainerFrame::initializeGlobally()
{
	markerFramesDo([](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->initializeGlobally(); });
}

void SpatialContainerFrame::addMarkerFrame(std::shared_ptr<MarkerFrame> markerFrame)
{
	markerFrame->setPartFrame(this);
	markerFrames->push_back(markerFrame);
}

EndFrmsptr SpatialContainerFrame::endFrame(std::string name)
{
	auto match = std::find_if(markerFrames->begin(), markerFrames->end(), [&](auto& mkr) {return mkr->name == name; });
	return (*match)->endFrames->at(0);
}

void SpatialContainerFrame::markerFramesDo(const std::function<void(std::shared_ptr<MarkerFrame>)>& f) const
{
	std::for_each(markerFrames->begin(), markerFrames->end(), f);
}

void SpatialContainerFrame::prePosIC()
{
	CartesianFrame::prePosIC();
	markerFramesDo([](std::shared_ptr<MarkerFrame> markerFrm) { markerFrm->prePosIC(); });
}

void SpatialContainerFrame::prePosKine()
{
	CartesianFrame::prePosKine();
	markerFramesDo([](std::shared_ptr<MarkerFrame> markerFrm) { markerFrm->prePosKine(); });
}

void SpatialContainerFrame::fillqsuWeights(DiagMatDsptr diagMat)
{
	markerFramesDo([&](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->fillqsuWeights(diagMat); });
}

void MbD::SpatialContainerFrame::fillqsuddotlam(FColDsptr col)
{
	markerFramesDo([&](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->fillqsuddotlam(col); });
}

void SpatialContainerFrame::fillqsulam(FColDsptr col)
{
	markerFramesDo([&](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->fillqsulam(col); });
}

void MbD::SpatialContainerFrame::fillpqsumu(FColDsptr col)
{
	//"Fill q, s and lam into col."
	markerFramesDo([&](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->fillpqsumu(col); });
}

void MbD::SpatialContainerFrame::fillpqsumudot(FColDsptr col)
{
	markerFramesDo([&](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->fillpqsumudot(col); });
}

void SpatialContainerFrame::fillqsudot(FColDsptr col)
{
	markerFramesDo([&](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->fillqsudot(col); });
}

void SpatialContainerFrame::fillqsudotWeights(DiagMatDsptr diagMat)
{
	markerFramesDo([&](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->fillqsudotWeights(diagMat); });
}

void SpatialContainerFrame::useEquationNumbers()
{
	markerFramesDo([](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->useEquationNumbers(); });
}

void SpatialContainerFrame::setqsu(FColDsptr col)
{
	markerFramesDo([&](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->setqsu(col); });
}

void SpatialContainerFrame::setqsulam(FColDsptr col)
{
	markerFramesDo([&](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->setqsulam(col); });
}

void SpatialContainerFrame::setqsudotlam(FColDsptr col)
{
	markerFramesDo([&](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->setqsudotlam(col); });
}

void SpatialContainerFrame::setqsudot(FColDsptr col)
{
	markerFramesDo([&](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->setqsudot(col); });
}

void SpatialContainerFrame::postPosICIteration()
{
	CartesianFrame::postPosICIteration();
	markerFramesDo([](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->postPosICIteration(); });
}

void SpatialContainerFrame::fillPosICError(FColDsptr col)
{
	markerFramesDo([&](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->fillPosICError(col); });
}

void SpatialContainerFrame::fillPosICJacob(SpMatDsptr mat)
{
	markerFramesDo([&](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->fillPosICJacob(mat); });
}

void SpatialContainerFrame::postPosIC()
{
	markerFramesDo([](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->postPosIC(); });
}

void SpatialContainerFrame::preDyn()
{
	markerFramesDo([](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->preDyn(); });
}

void SpatialContainerFrame::storeDynState()
{
	markerFramesDo([](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->storeDynState(); });
}

void SpatialContainerFrame::fillPosKineError(FColDsptr col)
{
	markerFramesDo([&](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->fillPosKineError(col); });
}

void SpatialContainerFrame::preVelIC()
{
	CartesianFrame::preVelIC();
	markerFramesDo([](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->preVelIC(); });
}

void SpatialContainerFrame::postVelIC()
{
	markerFramesDo([](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->postVelIC(); });
}

void SpatialContainerFrame::fillVelICError(FColDsptr col)
{
	markerFramesDo([&](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->fillVelICError(col); });
}

void SpatialContainerFrame::fillVelICJacob(SpMatDsptr mat)
{
	markerFramesDo([&](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->fillVelICJacob(mat); });
}

void SpatialContainerFrame::preAccIC()
{
	CartesianFrame::preAccIC();
	markerFramesDo([](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->preAccIC(); });
}

void SpatialContainerFrame::fillAccICIterError(FColDsptr col)
{
	markerFramesDo([&](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->fillAccICIterError(col); });
}

void SpatialContainerFrame::fillAccICIterJacob(SpMatDsptr mat)
{
	markerFramesDo([&](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->fillAccICIterJacob(mat); });
}

void SpatialContainerFrame::setqsuddotlam(FColDsptr col)
{
	markerFramesDo([&](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->setqsuddotlam(col); });
}

void SpatialContainerFrame::fillPosKineJacob(SpMatDsptr mat)
{
	markerFramesDo([&](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->fillPosKineJacob(mat); });
}

void SpatialContainerFrame::postDynStep()
{
	markerFramesDo([](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->postDynStep(); });
}

void MbD::SpatialContainerFrame::setpqsumu(FColDsptr col)
{
	markerFramesDo([&](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->setpqsumu(col); });
}

void MbD::SpatialContainerFrame::setpqsumudot(FColDsptr col)
{
	markerFramesDo([&](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->setpqsumudot(col); });
}

void MbD::SpatialContainerFrame::setpqsumuddot(FColDsptr col)
{
	markerFramesDo([&](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->setpqsumuddot(col); });
}

void MbD::SpatialContainerFrame::postDynPredictor()
{
	CartesianFrame::postDynPredictor();
	markerFramesDo([](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->postDynPredictor(); });
}

void MbD::SpatialContainerFrame::fillDynError(FColDsptr col)
{
	markerFramesDo([&](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->fillDynError(col); });
}

void MbD::SpatialContainerFrame::fillpFpy(SpMatDsptr mat)
{
	//markerFramesDo([&](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->fillpFpy(mat); });
}

void MbD::SpatialContainerFrame::fillpFpydot(SpMatDsptr mat)
{
	//markerFramesDo([&](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->fillpFpydot(mat); });
}

void MbD::SpatialContainerFrame::postDynCorrectorIteration()
{
	CartesianFrame::postDynCorrectorIteration();
	markerFramesDo([](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->postDynCorrectorIteration(); });
}

void MbD::SpatialContainerFrame::preDynOutput()
{
	CartesianFrame::preDynOutput();
	markerFramesDo([](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->preDynOutput(); });
}

void MbD::SpatialContainerFrame::postDynOutput()
{
	CartesianFrame::postDynOutput();
	markerFramesDo([](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->postDynOutput(); });
}

size_t MbD::SpatialContainerFrame::iqX()
{
	return size_t();
}

size_t MbD::SpatialContainerFrame::iqE()
{
	assert(false);
	return size_t();
}

FColDsptr MbD::SpatialContainerFrame::qX()
{
	return FColDsptr();
}

std::shared_ptr<EulerParameters<double>> MbD::SpatialContainerFrame::qE()
{
	return std::shared_ptr<EulerParameters<double>>();
}

FColDsptr MbD::SpatialContainerFrame::qXdot()
{
	return FColDsptr();
}

std::shared_ptr<EulerParametersDot<double>> MbD::SpatialContainerFrame::qEdot()
{
	return std::shared_ptr<EulerParametersDot<double>>();
}

FColDsptr MbD::SpatialContainerFrame::qXddot()
{
	return FColDsptr();
}

FColDsptr MbD::SpatialContainerFrame::qEddot()
{
	return FColDsptr();
}

FMatDsptr MbD::SpatialContainerFrame::aAOp()
{
	return FMatDsptr();
}

FMatDsptr MbD::SpatialContainerFrame::aC()
{
	return FMatDsptr();
}

FMatDsptr MbD::SpatialContainerFrame::aCdot()
{
	return FMatDsptr();
}

FColDsptr MbD::SpatialContainerFrame::alpOpO()
{
	return FColDsptr();
}

FColFMatDsptr MbD::SpatialContainerFrame::pAOppE()
{
	return FColFMatDsptr();
}

FColFMatDsptr MbD::SpatialContainerFrame::pAdotOppE()
{
	return FColFMatDsptr();
}

FMatDsptr MbD::SpatialContainerFrame::pomeOpOpE()
{
	return FMatDsptr();
}

FMatDsptr MbD::SpatialContainerFrame::pomeOpOpEdot()
{
	return FMatDsptr();
}

FColDsptr MbD::SpatialContainerFrame::vOpO()
{
	return FColDsptr();
}

FMatDsptr MbD::SpatialContainerFrame::aAdotOp()
{
	return FMatDsptr();
}

FColDsptr MbD::SpatialContainerFrame::aOpO()
{
	return FColDsptr();
}

FMatDsptr MbD::SpatialContainerFrame::aAddotOp()
{
	return FMatDsptr();
}

FColDsptr MbD::SpatialContainerFrame::omeOpO()
{
	return FColDsptr();
}

void SpatialContainerFrame::postInput()
{
	CartesianFrame::postInput();
	markerFramesDo([](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->postInput(); });
}
