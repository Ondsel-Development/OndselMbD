#include "VelRadIeqctJeqc.h"

using namespace MbD;

MbD::VelRadIeqctJeqc::VelRadIeqctJeqc(EndFrmsptr frmi, EndFrmsptr frmj) : VelRadIeqcJeqc(frmi, frmj)
{
	assert(false);
}

std::shared_ptr<VelRadIeqctJeqc> MbD::VelRadIeqctJeqc::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
	auto inst = std::make_shared<VelRadIeqctJeqc>(frmi, frmj);
	inst->initialize();
	return inst;
}
