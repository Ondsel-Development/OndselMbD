#include "ForceBasicqcsComp.h"

using namespace MbD;

std::shared_ptr<ForceBasicqcsComp> MbD::ForceBasicqcsComp::With()
{
	auto inst = std::make_shared<ForceBasicqcsComp>();
	inst->initialize();
	return inst;
}
