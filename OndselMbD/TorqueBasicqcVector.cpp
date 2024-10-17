#include "TorqueBasicqcVector.h"
#include "PartFrame.h"

using namespace MbD;

std::shared_ptr<TorqueBasicqcVector> MbD::TorqueBasicqcVector::With()
{
	auto inst = std::make_shared<TorqueBasicqcVector>();
	inst->initialize();
	return inst;
}

void MbD::TorqueBasicqcVector::calcPostDynCorrectorIteration()
{
	twoBT = endFrame->markerFrame->partFrame->qE()->aB->transpose()->times(2.0);
}

void MbD::TorqueBasicqcVector::fillAccICIterErroraFTO(FColDsptr col, FColDsptr aFTO)
{
	col->atplusFullColumn(iqE, (twoBT->timesFullColumn(aFTO)));
}

void MbD::TorqueBasicqcVector::fillAccICIterJacobpFTOplam(SpMatDsptr mat, SpMatDsptr pFTOplam)
{
	assert(false);
}

void MbD::TorqueBasicqcVector::fillDynErroraFTO(FColDsptr col, FColDsptr aFTO)
{
	col->atplusFullColumn(iqE, twoBT->timesFullColumn(aFTO));
}

void MbD::TorqueBasicqcVector::fillpFpyaFTO(SpMatDsptr mat, FColDsptr aFTO)
{
	mat->atandplusFullMatrix(iqE, iqE, (EulerParameters<double>::pBTpEtimesColumn(aFTO->times(2.0))));
}

void MbD::TorqueBasicqcVector::fillpFpypFTOpEjpartj(SpMatDsptr mat, FMatDsptr pFTOpEj, SpatialContainerFrame* partj)
{
	mat->atandplusFullMatrix(iqE, partj->iqE(), (twoBT->timesFullMatrix(pFTOpEj)));
}

void MbD::TorqueBasicqcVector::fillpFpypFTOpXjpartj(SpMatDsptr mat, FMatDsptr pFTOpXj, SpatialContainerFrame* partj)
{
	assert(false);
}

void MbD::TorqueBasicqcVector::fillpFpypFTOpXjpFTOpEjpartj(SpMatDsptr mat, FMatDsptr pFTOpXj, FMatDsptr pFTOpEj, SpatialContainerFrame* partj)
{
	mat->atandplusFullMatrix(iqE, partj->iqX(), twoBT->timesFullMatrix(pFTOpXj));
	mat->atandplusFullMatrix(iqE, partj->iqE(), twoBT->timesFullMatrix(pFTOpEj));
}

void MbD::TorqueBasicqcVector::fillpFpydotpFTOpEdotjpartj(SpMatDsptr mat, FMatDsptr pFTOpEdotj, SpatialContainerFrame* partj)
{
	assert(false);
}

void MbD::TorqueBasicqcVector::fillpFpydotpFTOpmudot(SpMatDsptr mat, SpMatDsptr pFTOpmudot)
{
	assert(false);
}

void MbD::TorqueBasicqcVector::fillpFpydotpFTOpXdotjpartj(SpMatDsptr mat, FMatDsptr pFTOpXdotj, SpatialContainerFrame* partj)
{
	assert(false);
}

void MbD::TorqueBasicqcVector::fillpFpydotpFTOpXdotjpFTOpEdotjpartj(SpMatDsptr mat, FMatDsptr pFTOpXdotj, FMatDsptr pFTOpEdotj, SpatialContainerFrame* partj)
{
	assert(false);
}

void MbD::TorqueBasicqcVector::useEquationNumbers()
{
	iqE = std::static_pointer_cast<EndFrameqc>(endFrame)->iqE();
}
