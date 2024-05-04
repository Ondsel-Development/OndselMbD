#include "ASMTForceIJKi.h"
#include "Units.h"

using namespace MbD;

std::shared_ptr<ASMTForceIJKi> MbD::ASMTForceIJKi::With()
{
	auto inst = std::make_shared<ASMTForceIJKi>();
	inst->initialize();
	return inst;
}

std::shared_ptr<KinematicIJ> MbD::ASMTForceIJKi::mbdClassNew()
{
	return std::shared_ptr<KinematicIJ>();
}

double MbD::ASMTForceIJKi::asmtUnit()
{
	return asmtUnits()->force;
}
