#include "ASMTOmegaIJKi.h"

using namespace MbD;

std::shared_ptr<ASMTOmegaIJKi> MbD::ASMTOmegaIJKi::With()
{
	auto inst = std::make_shared<ASMTOmegaIJKi>();
	inst->initialize();
	return inst;
}
