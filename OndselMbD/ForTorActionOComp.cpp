#include "ForTorActionOComp.h"
#include "ForTorBasic.h"

using namespace MbD;

std::shared_ptr<ForTorActionOComp> MbD::ForTorActionOComp::With()
{
	auto inst = std::make_shared<ForTorActionOComp>();
	inst->initialize();
	return inst;
}

void MbD::ForTorActionOComp::calcPostDynCorrectorIteration()
{
	assert(false);
}

void MbD::ForTorActionOComp::fillAccICIterError(FColDsptr col)
{
	forTorBasicI->fillAccICIterErroraFTOi(col, aFTIeOi);
}

void MbD::ForTorActionOComp::fillAccICIterJacob(SpMatDsptr mat)
{
	assert(false);
}

void MbD::ForTorActionOComp::fillDynError(FColDsptr col)
{
	assert(false);
}

void MbD::ForTorActionOComp::fillpFpy(SpMatDsptr mat)
{
	assert(false);
}

void MbD::ForTorActionOComp::fillpFpypFTpfunctionfunction(SpMatDsptr mat, Symsptr pFTpfunction, Symsptr function)
{
	assert(false);
}

void MbD::ForTorActionOComp::fillpFpydot(SpMatDsptr mat)
{
	assert(false);
}

void MbD::ForTorActionOComp::fillpFpydotpFTpfunctionfunction(SpMatDsptr mat, Symsptr pFTpfunction, Symsptr function)
{
	assert(false);
}

void MbD::ForTorActionOComp::forceOnFrmIandFrmJ(EndFrmsptr eFrmI, EndFrmsptr eFrmJ)
{
	assert(false);
}

void MbD::ForTorActionOComp::torqueOnFrmIandFrmJ(EndFrmsptr eFrmI, EndFrmsptr eFrmJ)
{
	assert(false);
}

FColDsptr MbD::ForTorActionOComp::getFTIeO() const
{
	return FColDsptr();
}

void MbD::ForTorActionOComp::postDynPredictor()
{
	assert(false);
}
