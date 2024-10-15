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
#include "SpatialContainerFrame.h"
#include "MarkerFrame.h"
#include "EndFrameqc.h"
#include "EndFramect.h"

using namespace MbD;

std::shared_ptr<EndFramec> MbD::EndFramec::With()
{
	auto inst = std::make_shared<EndFramec>();
	inst->initialize();
	return inst;
}

std::shared_ptr<EndFramec> MbD::EndFramec::With(const char* str)
{
	auto inst = std::make_shared<EndFramec>(str);
	inst->initialize();
	return inst;
}

void EndFramec::initialize()
{
	//Do nothing.
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
	endFramect = EndFramect::With(name.data());
	endFramect->setMarkerFrame(markerFrame);
}

void MbD::EndFramec::initEndFrameqct2()
{
	assert(false);
}

void EndFramec::calcPostDynCorrectorIteration()
{
	//rOeO = rOmO + aAOm*rmem
	//aAOe = aAOm*aAme;
	rOeO = markerFrame->rOmO->plusFullColumn(markerFrame->aAOm->timesFullColumn(rmem));
	aAOe = markerFrame->aAOm->timesFullMatrix(aAme);
}

void MbD::EndFramec::fillContactEndFrames(std::set<EndFramec*> efrms)
{
}

FColDsptr MbD::EndFramec::ieO() const
{
	return aAOe->column(0);
}

FColDsptr MbD::EndFramec::jeO() const
{
	return aAOe->column(1);
}

FColDsptr MbD::EndFramec::keO() const
{
	return aAOe->column(2);
}

FColDsptr EndFramec::aAjOe(size_t j) const
{
	return aAOe->column(j);
}

void MbD::EndFramec::aApm(FMatDsptr mat)
{
	markerFrame->aApm = mat;
}

double EndFramec::riOeO(size_t i) const
{
	return rOeO->at(i);
}

FColDsptr MbD::EndFramec::rpmp()
{
	return FColDsptr();
}

FColDsptr EndFramec::rmeO()
{
	return markerFrame->aAOm->timesFullColumn(rmem);
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

std::shared_ptr<EndFrameqc> MbD::EndFramec::followEndFrame(EndFrmsptr frmi)
{
	assert(false);
	return std::shared_ptr<EndFrameqc>();
}

bool MbD::EndFramec::isEndFrameqc()
{
	return false;
}

SpatialContainerFrame* MbD::EndFramec::getPartFrame() const
{
	return markerFrame->getPartFrame();
}

std::shared_ptr<EulerParameters<double>> MbD::EndFramec::qEOe() const
{
	return aAOe->asEulerParameters();
}

FColDsptr MbD::EndFramec::vOeO() const
{
	return markerFrame->vOmO();
}

FColDsptr MbD::EndFramec::aOeO() const
{
	return markerFrame->aOmO();
}
