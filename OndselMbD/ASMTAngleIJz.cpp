#include "ASMTAngleIJz.h"

using namespace MbD;

std::shared_ptr<ASMTAngleIJz> MbD::ASMTAngleIJz::With()
{
	auto inst = std::make_shared<ASMTAngleIJz>();
	inst->initialize();
	return inst;
}
