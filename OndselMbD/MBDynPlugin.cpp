#include "MBDynPlugin.h"
#include "MBDynNodePlugin.h"

using namespace MbD;

std::shared_ptr<MBDynPlugin> MbD::MBDynPlugin::newPlugin(std::string statement)
{
	std::vector<std::string> tokens;
	tokens = { "set:", "[", "node" };
	if (lineHasTokens(statement, tokens)) {
		return std::make_shared<MBDynNodePlugin>();
	}
	assert(false);
	return std::shared_ptr<MBDynPlugin>();
}

void MbD::MBDynPlugin::parseMBDyn(std::string line)
{
	assert(false);
}

void MbD::MBDynPlugin::createASMT()
{
	assert(false);
}
