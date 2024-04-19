#include "MBDynNodePlugin.h"

using namespace MbD;

std::shared_ptr<MBDynNodePlugin> MbD::MBDynNodePlugin::With()
{
	auto inst = std::make_shared<MBDynNodePlugin>();
	inst->initialize();
	return inst;
}

void MbD::MBDynNodePlugin::parseMBDyn(std::string line)
{
	pluginString = line;
	arguments = collectArgumentsFor("set", line);
	assert(lineHasToken(readStringOffTop(arguments), "node"));
	varName = readStringOffTop(arguments);
	nodeName = readStringOffTop(arguments);
	readStringOffTop(arguments);
	auto str = readStringOffTop(arguments);
	auto firstPos = str.find("\"", 0);
	auto secondPos = str.find("\"", firstPos + 1);
	_string = str.substr(firstPos + 1, secondPos - firstPos - 1);
}

void MbD::MBDynNodePlugin::createASMT()
{
	assert(false);
}
