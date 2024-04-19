#include "MBDynDriveSine.h"

using namespace MbD;

std::shared_ptr<MBDynDriveSine> MbD::MBDynDriveSine::With()
{
	auto inst = std::make_shared<MBDynDriveSine>();
	inst->initialize();
	return inst;
}

void MbD::MBDynDriveSine::readFunction(std::vector<std::string>& args)
{
	assert(false);
}

void MbD::MBDynDriveSine::createASMT()
{
	assert(false);
}

