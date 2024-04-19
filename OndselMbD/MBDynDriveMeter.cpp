#include "MBDynDriveMeter.h"

using namespace MbD;

std::shared_ptr<MBDynDriveMeter> MbD::MBDynDriveMeter::With()
{
	auto inst = std::make_shared<MBDynDriveMeter>();
	inst->initialize();
	return inst;
}

void MbD::MBDynDriveMeter::readFunction(std::vector<std::string>& args)
{
	assert(false);
}

void MbD::MBDynDriveMeter::createASMT()
{
	assert(false);
}

