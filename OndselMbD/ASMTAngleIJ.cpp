#include "ASMTAngleIJ.h"
#include "Units.h"

using namespace MbD;

std::shared_ptr<ASMTAngleIJ> MbD::ASMTAngleIJ::With()
{
	auto inst = std::make_shared<ASMTAngleIJ>();
	inst->initialize();
	return inst;
}

double MbD::ASMTAngleIJ::asmtUnit()
{
	return asmtUnits()->angle;
}
