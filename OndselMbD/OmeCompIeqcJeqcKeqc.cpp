#include "OmeCompIeqcJeqcKeqc.h"
#include "EndFrameqc.h"

using namespace MbD;

std::shared_ptr<OmeCompIeqcJeqcKeqc> MbD::OmeCompIeqcJeqcKeqc::With()
{
	auto inst = std::make_shared<OmeCompIeqcJeqcKeqc>();
	inst->initialize();
	return inst;
}

std::shared_ptr<OmeCompIeqcJeqcKeqc> MbD::OmeCompIeqcJeqcKeqc::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
	auto inst = std::make_shared<OmeCompIeqcJeqcKeqc>(frmi, frmj);
	inst->initialize();
	return inst;
}

void MbD::OmeCompIeqcJeqcKeqc::initialize()
{
	OmeCompIeqcJecKeqc::initialize();
	pomeiIeJeKepEJ = FullRow<double>::With(4);
	pomeiIeJeKepEdotJ = FullRow<double>::With(4);
}

void MbD::OmeCompIeqcJeqcKeqc::calcPostDynCorrectorIteration()
{
	OmeCompIeqcJecKeqc::calcPostDynCorrectorIteration();
	auto efrmJqc = std::static_pointer_cast<EndFrameqc>(efrmJ);
	auto pomeIeJeOpEJ = efrmJqc->pomeOeOpE();
	auto pomeIeJeOpEdotJ = efrmJqc->pomeOeOpEdot();
	pomeiIeJeKepEJ = pomeIeJeOpEJ->dot(aAjOKe);
	pomeiIeJeKepEdotJ = pomeIeJeOpEdotJ->dot(aAjOKe);
}

FRowDsptr MbD::OmeCompIeqcJeqcKeqc::pvaluepEJ()
{
	return pomeiIeJeKepEJ;
}

FRowDsptr MbD::OmeCompIeqcJeqcKeqc::pvaluepEdotJ()
{
	return pomeiIeJeKepEdotJ;
}
