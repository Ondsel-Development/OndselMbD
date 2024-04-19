#include "ForTorActionComp.h"

using namespace MbD;

std::shared_ptr<ForTorActionComp> MbD::ForTorActionComp::With()
{
	auto inst = std::make_shared<ForTorActionComp>();
	inst->initialize();
	return inst;
}
