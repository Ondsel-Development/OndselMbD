#include "ASMTrIJ.h"
#include "DistIeqcJeqc.h"

using namespace MbD;

std::shared_ptr<ASMTrIJ> MbD::ASMTrIJ::With()
{
	auto inst = std::make_shared<ASMTrIJ>();
	inst->initialize();
	return inst;
}

std::shared_ptr<KinematicIeJe> MbD::ASMTrIJ::mbdClassNew()
{
	return DistIeqcJeqc::With();
}
