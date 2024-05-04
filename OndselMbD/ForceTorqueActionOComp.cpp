#include "ForceTorqueActionOComp.h"
#include "ForceTorqueBasic.h"
#include "ForceBasicqcComp.h"

using namespace MbD;

std::shared_ptr<ForceTorqueActionOComp> MbD::ForceTorqueActionOComp::With()
{
	auto inst = std::make_shared<ForceTorqueActionOComp>();
	inst->initialize();
	return inst;
}

void MbD::ForceTorqueActionOComp::calcPostDynCorrectorIteration()
{
	assert(false);
}

void MbD::ForceTorqueActionOComp::fillAccICIterError(FColDsptr col)
{
	forTorBasicI->fillAccICIterErroraFTOi(col, aFTIeOi);
}

void MbD::ForceTorqueActionOComp::fillAccICIterJacob(SpMatDsptr mat)
{
	assert(false);
}

void MbD::ForceTorqueActionOComp::fillDynError(FColDsptr col)
{
	assert(false);
}

void MbD::ForceTorqueActionOComp::fillpFpy(SpMatDsptr mat)
{
	assert(false);
}

void MbD::ForceTorqueActionOComp::fillpFpypFTpfunctionfunction(SpMatDsptr mat, double pFTpfunction, Symsptr function)
{
	assert(false);
}

void MbD::ForceTorqueActionOComp::fillpFpydot(SpMatDsptr mat)
{
	assert(false);
}

void MbD::ForceTorqueActionOComp::fillpFpydotpFTpfunctionfunction(SpMatDsptr mat, double pFTpfunction, Symsptr function)
{
	assert(false);
}

void MbD::ForceTorqueActionOComp::forceOnFrmIandFrmJ(EndFrmsptr eFrmI, EndFrmsptr eFrmJ)
{
	assert(false);
}

void MbD::ForceTorqueActionOComp::torqueOnFrmIandFrmJ(EndFrmsptr eFrmI, EndFrmsptr eFrmJ)
{
	assert(false);
}

FColDsptr MbD::ForceTorqueActionOComp::getFTIeO() const
{
	return FColDsptr();
}

void MbD::ForceTorqueActionOComp::forceOnFrmIaxis(EndFrmsptr frmi, size_t axis)
{
	forTorBasicI = ForceBasicqcComp::With();
	forTorBasicI->parent = this;
	forTorBasicI->endFrame = frmi;
}

void MbD::ForceTorqueActionOComp::torqueOnFrmIaxis(EndFrmsptr frmi, size_t axis)
{
	assert(false);
}

void MbD::ForceTorqueActionOComp::postDynPredictor()
{
	assert(false);
}
