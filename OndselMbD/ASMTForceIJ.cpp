#include "ASMTForceIJ.h"
#include "Units.h"

using namespace MbD;

std::shared_ptr<ASMTForceIJ> MbD::ASMTForceIJ::With()
{
	auto inst = std::make_shared<ASMTForceIJ>();
	inst->initialize();
	return inst;
}

void MbD::ASMTForceIJ::createMbD()
{
	assert(false);
}

double MbD::ASMTForceIJ::asmtUnit()
{
	return asmtUnits()->force;
}
