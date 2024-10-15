/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include<algorithm>

#include "AssemblyFrame.h"
#include "Part.h"
#include "EulerConstraint.h"
#include "AbsConstraint.h"
#include "MarkerFrame.h"
#include "EulerParameters.h"
#include "EulerParametersDot.h"
#include "RedundantConstraint.h"
#include "System.h"

using namespace MbD;

AssemblyFrame::AssemblyFrame(const char* str) : SpatialContainerFrame(str)
{
	assert(false);
}

std::shared_ptr<AssemblyFrame> MbD::AssemblyFrame::With()
{
	auto inst = std::make_shared<AssemblyFrame>();
	inst->initialize();
	return inst;
}

std::shared_ptr<AssemblyFrame> MbD::AssemblyFrame::With(const char* str)
{
	auto inst = std::make_shared<AssemblyFrame>(str);
	inst->initialize();
	return inst;
}

System* AssemblyFrame::root()
{
	return assembly->root();
}

void AssemblyFrame::initializeLocally()
{
	markerFramesDo([](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->initializeLocally(); });
}

void AssemblyFrame::initializeGlobally()
{
	markerFramesDo([](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->initializeGlobally(); });
}

void AssemblyFrame::setAssembly(System* x) {
	assembly = x;
}

System* AssemblyFrame::getAssembly() {
	return assembly;
}

void MbD::AssemblyFrame::setPart(Part* x)
{
}

void AssemblyFrame::fillqsu(FColDsptr col)
{
	markerFramesDo([&](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->fillqsu(col); });
}

void AssemblyFrame::fillqsuWeights(DiagMatDsptr diagMat)
{
	markerFramesDo([&](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->fillqsuWeights(diagMat); });
}

void MbD::AssemblyFrame::fillqsuddotlam(FColDsptr col)
{
	markerFramesDo([&](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->fillqsuddotlam(col); });
}

void AssemblyFrame::fillqsulam(FColDsptr col)
{
	markerFramesDo([&](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->fillqsulam(col); });
}

void MbD::AssemblyFrame::fillpqsumu(FColDsptr col)
{
	//"Fill q, s and lam into col."
	markerFramesDo([&](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->fillpqsumu(col); });
}

void MbD::AssemblyFrame::fillpqsumudot(FColDsptr col)
{
	markerFramesDo([&](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->fillpqsumudot(col); });
}

void AssemblyFrame::fillqsudot(FColDsptr col)
{
	markerFramesDo([&](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->fillqsudot(col); });
}

void AssemblyFrame::fillqsudotWeights(DiagMatDsptr diagMat)
{
	markerFramesDo([&](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->fillqsudotWeights(diagMat); });
}

void AssemblyFrame::useEquationNumbers()
{
	markerFramesDo([](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->useEquationNumbers(); });
}

void AssemblyFrame::setqsu(FColDsptr col)
{
	markerFramesDo([&](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->setqsu(col); });
}

void AssemblyFrame::setqsulam(FColDsptr col)
{
	markerFramesDo([&](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->setqsulam(col); });
}

void AssemblyFrame::setqsudotlam(FColDsptr col)
{
	markerFramesDo([&](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->setqsudotlam(col); });
}

void AssemblyFrame::setqsudot(FColDsptr col)
{
	markerFramesDo([&](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->setqsudot(col); });
}

void AssemblyFrame::postPosICIteration()
{
	CartesianFrame::postPosICIteration();
	markerFramesDo([](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->postPosICIteration(); });
}

void AssemblyFrame::fillPosICError(FColDsptr col)
{
	markerFramesDo([&](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->fillPosICError(col); });
}

void AssemblyFrame::fillPosICJacob(SpMatDsptr mat)
{
	markerFramesDo([&](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->fillPosICJacob(mat); });
}

void AssemblyFrame::postPosIC()
{
	markerFramesDo([](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->postPosIC(); });
}

void AssemblyFrame::preDyn()
{
	markerFramesDo([](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->preDyn(); });
}

void AssemblyFrame::storeDynState()
{
	markerFramesDo([](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->storeDynState(); });
}

void AssemblyFrame::fillPosKineError(FColDsptr col)
{
	markerFramesDo([&](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->fillPosKineError(col); });
}

void AssemblyFrame::preVelIC()
{
	CartesianFrame::preVelIC();
	markerFramesDo([](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->preVelIC(); });
}

void AssemblyFrame::postVelIC()
{
	markerFramesDo([](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->postVelIC(); });
}

void AssemblyFrame::fillVelICError(FColDsptr col)
{
	markerFramesDo([&](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->fillVelICError(col); });
}

void AssemblyFrame::fillVelICJacob(SpMatDsptr mat)
{
	markerFramesDo([&](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->fillVelICJacob(mat); });
}

void AssemblyFrame::preAccIC()
{
	CartesianFrame::preAccIC();
	markerFramesDo([](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->preAccIC(); });
}

void AssemblyFrame::fillAccICIterError(FColDsptr col)
{
	markerFramesDo([&](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->fillAccICIterError(col); });
}

void AssemblyFrame::fillAccICIterJacob(SpMatDsptr mat)
{
	markerFramesDo([&](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->fillAccICIterJacob(mat); });
}

void AssemblyFrame::setqsuddotlam(FColDsptr col)
{
	markerFramesDo([&](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->setqsuddotlam(col); });
}

void AssemblyFrame::fillPosKineJacob(SpMatDsptr mat)
{
	markerFramesDo([&](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->fillPosKineJacob(mat); });
}

double MbD::AssemblyFrame::suggestSmallerOrAcceptDynStepSize(double hnew)
{
	//"Default is return hnew."
	return hnew;
}

void AssemblyFrame::postDynStep()
{
	markerFramesDo([](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->postDynStep(); });
}

void MbD::AssemblyFrame::setpqsumu(FColDsptr col)
{
	markerFramesDo([&](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->setpqsumu(col); });
}

void MbD::AssemblyFrame::setpqsumudot(FColDsptr col)
{
	markerFramesDo([&](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->setpqsumudot(col); });
}

void MbD::AssemblyFrame::setpqsumuddot(FColDsptr col)
{
	markerFramesDo([&](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->setpqsumuddot(col); });
}

void MbD::AssemblyFrame::postDynPredictor()
{
	CartesianFrame::postDynPredictor();
	markerFramesDo([](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->postDynPredictor(); });
}

void MbD::AssemblyFrame::fillDynError(FColDsptr col)
{
	markerFramesDo([&](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->fillDynError(col); });
}

void MbD::AssemblyFrame::fillpFpy(SpMatDsptr mat)
{
}

void MbD::AssemblyFrame::fillpFpydot(SpMatDsptr mat)
{
}

void MbD::AssemblyFrame::postDynCorrectorIteration()
{
	CartesianFrame::postDynCorrectorIteration();
	markerFramesDo([](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->postDynCorrectorIteration(); });
}

void MbD::AssemblyFrame::preDynOutput()
{
	CartesianFrame::preDynOutput();
	markerFramesDo([](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->preDynOutput(); });
}

void MbD::AssemblyFrame::postDynOutput()
{
	CartesianFrame::postDynOutput();
	markerFramesDo([](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->postDynOutput(); });
}

void AssemblyFrame::postInput()
{
	CartesianFrame::postInput();
	markerFramesDo([](std::shared_ptr<MarkerFrame> markerFrame) { markerFrame->postInput(); });
}

void MbD::AssemblyFrame::calcPostDynCorrectorIteration()
{
	//Do nothing.
}
