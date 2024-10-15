#include "TorqueBasiccVector.h"
#include "PartFrame.h"

using namespace MbD;

std::shared_ptr<TorqueBasiccVector> MbD::TorqueBasiccVector::With()
{
	auto inst = std::make_shared<TorqueBasiccVector>();
	inst->initialize();
	return inst;
}

void MbD::TorqueBasiccVector::calcPostDynCorrectorIteration()
{
	//Do nothing.
}

void MbD::TorqueBasiccVector::fillAccICIterErroraFTO(FColDsptr col, FColDsptr aFTO)
{
	//Do nothing.
}

void MbD::TorqueBasiccVector::fillAccICIterJacobpFTOplam(SpMatDsptr mat, SpMatDsptr pFTOplam)
{
	assert(false);
}

void MbD::TorqueBasiccVector::fillDynErroraFTO(FColDsptr col, FColDsptr aFTO)
{
	//Do nothing.
}

void MbD::TorqueBasiccVector::fillpFpyaFTO(SpMatDsptr mat, FColDsptr aFTO)
{
	//Do nothing.
}

void MbD::TorqueBasiccVector::fillpFpypFTOpEjpartj(SpMatDsptr mat, FMatDsptr pFTOpEj, SpatialContainerFrame* partj)
{
	//Do nothing.
}

void MbD::TorqueBasiccVector::fillpFpypFTOpXjpartj(SpMatDsptr mat, FMatDsptr pFTOpXj, SpatialContainerFrame* partj)
{
	assert(false);
}

void MbD::TorqueBasiccVector::fillpFpypFTOpXjpFTOpEjpartj(SpMatDsptr mat, FMatDsptr pFTOpXj, FMatDsptr pFTOpEj, SpatialContainerFrame* partj)
{
	//Do nothing.
}

void MbD::TorqueBasiccVector::fillpFpydotpFTOpEdotjpartj(SpMatDsptr mat, FMatDsptr pFTOpEdotj, SpatialContainerFrame* partj)
{
	assert(false);
}

void MbD::TorqueBasiccVector::fillpFpydotpFTOpmudot(SpMatDsptr mat, SpMatDsptr pFTOpmudot)
{
	assert(false);
}

void MbD::TorqueBasiccVector::fillpFpydotpFTOpXdotjpartj(SpMatDsptr mat, FMatDsptr pFTOpXdotj, SpatialContainerFrame* partj)
{
	assert(false);
}

void MbD::TorqueBasiccVector::fillpFpydotpFTOpXdotjpFTOpEdotjpartj(SpMatDsptr mat, FMatDsptr pFTOpXdotj, FMatDsptr pFTOpEdotj, SpatialContainerFrame* partj)
{
	assert(false);
}
