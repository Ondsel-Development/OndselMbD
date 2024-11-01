/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include "ASMTItem.h"
#include "ASMTSpatialContainer.h"
#include "ASMTAssembly.h"
#include "Constant.h"
#include <algorithm>

using namespace MbD;

std::shared_ptr<ASMTItem> MbD::ASMTItem::With()
{
	auto inst = std::make_shared<ASMTItem>();
	inst->initialize();
	return inst;
}

void MbD::ASMTItem::initialize()
{
	//Subclass responsibility.
	assert(false);
}

void MbD::ASMTItem::initializeGlobally()
{
	//Subclass responsibility.
	assert(false);
}

void MbD::ASMTItem::initializeLocally()
{
	//Subclass responsibility.
	assert(false);
}

ASMTAssembly* MbD::ASMTItem::root()
{
	return container->root();
}

ASMTSpatialContainer* MbD::ASMTItem::partOrAssembly()
{
	return container->partOrAssembly();
}

ASMTPart* MbD::ASMTItem::part()
{
	return container->part();
}

void MbD::ASMTItem::noop()
{
	//No Operations
}

std::string MbD::ASMTItem::classname()
{
	std::string str = typeid(*this).name();
	auto answer = str.substr(11, str.size() - 11);
	return answer;
}

void MbD::ASMTItem::setName(std::string str)
{
	name = str;
}

void MbD::ASMTItem::parseASMT(std::vector<std::string>&)
{
	assert(false);
}

std::string MbD::ASMTItem::popOffTop(std::vector<std::string>& args)
{
	auto str = args.at(0);	//Must copy string
	args.erase(args.begin());
	return str;
}

std::string MbD::ASMTItem::readStringNoSpacesOffTop(std::vector<std::string>& args)
{
	//Return top string without whitespaces.
	std::string str = popOffTop(args);
	str.erase(std::remove_if(str.begin(), str.end(), isspace), str.end());
	return str;
}

FRowDsptr MbD::ASMTItem::readRowOfDoubles(std::string& line)
{
	std::istringstream iss(line);
	auto readRowOfDoubles = FullRow<double>::With();
	double d;
	while (iss >> d) {
		readRowOfDoubles->push_back(d);
	}
	return readRowOfDoubles;
}

FColDsptr MbD::ASMTItem::readColumnOfDoubles(std::string& line)
{
	std::istringstream iss(line);
	auto readColumnOfDoubles = FullColumn<double>::With();
	double d;
	while (iss >> d) {
		readColumnOfDoubles->push_back(d);
	}
	return readColumnOfDoubles;
}

double MbD::ASMTItem::readDouble(std::string& line)
{
	std::istringstream iss(line);
	double d;
	iss >> d;
	return d;
}

int MbD::ASMTItem::readInt(std::string& line)
{
	std::istringstream iss(line);
	int i;
	iss >> i;
	return i;
}

size_t MbD::ASMTItem::readSize_t(std::string& line)
{
	std::istringstream iss(line);
	size_t i;
	iss >> i;
	return i;
}

bool MbD::ASMTItem::readBool(std::string& line)
{
	if (line.find("true") != std::string::npos)
	{
		return true;
	}
	else 	if (line.find("false") != std::string::npos)
	{
		return false;
	}
	else {
		assert(false);
		return false;
	}
}

std::string MbD::ASMTItem::readString(std::string& line)
{
	//Read string without whitespaces.
	std::string str = line;
	str.erase(std::remove_if(str.begin(), str.end(), isspace), str.end());
	return str;
}

void MbD::ASMTItem::readName(std::vector<std::string>& lines)
{
	assert(readStringNoSpacesOffTop(lines) == "Name");
	name = readStringNoSpacesOffTop(lines);
}

std::string MbD::ASMTItem::fullName(std::string partialName)
{
	std::string longerName = "/" + name + partialName;
	if (container == nullptr) {
		return longerName;
	}
	else {
		return container->fullName(longerName);
	}
}

void MbD::ASMTItem::readDoublesInto(std::string& str, std::string label, FRowDsptr& row)
{
	auto pos = str.find(label);
	assert(pos != std::string::npos);
	str.erase(0, pos + label.length());
	row = readRowOfDoubles(str);
}

void MbD::ASMTItem::deleteMbD()
{
	mbdObject = nullptr;
}

void MbD::ASMTItem::createMbD()
{
	noop();
	assert(false);
}

void MbD::ASMTItem::updateFromMbD()
{
	assert(false);
}

std::shared_ptr<StateData> MbD::ASMTItem::dataFromMbD()
{
	assert(false);
	return std::shared_ptr<StateData>();
}

void MbD::ASMTItem::compareResults(AnalysisType)
{
	assert(false);
}

void MbD::ASMTItem::outputResults(AnalysisType)
{
	assert(false);
}

std::shared_ptr<Units> MbD::ASMTItem::asmtUnits()
{
	return root()->asmtUnits;
}

std::shared_ptr<Units> MbD::ASMTItem::mbdUnits()
{
	return mbdSys()->mbdUnits;
}

std::shared_ptr<System> MbD::ASMTItem::mbdSys()
{
	return root()->mbdSystem;
}

std::shared_ptr<Constant> MbD::ASMTItem::sptrConstant(double value)
{
	return Constant::With(value);
}

void MbD::ASMTItem::storeOnLevel(std::ofstream&, size_t)
{
	noop();
	assert(false);
}

void MbD::ASMTItem::storeOnLevelTabs(std::ofstream& os, size_t level)
{
	for (size_t i = 0; i < level; i++)
	{
		os << '\t';
	}
}

void MbD::ASMTItem::storeOnLevelString(std::ofstream& os, size_t level, std::string str)
{
	storeOnLevelTabs(os, level);
	os << str << std::endl;
}

void MbD::ASMTItem::storeOnLevelDouble(std::ofstream& os, size_t level, double value)
{
	storeOnLevelTabs(os, level);
	os << value << std::endl;
}

void MbD::ASMTItem::storeOnLevelInt(std::ofstream& os, size_t level, int i)
{
	storeOnLevelTabs(os, level);
	os << i << std::endl;
}

void MbD::ASMTItem::storeOnLevelSize_t(std::ofstream& os, size_t level, size_t i)
{
	storeOnLevelTabs(os, level);
	os << i << std::endl;
}

void MbD::ASMTItem::storeOnLevelBool(std::ofstream& os, size_t level, bool value)
{
	storeOnLevelTabs(os, level);
	if (value) {
		os << "true" << std::endl;
	}
	else {
		os << "false" << std::endl;
	}
}

void MbD::ASMTItem::storeOnLevelArray(std::ofstream& os, size_t level, std::vector<double> array)
{
	storeOnLevelTabs(os, level);
	for (size_t i = 0; i < array.size(); i++)
	{
		os << array[i] << '\t';
	}
	os << std::endl;
}

void MbD::ASMTItem::storeOnLevelName(std::ofstream& os, size_t level)
{
	storeOnLevelString(os, level, "Name");
	storeOnLevelString(os, level + 1, name);
}

void MbD::ASMTItem::storeOnTimeSeries(std::ofstream&)
{
	assert(false);
}

void MbD::ASMTItem::logString(std::string& str)
{
	std::cout << str << std::endl;
}

void MbD::ASMTItem::logString(const char* chars)
{
	std::cout << chars << std::endl;
}
