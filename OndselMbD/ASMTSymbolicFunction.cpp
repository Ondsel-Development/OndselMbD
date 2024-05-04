#include "ASMTSymbolicFunction.h"

using namespace MbD;

std::shared_ptr<ASMTSymbolicFunction> MbD::ASMTSymbolicFunction::With()
{
	auto inst = std::make_shared<ASMTSymbolicFunction>();
	inst->initialize();
	return inst;
}

std::shared_ptr<Units> MbD::ASMTSymbolicFunction::mbdUnits()
{
	return container->mbdUnits();
}

std::shared_ptr<Units> MbD::ASMTSymbolicFunction::asmtUnits()
{
	return container->asmtUnits();
}

std::shared_ptr<System> MbD::ASMTSymbolicFunction::mbdSys()
{
	return container->mbdSys();
}
