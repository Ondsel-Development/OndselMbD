#include "ASMTvIJ.h"
#include "Units.h"

using namespace MbD;

std::shared_ptr<ASMTvIJ> MbD::ASMTvIJ::With()
{
	auto inst = std::make_shared<ASMTvIJ>();
	inst->initialize();
	return inst;
}

std::shared_ptr<KinematicIJ> MbD::ASMTvIJ::mbdClassNew()
{
	return std::shared_ptr<KinematicIJ>();
}

void MbD::ASMTvIJ::createMbD()
{
	assert(false);
}

double MbD::ASMTvIJ::asmtUnit()
{
	return asmtUnits()->velocity;
}
