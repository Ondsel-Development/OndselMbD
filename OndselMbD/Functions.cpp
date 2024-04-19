#include "Functions.h"

using namespace MbD;

std::shared_ptr<Functions> MbD::Functions::With()
{
	auto inst = std::make_shared<Functions>();
	inst->initialize();
	return inst;
}
