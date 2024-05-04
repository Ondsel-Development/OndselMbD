#include "ASMTOmegaIJ.h"
#include "Units.h"

using namespace MbD;

std::shared_ptr<ASMTOmegaIJ> MbD::ASMTOmegaIJ::With()
{
	auto inst = std::make_shared<ASMTOmegaIJ>();
	inst->initialize();
	return inst;
}

std::shared_ptr<KinematicIJ> MbD::ASMTOmegaIJ::mbdClassNew()
{
	return std::shared_ptr<KinematicIJ>();
}

void MbD::ASMTOmegaIJ::createMbD()
{
	assert(false);
}

double MbD::ASMTOmegaIJ::asmtUnit()
{
	return asmtUnits()->omega;
}
