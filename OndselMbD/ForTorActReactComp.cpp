#include "ForTorActReactComp.h"

using namespace MbD;

std::shared_ptr<ForTorActReactComp> MbD::ForTorActReactComp::With()
{
	auto inst = std::make_shared<ForTorActReactComp>();
	inst->initialize();
	return inst;
}

void MbD::ForTorActReactComp::postDynPredictor()
{
	assert(false);
}
