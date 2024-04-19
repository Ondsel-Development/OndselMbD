/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include <assert.h>
#include <memory>

#include "EndFramec.h"
#include "PartFrame.h"
#include "MarkerFrame.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<EndFramec> MbD::EndFramec::With(const char* str)
{
	auto inst = std::make_shared<EndFramec>(str);
	inst->initialize();
	return inst;
}

void EndFramec::initialize()
{
	assert(false);
}

FMatDsptr MbD::EndFramec::aAeO() const
{
	return aAOe->transpose();
}

System* EndFramec::root()
{
	return markerFrame->root();
}

void EndFramec::setMarkerFrame(MarkerFrame* markerFrm)
{
	markerFrame = markerFrm;
}

MarkerFrame* EndFramec::getMarkerFrame() const
{
	return markerFrame;
}

void EndFramec::initEndFrameqct()
{
	assert(false);
}

void MbD::EndFramec::initEndFrameqct2()
{
	assert(false);
}

void EndFramec::calcPostDynCorrectorIteration()
{
	rOeO = markerFrame->rOmO;
	aAOe = markerFrame->aAOm;
}

void MbD::EndFramec::fillContactEndFrames(std::set<EndFramec*> efrms)
{
}

FColDsptr MbD::EndFramec::ieO()
{
	return aAOe->column(0);
}

FColDsptr MbD::EndFramec::jeO()
{
	return aAOe->column(1);
}

FColDsptr MbD::EndFramec::keO()
{
	return aAOe->column(2);
}

FColDsptr EndFramec::aAjOe(size_t j)
{
	return aAOe->column(j);
}

void MbD::EndFramec::aApm(FMatDsptr mat)
{
	markerFrame->aApm = mat;
}

double EndFramec::riOeO(size_t i)
{
	return rOeO->at(i);
}

FColDsptr EndFramec::rmeO()
{
	return rOeO->minusFullColumn(markerFrame->rOmO);
}

FColDsptr EndFramec::rpep()
{
	return FColDsptr();
}

FColFMatDsptr EndFramec::pAOppE()
{
	return FColFMatDsptr();
}

FMatDsptr EndFramec::aBOp()
{
	return FMatDsptr();
}

std::shared_ptr<EndFrameqc> MbD::EndFramec::newCopyEndFrameqc()
{
	auto frmIeqc = EndFrameqc::With();
	markerFrame->addEndFrame(frmIeqc);
	return frmIeqc;
}

bool MbD::EndFramec::isEndFrameqc()
{
	return false;
}

PartFrame* MbD::EndFramec::getPartFrame()
{
	return markerFrame->getPartFrame();
}

std::shared_ptr<EulerParameters<double>> MbD::EndFramec::qEOe()
{
	return aAOe->asEulerParameters();
}

FColDsptr MbD::EndFramec::vOeO()
{
	return markerFrame->vOmO();
}

FColDsptr MbD::EndFramec::aOeO()
{
	return markerFrame->aOmO();
}
