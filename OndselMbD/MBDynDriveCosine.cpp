#include "MBDynDriveCosine.h"

using namespace MbD;

std::shared_ptr<MBDynDriveCosine> MbD::MBDynDriveCosine::With()
{
	auto inst = std::make_shared<MBDynDriveCosine>();
	inst->initialize();
	return inst;
}

void MbD::MBDynDriveCosine::readFunction(std::vector<std::string>& args)
{
	assert(false);
}

void MbD::MBDynDriveCosine::createASMT()
{
	assert(false);
}
