#include "ASMTvrIJ.h"
#include "Units.h"
#include "VelRadIeqcJeqc.h"

using namespace MbD;

std::shared_ptr<ASMTvrIJ> MbD::ASMTvrIJ::With()
{
	auto inst = std::make_shared<ASMTvrIJ>();
	inst->initialize();
	return inst;
}

std::shared_ptr<KinematicIJ> MbD::ASMTvrIJ::mbdClassNew()
{
	return VelRadIeqcJeqc::With();
}

double MbD::ASMTvrIJ::asmtUnit()
{
	return asmtUnits()->velocity;
}
