#include "ASMTdAngleIJx.h"
#include "DAngleXIeqcJeqc.h"

using namespace MbD;

std::shared_ptr<ASMTdAngleIJx> MbD::ASMTdAngleIJx::With()
{
	auto inst = std::make_shared<ASMTdAngleIJx>();
	inst->initialize();
	return inst;
}

std::shared_ptr<KinematicIJ> MbD::ASMTdAngleIJx::mbdClassNew()
{
	return DAngleXIeqcJeqc::With();
}
