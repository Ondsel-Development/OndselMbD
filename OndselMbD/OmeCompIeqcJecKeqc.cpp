#include "OmeCompIeqcJecKeqc.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<OmeCompIeqcJecKeqc> MbD::OmeCompIeqcJecKeqc::With()
{
	auto inst = std::make_shared<OmeCompIeqcJecKeqc>();
	inst->initialize();
	return inst;
}

std::shared_ptr<OmeCompIeqcJecKeqc> MbD::OmeCompIeqcJecKeqc::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
	auto inst = std::make_shared<OmeCompIeqcJecKeqc>(frmi, frmj);
	inst->initialize();
	return inst;
}

void MbD::OmeCompIeqcJecKeqc::initialize()
{
	OmeCompIecJecKeqc::initialize();
	pomeiIeJeKepEI = FullRow<double>::With(4);
	pomeiIeJeKepEdotI = FullRow<double>::With(4);
}

void MbD::OmeCompIeqcJecKeqc::calcPostDynCorrectorIteration()
{
	OmeCompIecJecKeqc::calcPostDynCorrectorIteration();
	auto efrmIqc = std::static_pointer_cast<EndFrameqc>(efrmI);
	auto mpomeIeJeOpEI = efrmIqc->pomeOeOpE();
	auto mpomeIeJeOpEdotI = efrmIqc->pomeOeOpEdot();
	auto mAjOKe = aAjOKe->negated();
	pomeiIeJeKepEI = mpomeIeJeOpEI->dot(mAjOKe);
	pomeiIeJeKepEdotI = mpomeIeJeOpEdotI->dot(mAjOKe);
}

FRowDsptr MbD::OmeCompIeqcJecKeqc::pvaluepEI()
{
	return pomeiIeJeKepEI;
}

FRowDsptr MbD::OmeCompIeqcJecKeqc::pvaluepEdotI()
{
	return pomeiIeJeKepEdotI;
}
