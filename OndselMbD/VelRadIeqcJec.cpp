#include "VelRadIeqcJec.h"
#include "EndFrameqc.h"

using namespace MbD;

MbD::VelRadIeqcJec::VelRadIeqcJec(EndFrmsptr frmi, EndFrmsptr frmj) : VelRadIecJec(frmi, frmj)
{
	assert(false);
}

std::shared_ptr<VelRadIeqcJec> MbD::VelRadIeqcJec::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
	auto inst = std::make_shared<VelRadIeqcJec>(frmi, frmj);
	inst->initialize();
	return inst;
}

void MbD::VelRadIeqcJec::initialize()
{
	VelRadIecJec::initialize();
	pvIeJepXI = FullRow<double>::With(3);
	pvIeJepEI = FullRow<double>::With(4);
	pvIeJepXdotI = FullRow<double>::With(3);
	pvIeJepEdotI = FullRow<double>::With(4);
}

void MbD::VelRadIeqcJec::calcPostDynCorrectorIteration()
{
	VelRadIecJec::calcPostDynCorrectorIteration();
	if (rIeJe == 0.0) return;
	auto muIeJeO = uIeJeO->negated();
	auto efrmqcI = std::static_pointer_cast<EndFrameqc>(frmI);
	auto mprIeJeOpEI = efrmqcI->prOeOpE;
	auto mprIeJeOpEIT = mprIeJeOpEI->transpose();
	auto mpvIeJeOpEIT = efrmqcI->pvOeOpE()->transpose();
	auto muIeJeOT = muIeJeO->transpose();
	auto prIeJepXI = muIeJeOT;
	auto prIeJepEI = muIeJeOT->timesFullMatrix(mprIeJeOpEI);
	for (size_t i = 0; i < 3; i++) {
		pvIeJepXI->atput(i, (-vIeJe*prIeJepXI->at(i) - vIeJeO->at(i)) / rIeJe);
	}
	for (size_t i = 0; i < 4; i++) {
		pvIeJepEI->atput(i, (-vIeJe*prIeJepEI->at(i) - mpvIeJeOpEIT->at(i)->dot(rIeJeO) - mprIeJeOpEIT->at(i)->dot(vIeJeO)) / rIeJe);
	}
	pvIeJepXdotI = prIeJepXI;
	pvIeJepEdotI = prIeJepEI;
}

FRowDsptr MbD::VelRadIeqcJec::pvaluepEdotI()
{
	return pvIeJepEdotI;
}

FRowDsptr MbD::VelRadIeqcJec::pvaluepEI()
{
	return pvIeJepEI;
}

FRowDsptr MbD::VelRadIeqcJec::pvaluepXdotI()
{
	return pvIeJepXdotI;
}

FRowDsptr MbD::VelRadIeqcJec::pvaluepXI()
{
	return pvIeJepXI;
}
