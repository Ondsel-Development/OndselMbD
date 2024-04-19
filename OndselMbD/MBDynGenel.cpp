#include "MBDynGenel.h"
#include "MBDynClampGenel.h"

using namespace MbD;

std::shared_ptr<MBDynGenel> MbD::MBDynGenel::newGenel(std::string statement)
{
	std::vector<std::string> tokens;
	tokens = { "clamp" };
	if (lineHasTokens(statement, tokens)) {
		return std::make_shared<MBDynClampGenel>();
	}
	assert(false);
	return std::shared_ptr<MBDynGenel>();
}

void MbD::MBDynGenel::parseMBDyn(std::string line)
{
	assert(false);
}

void MbD::MBDynGenel::createASMT()
{
	assert(false);
}
