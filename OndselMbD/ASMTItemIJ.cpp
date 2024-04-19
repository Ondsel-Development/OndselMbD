/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
#include <fstream>	

#include "ASMTItemIJ.h"
#include "Joint.h"
#include "ASMTAssembly.h"
#include "EndFrameqc.h"

using namespace MbD;

MbD::ASMTItemIJ::ASMTItemIJ()
{
	cFIO = std::make_shared<std::vector<std::shared_ptr<FullColumn<double>>>>();
	cTIO = std::make_shared<std::vector<std::shared_ptr<FullColumn<double>>>>();
}

std::shared_ptr<ASMTItemIJ> MbD::ASMTItemIJ::With()
{
	auto inst = std::make_shared<ASMTItemIJ>();
	inst->initialize();
	return inst;
}

void MbD::ASMTItemIJ::initialize()
{
	//Do nothing.
}

void MbD::ASMTItemIJ::parseASMT(std::vector<std::string>& lines)
{
	readName(lines);
	readMarkerI(lines);
	readMarkerJ(lines);
}

void MbD::ASMTItemIJ::setMarkerI(std::shared_ptr<ASMTMarker> mkrI)
{
	markerI = mkrI;
}

void MbD::ASMTItemIJ::setMarkerJ(std::shared_ptr<ASMTMarker> mkrJ)
{
	markerJ = mkrJ;
}

void MbD::ASMTItemIJ::readMarkerI(std::vector<std::string>& lines)
{
	assert(readStringOffTop(lines) == "MarkerI");
	auto markerName = readStringOffTop(lines);
	markerI = root()->markerAt(markerName);
}

void MbD::ASMTItemIJ::readMarkerJ(std::vector<std::string>& lines)
{
	assert(readStringOffTop(lines) == "MarkerJ");
	auto markerName = readStringOffTop(lines);
	markerJ = root()->markerAt(markerName);
}

void MbD::ASMTItemIJ::readFXonIs(std::vector<std::string>& lines)
{
	std::string str = lines[0];
	readDoublesInto(str, "FXonI", infxs);
	lines.erase(lines.begin());
}

void MbD::ASMTItemIJ::readFYonIs(std::vector<std::string>& lines)
{
	std::string str = lines[0];
	readDoublesInto(str, "FYonI", infys);
	lines.erase(lines.begin());
}

void MbD::ASMTItemIJ::readFZonIs(std::vector<std::string>& lines)
{
	std::string str = lines[0];
	readDoublesInto(str, "FZonI", infzs);
	lines.erase(lines.begin());
}

void MbD::ASMTItemIJ::readTXonIs(std::vector<std::string>& lines)
{
	std::string str = lines[0];
	readDoublesInto(str, "TXonI", intxs);
	lines.erase(lines.begin());
}

void MbD::ASMTItemIJ::readTYonIs(std::vector<std::string>& lines)
{
	std::string str = lines[0];
	readDoublesInto(str, "TYonI", intys);
	lines.erase(lines.begin());
}

void MbD::ASMTItemIJ::readTZonIs(std::vector<std::string>& lines)
{
	std::string str = lines[0];
	readDoublesInto(str, "TZonI", intzs);
	lines.erase(lines.begin());
}

void MbD::ASMTItemIJ::storeOnLevel(std::ofstream& os, size_t level)
{
	storeOnLevelString(os, level + 1, "MarkerI");
	storeOnLevelString(os, level + 2, markerI->name);
	storeOnLevelString(os, level + 1, "MarkerJ");
	storeOnLevelString(os, level + 2, markerJ->name);
}

void MbD::ASMTItemIJ::storeOnTimeSeries(std::ofstream& os)
{
	auto n = cFIO->size();
	os << "FXonI\t";
	for (size_t i = 0; i < n; i++)
	{
		os << cFIO->at(i)-> at(0) << '\t';
	}
	os << std::endl;
	os << "FYonI\t";
	for (size_t i = 0; i < n; i++)
	{
		os << cFIO->at(i)->at(1) << '\t';
	}
	os << std::endl;
	os << "FZonI\t";
	for (size_t i = 0; i < n; i++)
	{
		os << cFIO->at(i)->at(2) << '\t';
	}
	os << std::endl;
	os << "TXonI\t";
	for (size_t i = 0; i < n; i++)
	{
		os << cTIO->at(i)->at(0) << '\t';
	}
	os << std::endl;
	os << "TYonI\t";
	for (size_t i = 0; i < n; i++)
	{
		os << cTIO->at(i)->at(1) << '\t';
	}
	os << std::endl;
	os << "TZonI\t";
	for (size_t i = 0; i < n; i++)
	{
		os << cTIO->at(i)->at(2) << '\t';
	}
	os << std::endl;
}

FColDsptr MbD::ASMTItemIJ::aFII(size_t i)
{
	auto mbdJoint = std::static_pointer_cast<Joint>(mbdObject);
	auto aAIO = mbdJoint->frmI->aAeO();
	return aAIO->timesFullColumn(aFIO(i));
}

FColDsptr MbD::ASMTItemIJ::aFIO(size_t i)
{
	return cFIO->at(i);
}

FColDsptr MbD::ASMTItemIJ::aTII(size_t i)
{
	auto mbdJoint = std::static_pointer_cast<Joint>(mbdObject);
	auto aAIO = mbdJoint->frmI->aAeO();
	return aAIO->timesFullColumn(aTIO(i));
}

FColDsptr MbD::ASMTItemIJ::aTIO(size_t i)
{
	return cTIO->at(i);
}
