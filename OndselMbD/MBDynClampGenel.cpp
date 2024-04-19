#include <regex>

#include "MBDynClampGenel.h"

using namespace MbD;

std::shared_ptr<MBDynClampGenel> MbD::MBDynClampGenel::With()
{
	auto inst = std::make_shared<MBDynClampGenel>();
	inst->initialize();
	return inst;
}

void MbD::MBDynClampGenel::parseMBDyn(std::string line)
{
	genelString = line;
	arguments = collectArgumentsFor("genel", line);
	readLabel(arguments);
	type = readStringOffTop(arguments);
	nodeName = readStringOffTop(arguments);
	assert(readStringOffTop(arguments) == "abstract");
	valueType = readStringOffTop(arguments);
	assert(readStringOffTop(arguments) == "string");
	formula = popOffTop(arguments);
	formula = std::regex_replace(formula, std::regex("\""), "");
}

void MbD::MBDynClampGenel::createASMT()
{
	assert(false);
}
