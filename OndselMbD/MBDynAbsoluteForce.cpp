#include <regex>

#include "MBDynAbsoluteForce.h"

using namespace MbD;

std::shared_ptr<MBDynAbsoluteForce> MbD::MBDynAbsoluteForce::With()
{
	auto inst = std::make_shared<MBDynAbsoluteForce>();
	inst->initialize();
	return inst;
}

void MbD::MBDynAbsoluteForce::parseMBDyn(std::string line)
{
	forceString = line;
	arguments = collectArgumentsFor("force", line);
	readLabel(arguments);
	type = readStringOffTop(arguments);
	nodeName = readStringOffTop(arguments);
	rnmn = readPosition(arguments);
	assert(readStringOffTop(arguments) == "single");
	fn = readVector3(arguments);
	assert(readStringOffTop(arguments) == "string");
	formula = popOffTop(arguments);
	formula = std::regex_replace(formula, std::regex("\""), "");
}

void MbD::MBDynAbsoluteForce::createASMT()
{
	assert(false);
}
