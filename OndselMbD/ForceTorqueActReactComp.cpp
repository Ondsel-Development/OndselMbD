#include "ForceTorqueActReactComp.h"

using namespace MbD;

std::shared_ptr<ForceTorqueActReactComp> MbD::ForceTorqueActReactComp::With()
{
	auto inst = std::make_shared<ForceTorqueActReactComp>();
	inst->initialize();
	return inst;
}
