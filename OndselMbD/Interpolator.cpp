#include "Interpolator.h"

using namespace MbD;

std::shared_ptr<Interpolator> MbD::Interpolator::With()
{
	auto inst = std::make_shared<Interpolator>();
	inst->initialize();
	return inst;
}
