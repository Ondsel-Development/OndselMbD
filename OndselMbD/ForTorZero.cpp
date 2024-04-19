#include "ForTorZero.h"

using namespace MbD;

std::shared_ptr<ForTorZero> MbD::ForTorZero::With()
{
	auto inst = std::make_shared<ForTorZero>();
	inst->initialize();
	return inst;
}
