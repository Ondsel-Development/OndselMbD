#include "ASMTrIJKi.h"

using namespace MbD;

std::shared_ptr<ASMTrIJKi> MbD::ASMTrIJKi::With()
{
	auto inst = std::make_shared<ASMTrIJKi>();
	inst->initialize();
	return inst;
}
