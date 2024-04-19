#include "ForceBasicqccqComp.h"

using namespace MbD;

std::shared_ptr<ForceBasicqccqComp> MbD::ForceBasicqccqComp::With()
{
	auto inst = std::make_shared<ForceBasicqccqComp>();
	inst->initialize();
	return inst;
}
