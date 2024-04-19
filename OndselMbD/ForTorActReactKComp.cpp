#include "ForTorActReactKComp.h"

using namespace MbD;

std::shared_ptr<ForTorActReactKComp> MbD::ForTorActReactKComp::With()
{
	auto inst = std::make_shared<ForTorActReactKComp>();
	inst->initialize();
	return inst;
}

void MbD::ForTorActReactKComp::postDynPredictor()
{
	assert(false);
}
