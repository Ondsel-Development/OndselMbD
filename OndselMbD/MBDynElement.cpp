#include "MBDynElement.h"

using namespace MbD;

std::shared_ptr<MBDynElement> MbD::MBDynElement::With()
{
	auto inst = std::make_shared<MBDynElement>();
	inst->initialize();
	return inst;
}

void MbD::MBDynElement::initialize()
{
	//Do nothing.
}

void MBDynElement::parseMBDyn(std::vector<std::string> &lines) {
	MBDynItem::parseMBDyn(lines);
}
