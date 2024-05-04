#include "ForceTorqueActionComp.h"

using namespace MbD;

std::shared_ptr<ForceTorqueActionComp> MbD::ForceTorqueActionComp::With()
{
	auto inst = std::make_shared<ForceTorqueActionComp>();
	inst->initialize();
	return inst;
}
