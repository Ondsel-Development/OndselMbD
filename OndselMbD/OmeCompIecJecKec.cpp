#include "OmeCompIecJecKec.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<OmeCompIecJecKec> MbD::OmeCompIecJecKec::With()
{
	auto inst = std::make_shared<OmeCompIecJecKec>();
	inst->initialize();
	return inst;
}

std::shared_ptr<OmeCompIecJecKec> MbD::OmeCompIecJecKec::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
	auto inst = std::make_shared<OmeCompIecJecKec>(frmi, frmj);
	inst->initialize();
	return inst;
}

void MbD::OmeCompIecJecKec::withFrmIfrmJfrmKaxis(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk, size_t axis)
{
	efrmI = frmi;
	efrmJ = frmj;
	efrmK = frmk;
	axisK = axis;
}

double MbD::OmeCompIecJecKec::value()
{
	return omeiIeJeKe;
}

void MbD::OmeCompIecJecKec::calcPostDynCorrectorIteration()
{
	KinematicDotIeJe::calcPostDynCorrectorIteration();
	aAjOKe = efrmK->aAjOe(axisK);
	auto efrmIqc = std::static_pointer_cast<EndFrameqc>(efrmI);
	auto efrmJqc = std::static_pointer_cast<EndFrameqc>(efrmJ);
	omeIeJeO = efrmJqc->omeOeO()->minusFullColumn(efrmIqc->omeOeO());
	omeiIeJeKe = aAjOKe->dot(omeIeJeO);
}
