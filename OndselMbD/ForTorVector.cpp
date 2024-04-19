#include <algorithm>

#include "ForTorVector.h"

using namespace MbD;

std::shared_ptr<ForTorVector> MbD::ForTorVector::With()
{
	auto inst = std::make_shared<ForTorVector>();
	inst->initialize();
	return inst;
}

void MbD::ForTorVector::useEquationNumbers()
{
	std::for_each(components->begin(), components->end(), [&](auto component) { component->useEquationNumbers(); });
}
