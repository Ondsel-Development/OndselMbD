#include "MBDynDriveString.h"

using namespace MbD;

std::shared_ptr<MBDynDriveString> MbD::MBDynDriveString::With()
{
	auto inst = std::make_shared<MBDynDriveString>();
	inst->initialize();
	return inst;
}

void MbD::MBDynDriveString::readFunction(std::vector<std::string>& args)
{
	assert(readStringNoSpacesOffTop(args) == "string");
	expression = popOffTop(args);
	output = readStringNoSpacesOffTop(args);
	yesno = readStringNoSpacesOffTop(args);
}

void MbD::MBDynDriveString::createASMT()
{
	assert(false);
}

