#include "ASMTOmegaIJKi.h"
#include "Units.h"
#include "OmeCompIeqcJeqcKeqc.h"

using namespace MbD;

std::shared_ptr<ASMTOmegaIJKi> MbD::ASMTOmegaIJKi::With()
{
	auto inst = std::make_shared<ASMTOmegaIJKi>();
	inst->initialize();
	return inst;
}

std::shared_ptr<KinematicIJ> MbD::ASMTOmegaIJKi::mbdClassNew()
{
	return OmeCompIeqcJeqcKeqc::With();
}

double MbD::ASMTOmegaIJKi::asmtUnit()
{
	return asmtUnits()->omega;
}
