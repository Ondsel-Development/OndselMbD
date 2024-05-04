#include <regex>

#include "MBDynOutputMeter.h"

using namespace MbD;

std::shared_ptr<MBDynOutputMeter> MbD::MBDynOutputMeter::With()
{
	auto inst = std::make_shared<MBDynOutputMeter>();
	inst->initialize();
	return inst;
}

void MbD::MBDynOutputMeter::parseMBDyn(std::string line)
{
	outputMeterString = line;
	arguments = collectArgumentsFor("output meter", line);
	assert(readStringNoSpacesOffTop(arguments) == "string");
	formula = popOffTop(arguments);
	formula = std::regex_replace(formula, std::regex("\""), "");
}

void MbD::MBDynOutputMeter::readFunction(std::vector<std::string>& args)
{
	assert(false);
}
