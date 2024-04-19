/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
#include <fstream>	

#include "ASMTMotion.h"

using namespace MbD;

std::shared_ptr<ASMTMotion> MbD::ASMTMotion::With()
{
	auto inst = std::make_shared<ASMTMotion>();
	inst->initialize();
	return inst;
}

void MbD::ASMTMotion::readMotionSeries(std::vector<std::string>& lines)
{
	std::string str = lines[0];
	std::string substr = "MotionSeries";
	auto pos = str.find(substr);
	assert(pos != std::string::npos);
	str.erase(0, pos + substr.length());
	auto seriesName = readString(str);
	assert(fullName("") == seriesName);
	lines.erase(lines.begin());
	readFXonIs(lines);
	readFYonIs(lines);
	readFZonIs(lines);
	readTXonIs(lines);
	readTYonIs(lines);
	readTZonIs(lines);
}

void MbD::ASMTMotion::initMarkers()
{
	assert(false);
}

void ASMTMotion::storeOnLevel(std::ofstream&, size_t)
{
	assert(false);
}

void ASMTMotion::storeOnTimeSeries(std::ofstream&)
{
	assert(false);
}
