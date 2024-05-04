#include "ASMTrIJ.h"
#include "Units.h"
#include "DistIeqcJeqc.h"

using namespace MbD;

std::shared_ptr<ASMTrIJ> MbD::ASMTrIJ::With()
{
	auto inst = std::make_shared<ASMTrIJ>();
	inst->initialize();
	return inst;
}

std::shared_ptr<KinematicIJ> MbD::ASMTrIJ::mbdClassNew()
{
	return DistIeqcJeqc::With();
}

double MbD::ASMTrIJ::asmtUnit()
{
	return asmtUnits()->length;
}
