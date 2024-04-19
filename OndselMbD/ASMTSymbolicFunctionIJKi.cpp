#include "ASMTSymbolicFunctionIJKi.h"

using namespace MbD;

std::shared_ptr<ASMTSymbolicFunctionIJKi> MbD::ASMTSymbolicFunctionIJKi::With()
{
	auto inst = std::make_shared<ASMTSymbolicFunctionIJKi>();
	inst->initialize();
	return inst;
}
