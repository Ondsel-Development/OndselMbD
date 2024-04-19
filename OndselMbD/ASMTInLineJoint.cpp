
#include "ASMTInLineJoint.h"

using namespace MbD;

std::shared_ptr<ASMTInLineJoint> MbD::ASMTInLineJoint::With()
{
	auto inst = std::make_shared<ASMTInLineJoint>();
	inst->initialize();
	return inst;
}
