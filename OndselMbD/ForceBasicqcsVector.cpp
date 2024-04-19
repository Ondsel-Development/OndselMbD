#include "ForceBasicqcsVector.h"

using namespace MbD;

std::shared_ptr<ForceBasicqcsVector> MbD::ForceBasicqcsVector::With()
{
	auto inst = std::make_shared<ForceBasicqcsVector>();
	inst->initialize();
	return inst;
}
