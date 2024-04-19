#include "ASMTvIJKi.h"

using namespace MbD;

std::shared_ptr<ASMTvIJKi> MbD::ASMTvIJKi::With()
{
	auto inst = std::make_shared<ASMTvIJKi>();
	inst->initialize();
	return inst;
}
