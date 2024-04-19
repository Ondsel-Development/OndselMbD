#include "TorqueVector.h"

using namespace MbD;

MbD::TorqueVector::TorqueVector(EndFrmsptr frmi, EndFrmsptr frmj)
{
}

MbD::TorqueVector::TorqueVector(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk)
{
}

std::shared_ptr<TorqueVector> MbD::TorqueVector::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
	auto inst = std::make_shared<TorqueVector>(frmi, frmj);
	inst->initialize();
	return inst;
}

std::shared_ptr<TorqueVector> MbD::TorqueVector::With(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk)
{
	auto inst = std::make_shared<TorqueVector>(frmi, frmj, frmk);
	inst->initialize();
	return inst;
}
