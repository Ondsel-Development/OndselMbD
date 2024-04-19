#include "ASMTOmegaIJ.h"

using namespace MbD;

std::shared_ptr<ASMTOmegaIJ> MbD::ASMTOmegaIJ::With()
{
	auto inst = std::make_shared<ASMTOmegaIJ>();
	inst->initialize();
	return inst;
}
