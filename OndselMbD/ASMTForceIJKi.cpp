#include "ASMTForceIJKi.h"

using namespace MbD;

std::shared_ptr<ASMTForceIJKi> MbD::ASMTForceIJKi::With()
{
	auto inst = std::make_shared<ASMTForceIJKi>();
	inst->initialize();
	return inst;
}
