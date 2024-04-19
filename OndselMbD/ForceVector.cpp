#include "ForceVector.h"

using namespace MbD;

MbD::ForceVector::ForceVector(EndFrmsptr frmi, EndFrmsptr frmj)
{
	assert(false);
}

MbD::ForceVector::ForceVector(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk)
{
	assert(false);
}

std::shared_ptr<ForceVector> MbD::ForceVector::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
	auto inst = std::make_shared<ForceVector>(frmi, frmj);
	inst->initialize();
	return inst;
}

std::shared_ptr<ForceVector> MbD::ForceVector::With(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk)
{
	auto inst = std::make_shared<ForceVector>(frmi, frmj, frmk);
	inst->initialize();
	return inst;
}
