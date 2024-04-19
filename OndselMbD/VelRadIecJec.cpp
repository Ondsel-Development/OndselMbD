#include "VelRadIecJec.h"
#include "EndFrameqc.h"

using namespace MbD;

MbD::VelRadIecJec::VelRadIecJec(EndFrmsptr frmi, EndFrmsptr frmj) : KinematicDotIeJe(frmi, frmj)
{
	assert(false);
}

std::shared_ptr<VelRadIecJec> MbD::VelRadIecJec::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
	auto inst = std::make_shared<VelRadIecJec>(frmi, frmj);
	inst->initialize();
	return inst;
}

void MbD::VelRadIecJec::calcPostDynCorrectorIteration()
{
	rIeJeO = frmJ->rOeO->minusFullColumn(frmI->rOeO);
	rIeJe = rIeJeO->length();
	if (rIeJe == 0.0) return;
	uIeJeO = rIeJeO->times(1.0 / rIeJe);
	vIeJeO = frmJ->vOeO()->minusFullColumn(frmI->vOeO());
	vIeJe = vIeJeO->dot(uIeJeO);
}

double MbD::VelRadIecJec::value()
{
	return vIeJe;
}
