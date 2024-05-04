#include "ASMTdAngleIJy.h"
#include "DAngleYIeqcJeqc.h"

using namespace MbD;

std::shared_ptr<ASMTdAngleIJy> MbD::ASMTdAngleIJy::With()
{
	auto inst = std::make_shared<ASMTdAngleIJy>();
	inst->initialize();
	return inst;
}

std::shared_ptr<KinematicIJ> MbD::ASMTdAngleIJy::mbdClassNew()
{
	return DAngleYIeqcJeqc::With();
}
