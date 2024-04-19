#include "ForTorActReactOComp.h"

using namespace MbD;

std::shared_ptr<ForTorActReactOComp> MbD::ForTorActReactOComp::With()
{
	auto inst = std::make_shared<ForTorActReactOComp>();
	inst->initialize();
	return inst;
}

void MbD::ForTorActReactOComp::postDynPredictor()
{
	assert(false);
}
