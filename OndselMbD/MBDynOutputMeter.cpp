#include <regex>

#include "MBDynOutputMeter.h"

using namespace MbD;

void MbD::MBDynOutputMeter::parseMBDyn(std::string line)
{
	outputMeterString = line;
	arguments = collectArgumentsFor("output meter", line);
	assert(readStringOffTop(arguments) == "string");
	formula = popOffTop(arguments);
	formula = std::regex_replace(formula, std::regex("\""), "");
}

void MbD::MBDynOutputMeter::readFunction(std::vector<std::string>& args)
{
	assert(false);
}
