#include "ForceBasicqccqVector.h"

using namespace MbD;

std::shared_ptr<ForceBasicqccqVector> MbD::ForceBasicqccqVector::With()
{
	auto inst = std::make_shared<ForceBasicqccqVector>();
	inst->initialize();
	return inst;
}
