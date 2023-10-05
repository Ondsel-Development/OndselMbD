/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselMbD.                                       *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include <assert.h>
#include <memory>

#include "EndFramec.h"
#include "MarkerFrame.h"
#include "EndFrameqc.h"
#include "CREATE.h"

using namespace MbD;

EndFramec::EndFramec() {
}

EndFramec::EndFramec(const char* str) : CartesianFrame(str) {
}

FMatDsptr MbD::EndFramec::aAeO()
{
	return aAOe->transpose();
}

System* EndFramec::root()
{
	return markerFrame->root();
}

void EndFramec::initialize()
{
}

void EndFramec::setMarkerFrame(MarkerFrame* markerFrm)
{
	markerFrame = markerFrm;
}

MarkerFrame* EndFramec::getMarkerFrame()
{
	return markerFrame;
}

void EndFramec::initializeLocally()
{
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

FColDsptr EndFramec::aAjOe(int j)
{
	return aAOe->column(j);
}

double EndFramec::riOeO(int i)
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
	auto frmIeqc = CREATE<EndFrameqc>::With();
	markerFrame->addEndFrame(frmIeqc);
	return frmIeqc;
}

void MbD::EndFramec::fillpqsumu(FColDsptr col)
{
}

void MbD::EndFramec::fillpqsumudot(FColDsptr col)
{
}

void MbD::EndFramec::setpqsumu(FColDsptr col)
{
}

void MbD::EndFramec::setpqsumudot(FColDsptr col)
{
}