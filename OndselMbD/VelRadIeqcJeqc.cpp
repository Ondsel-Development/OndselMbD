#include "VelRadIeqcJeqc.h"
#include "EndFrameqct.h"

using namespace MbD;

MbD::VelRadIeqcJeqc::VelRadIeqcJeqc(EndFrmsptr frmi, EndFrmsptr frmj) : VelRadIeqcJec(frmi, frmj)
{
	assert(false);
}

std::shared_ptr<VelRadIeqcJeqc> MbD::VelRadIeqcJeqc::With()
{
	auto inst = std::make_shared<VelRadIeqcJeqc>();
	inst->initialize();
	return inst;
}

std::shared_ptr<VelRadIeqcJeqc> MbD::VelRadIeqcJeqc::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
	auto inst = std::make_shared<VelRadIeqcJeqc>(frmi, frmj);
	inst->initialize();
	return inst;
}

void MbD::VelRadIeqcJeqc::initialize()
{
	VelRadIeqcJec::initialize();
	pvIeJepXJ = FullRow<double>::With(3);
	pvIeJepEJ = FullRow<double>::With(4);
	pvIeJepXdotJ = FullRow<double>::With(3);
	pvIeJepEdotJ = FullRow<double>::With(4);
}

void MbD::VelRadIeqcJeqc::calcPostDynCorrectorIteration()
{
	VelRadIeqcJec::calcPostDynCorrectorIteration();
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

FRowDsptr MbD::VelRadIeqcJeqc::pvaluepEdotJ()
{
	return pvIeJepEdotJ;
}

FRowDsptr MbD::VelRadIeqcJeqc::pvaluepEJ()
{
	return pvIeJepEJ;
}

FRowDsptr MbD::VelRadIeqcJeqc::pvaluepXdotJ()
{
	return pvIeJepXdotJ;
}

FRowDsptr MbD::VelRadIeqcJeqc::pvaluepXJ()
{
	return pvIeJepXJ;
}
