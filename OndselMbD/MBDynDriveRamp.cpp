#include "MBDynDriveRamp.h"

using namespace MbD;

std::shared_ptr<MBDynDriveRamp> MbD::MBDynDriveRamp::With()
{
	auto inst = std::make_shared<MBDynDriveRamp>();
	inst->initialize();
	return inst;
}

void MbD::MBDynDriveRamp::readFunction(std::vector<std::string>& args)
{
	assert(false);
}

void MbD::MBDynDriveRamp::createASMT()
{
	assert(false);
}

