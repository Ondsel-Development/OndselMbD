#include "ASMTTorqueIJ.h"

using namespace MbD;

std::shared_ptr<ASMTTorqueIJ> MbD::ASMTTorqueIJ::With()
{
	auto inst = std::make_shared<ASMTTorqueIJ>();
	inst->initialize();
	return inst;
}
