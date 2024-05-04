#include "KinematicDotIeJe.h"

using namespace MbD;

std::shared_ptr<KinematicDotIeJe> MbD::KinematicDotIeJe::With()
{
	auto inst = std::make_shared<KinematicDotIeJe>();
	inst->initialize();
	return inst;
}

std::shared_ptr<KinematicDotIeJe> MbD::KinematicDotIeJe::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
	auto inst = std::make_shared<KinematicDotIeJe>(frmi, frmj);
	inst->initialize();
	return inst;
}

bool MbD::KinematicDotIeJe::isKineIJ()
{
	return false;
}

bool MbD::KinematicDotIeJe::isKinedotIJ()
{
	return true;
}

FRowDsptr MbD::KinematicDotIeJe::pvaluepEdotI()
{
	assert(false);
	return FRowDsptr();
}

FRowDsptr MbD::KinematicDotIeJe::pvaluepEdotJ()
{
	assert(false);
	return FRowDsptr();
}

FRowDsptr MbD::KinematicDotIeJe::pvaluepEdotK()
{
	return FullRow<double>::With(0);
}

FRowDsptr MbD::KinematicDotIeJe::pvaluepXdotI()
{
	assert(false);
	return FRowDsptr();
}

FRowDsptr MbD::KinematicDotIeJe::pvaluepXdotJ()
{
	assert(false);
	return FRowDsptr();
}

FRowDsptr MbD::KinematicDotIeJe::pvaluepXdotK()
{
	return FullRow<double>::With(0);
}
