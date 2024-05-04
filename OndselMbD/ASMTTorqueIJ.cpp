#include "ASMTTorqueIJ.h"
#include "Units.h"

using namespace MbD;

std::shared_ptr<ASMTTorqueIJ> MbD::ASMTTorqueIJ::With()
{
	auto inst = std::make_shared<ASMTTorqueIJ>();
	inst->initialize();
	return inst;
}

void MbD::ASMTTorqueIJ::createMbD()
{
	assert(false);
}

double MbD::ASMTTorqueIJ::asmtUnit()
{
	return asmtUnits()->torque;
}
