#include "MBDynStructuralStatic.h"

using namespace MbD;

std::shared_ptr<MBDynStructuralStatic> MbD::MBDynStructuralStatic::With()
{
	auto inst = std::make_shared<MBDynStructuralStatic>();
	inst->initialize();
	return inst;
}

void MbD::MBDynStructuralStatic::parseMBDyn(std::string line)
{
	strucString = line;
	arguments = collectArgumentsFor("structural", line);
	readLabel(arguments);
	auto nodeType = readStringOffTop(arguments);
	assert(nodeType == "static");
	readPosition(arguments);
	readOrientation(arguments);
	readVelocity(arguments);
	readOmega(arguments);
}
