#include "ASMTvIJ.h"

using namespace MbD;

std::shared_ptr<ASMTvIJ> MbD::ASMTvIJ::With()
{
	auto inst = std::make_shared<ASMTvIJ>();
	inst->initialize();
	return inst;
}
