#include "ASMTTorqueIJKi.h"

using namespace MbD;

std::shared_ptr<ASMTTorqueIJKi> MbD::ASMTTorqueIJKi::With()
{
	auto inst = std::make_shared<ASMTTorqueIJKi>();
	inst->initialize();
	return inst;
}
