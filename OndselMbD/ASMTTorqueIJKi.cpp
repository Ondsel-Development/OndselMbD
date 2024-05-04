#include "ASMTTorqueIJKi.h"
#include "Units.h"

using namespace MbD;

std::shared_ptr<ASMTTorqueIJKi> MbD::ASMTTorqueIJKi::With()
{
	auto inst = std::make_shared<ASMTTorqueIJKi>();
	inst->initialize();
	return inst;
}

std::shared_ptr<KinematicIJ> MbD::ASMTTorqueIJKi::mbdClassNew()
{
	return std::shared_ptr<KinematicIJ>();
}

double MbD::ASMTTorqueIJKi::asmtUnit()
{
	return asmtUnits()->torque;
}
