#include "ForceTorqueZero.h"

using namespace MbD;

std::shared_ptr<ForceTorqueZero> MbD::ForceTorqueZero::With()
{
	auto inst = std::make_shared<ForceTorqueZero>();
	inst->initialize();
	return inst;
}
