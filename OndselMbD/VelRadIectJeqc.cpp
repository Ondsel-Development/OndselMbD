#include "VelRadIectJeqc.h"

using namespace MbD;

MbD::VelRadIectJeqc::VelRadIectJeqc(EndFrmsptr frmi, EndFrmsptr frmj) : VelRadIecJeqc(frmi, frmj)
{
	assert(false);
}

std::shared_ptr<VelRadIectJeqc> MbD::VelRadIectJeqc::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
	auto inst = std::make_shared<VelRadIectJeqc>(frmi, frmj);
	inst->initialize();
	return inst;
}
