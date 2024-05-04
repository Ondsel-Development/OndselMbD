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
	assert(readStringNoSpacesOffTop(args) == "element");
	elementLabel = readStringNoSpacesOffTop(args);
	elementType = readStringNoSpacesOffTop(args);
	str = readStringNoSpacesOffTop(args);
	component = readStringNoSpacesOffTop(args);
	direct = readStringNoSpacesOffTop(args);
	output = readStringNoSpacesOffTop(args);
	yesno = readStringNoSpacesOffTop(args);
}

void MbD::MBDynDriveElement::createASMT()
{
	assert(false);
}
