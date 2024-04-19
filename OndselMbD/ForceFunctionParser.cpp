#include "ForceFunctionParser.h"

using namespace MbD;

std::shared_ptr<ForceFunctionParser> MbD::ForceFunctionParser::With()
{
	auto inst = std::make_shared<ForceFunctionParser>();
	inst->initialize();
	return inst;
}
