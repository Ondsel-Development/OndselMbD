#include "TorqueBasicVector.h"
#include "PartFrame.h"

using namespace MbD;

std::shared_ptr<TorqueBasicVector> MbD::TorqueBasicVector::With()
{
	auto inst = std::make_shared<TorqueBasicVector>();
	inst->initialize();
	return inst;
}

void MbD::TorqueBasicVector::calcPostDynCorrectorIteration()
{
	twoBT = endFrame->markerFrame->partFrame->qE()->aB->transpose()->times(2.0);
}

void MbD::TorqueBasicVector::fillAccICIterErroraFTO(FColDsptr col, FColDsptr aFTO)
{
	col->atplusFullColumn(iqE, (twoBT->timesFullColumn(aFTO)));
}

void MbD::TorqueBasicVector::fillAccICIterJacobpFTOplam(SpMatDsptr mat, SpMatDsptr pFTOplam)
{
	assert(false);
}

void MbD::TorqueBasicVector::fillDynErroraFTO(FColDsptr col, FColDsptr aFTO)
{
	col->atplusFullColumn(iqE, twoBT->timesFullColumn(aFTO));
}

void MbD::TorqueBasicVector::fillpFpyaFTO(SpMatDsptr mat, FColDsptr aFTO)
{
	mat->atandplusFullMatrix(iqE, iqE, (EulerParameters<double>::pBTpEtimesColumn(aFTO->times(2.0))));
}

void MbD::TorqueBasicVector::fillpFpypFTOpEjpartj(SpMatDsptr mat, FMatDsptr pFTOpEj, SpatialContainerFrame* partj)
{
	mat->atandplusFullMatrix(iqE, partj->iqE(), (twoBT->timesFullMatrix(pFTOpEj)));
}

void MbD::TorqueBasicVector::fillpFpypFTOpXjpartj(SpMatDsptr mat, FMatDsptr pFTOpXj, SpatialContainerFrame* partj)
{
	assert(false);
}

void MbD::TorqueBasicVector::fillpFpypFTOpXjpFTOpEjpartj(SpMatDsptr mat, FMatDsptr pFTOpXj, FMatDsptr pFTOpEj, SpatialContainerFrame* partj)
{
	mat->atandplusFullMatrix(iqE, partj->iqX(), twoBT->timesFullMatrix(pFTOpXj));
	mat->atandplusFullMatrix(iqE, partj->iqE(), twoBT->timesFullMatrix(pFTOpEj));
}

void MbD::TorqueBasicVector::fillpFpydotpFTOpEdotjpartj(SpMatDsptr mat, FMatDsptr pFTOpEdotj, SpatialContainerFrame* partj)
{
	assert(false);
}

void MbD::TorqueBasicVector::fillpFpydotpFTOpmudot(SpMatDsptr mat, SpMatDsptr pFTOpmudot)
{
	assert(false);
}

void MbD::TorqueBasicVector::fillpFpydotpFTOpXdotjpartj(SpMatDsptr mat, FMatDsptr pFTOpXdotj, SpatialContainerFrame* partj)
{
	assert(false);
}

void MbD::TorqueBasicVector::fillpFpydotpFTOpXdotjpFTOpEdotjpartj(SpMatDsptr mat, FMatDsptr pFTOpXdotj, FMatDsptr pFTOpEdotj, SpatialContainerFrame* partj)
{
	assert(false);
}
