#include "ASMTAtPointJoint.h"

using namespace MbD;

std::shared_ptr<ASMTAtPointJoint> MbD::ASMTAtPointJoint::With()
{
	auto inst = std::make_shared<ASMTAtPointJoint>();
	inst->initialize();
	return inst;
}
