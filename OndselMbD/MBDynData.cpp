#include "MBDynData.h"

using namespace MbD;

std::shared_ptr<MBDynData> MbD::MBDynData::With()
{
	auto inst = std::make_shared<MBDynData>();
	inst->initialize();
	return inst;
}

void MbD::MBDynData::initialize()
{
	assert(false);
}

void MbD::MBDynData::parseMBDyn(std::vector<std::string>& lines)
{
	assert(lines.size() == 3);
	std::vector<std::string> tokens{ "problem:", "initial", "value" };
	auto problemit = findLineWith(lines, tokens);
	assert(problemit != lines.end());
}
