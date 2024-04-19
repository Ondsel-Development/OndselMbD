#include <regex>

#include "MBDynForce.h"
#include "MBDynAbsoluteForce.h"

using namespace MbD;

std::shared_ptr<MBDynForce> MbD::MBDynForce::newForce(std::string statement)
{
	std::vector<std::string> tokens;
	tokens = { "absolute" };
	if (lineHasTokens(statement, tokens)) {
		return std::make_shared<MBDynAbsoluteForce>();
	}
	assert(false);
	return std::shared_ptr<MBDynForce>();
}

void MbD::MBDynForce::parseMBDyn(std::string line)
{
	assert(false);
}

void MbD::MBDynForce::createASMT()
{
	assert(false);
}
