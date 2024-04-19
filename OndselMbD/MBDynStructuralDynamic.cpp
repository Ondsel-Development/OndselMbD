#include "MBDynStructuralDynamic.h"

using namespace MbD;

std::shared_ptr<MBDynStructuralDynamic> MbD::MBDynStructuralDynamic::With()
{
	auto inst = std::make_shared<MBDynStructuralDynamic>();
	inst->initialize();
	return inst;
}

void MbD::MBDynStructuralDynamic::parseMBDyn(std::string line)
{
	strucString = line;
	arguments = collectArgumentsFor("structural", line);
	readLabel(arguments);
	auto nodeType = readStringOffTop(arguments);
	assert(nodeType == "dynamic");
	readPosition(arguments);
	readOrientation(arguments);
	readVelocity(arguments);
	readOmega(arguments);
}
