#include "ASMTAngleIJz.h"
#include "AngleZIeqcJeqc.h"

using namespace MbD;

std::shared_ptr<ASMTAngleIJz> MbD::ASMTAngleIJz::With()
{
	auto inst = std::make_shared<ASMTAngleIJz>();
	inst->initialize();
	return inst;
}

std::shared_ptr<KinematicIJ> MbD::ASMTAngleIJz::mbdClassNew()
{
	return AngleZIeqcJeqc::With();
}
