#include "ASMTSymbolicFunction.h"

using namespace MbD;

std::shared_ptr<ASMTSymbolicFunction> MbD::ASMTSymbolicFunction::With()
{
	auto inst = std::make_shared<ASMTSymbolicFunction>();
	inst->initialize();
	return inst;
}
