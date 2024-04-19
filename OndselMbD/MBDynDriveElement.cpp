#include "MBDynDriveElement.h"

using namespace MbD;

std::shared_ptr<MBDynDriveElement> MbD::MBDynDriveElement::With()
{
	auto inst = std::make_shared<MBDynDriveElement>();
	inst->initialize();
	return inst;
}

void MbD::MBDynDriveElement::readFunction(std::vector<std::string>& args)
{
	assert(readStringOffTop(arguments) == "element");
	elementLabel = readStringOffTop(args);
	elementType = readStringOffTop(args);
	str = readStringOffTop(args);
	component = readStringOffTop(args);
	direct = readStringOffTop(args);
	output = readStringOffTop(args);
	yesno = readStringOffTop(args);
}

void MbD::MBDynDriveElement::createASMT()
{
	assert(false);
}
