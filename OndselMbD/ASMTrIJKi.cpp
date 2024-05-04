#include "ASMTrIJKi.h"
#include "Units.h"

using namespace MbD;

std::shared_ptr<ASMTrIJKi> MbD::ASMTrIJKi::With()
{
	auto inst = std::make_shared<ASMTrIJKi>();
	inst->initialize();
	return inst;
}

std::shared_ptr<KinematicIJ> MbD::ASMTrIJKi::mbdClassNew()
{
	return std::shared_ptr<KinematicIJ>();
}

double MbD::ASMTrIJKi::asmtUnit()
{
	return asmtUnits()->length;
}
