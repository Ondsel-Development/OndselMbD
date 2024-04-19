#include "ASMTdAngleIJy.h"

using namespace MbD;

std::shared_ptr<ASMTdAngleIJy> MbD::ASMTdAngleIJy::With()
{
	auto inst = std::make_shared<ASMTdAngleIJy>();
	inst->initialize();
	return inst;
}
