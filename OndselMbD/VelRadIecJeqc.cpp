#include "VelRadIecJeqc.h"
#include "EndFrameqct.h"

using namespace MbD;

std::shared_ptr<VelRadIecJeqc> MbD::VelRadIecJeqc::With()
{
	auto inst = std::make_shared<VelRadIecJeqc>();
	inst->initialize();
	return inst;
}

std::shared_ptr<VelRadIecJeqc> MbD::VelRadIecJeqc::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
	auto inst = std::make_shared<VelRadIecJeqc>(frmi, frmj);
	inst->initialize();
	return inst;
}

void MbD::VelRadIecJeqc::initialize()
{
	VelRadIecJec::initialize();
	pvIeJepXJ = FullRow<double>::With(3);
	pvIeJepEJ = FullRow<double>::With(4);
	pvIeJepXdotJ = FullRow<double>::With(3);
	pvIeJepEdotJ = FullRow<double>::With(4);
}

void MbD::VelRadIecJeqc::calcPostDynCorrectorIteration()
{
	VelRadIecJec::calcPostDynCorrectorIteration();
	if (rIeJe == 0.0) return;
	auto efrmqcJ = std::static_pointer_cast<EndFrameqc>(efrmJ);
	auto prIeJeOpEJ = efrmqcJ->prOeOpE;
	auto prIeJeOpEJT = prIeJeOpEJ->transpose();
	auto pvIeJeOpEJT = efrmqcJ->pvOeOpE()->transpose();
	auto uIeJeOT = uIeJeO->transpose();
	auto prIeJepXJ = uIeJeOT;
	auto prIeJepEJ = uIeJeOT->timesFullMatrix(prIeJeOpEJ);
	for (size_t i = 0; i < 3; i++) {
		pvIeJepXJ->atput(i, (vIeJeO->at(i) - vIeJe * prIeJepXJ->at(i)) / rIeJe);
	}
	for (size_t i = 0; i < 4; i++) {
		pvIeJepEJ->atput(i, (pvIeJeOpEJT->at(i)->dot(rIeJeO) + prIeJeOpEJT->at(i)->dot(vIeJeO) - vIeJe * prIeJepEJ->at(i)) / rIeJe);
	}
	pvIeJepXdotJ = prIeJepXJ;
	pvIeJepEdotJ = prIeJepEJ;
}

FRowDsptr MbD::VelRadIecJeqc::pvaluepEdotJ()
{
	return pvIeJepEdotJ;
}

FRowDsptr MbD::VelRadIecJeqc::pvaluepEJ()
{
	return pvIeJepEJ;
}

FRowDsptr MbD::VelRadIecJeqc::pvaluepXdotJ()
{
	return pvIeJepXdotJ;
}

FRowDsptr MbD::VelRadIecJeqc::pvaluepXJ()
{
	return pvIeJepXJ;
}
