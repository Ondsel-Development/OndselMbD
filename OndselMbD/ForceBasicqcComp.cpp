#include "ForceBasicqcComp.h"
#include "ForceTorqueActionComp.h"

using namespace MbD;

std::shared_ptr<ForceBasicqcComp> MbD::ForceBasicqcComp::With()
{
	auto inst = std::make_shared<ForceBasicqcComp>();
	inst->initialize();
	return inst;
}

void MbD::ForceBasicqcComp::calcPostDynCorrectorIteration()
{
	//"rpep is not a constant for aMbDEndFrameqccq, qcs or qct."

	auto efrmqc = std::static_pointer_cast<EndFrameqc>(endFrame);
	auto axis = static_cast<ForceTorqueActionComp*>(parent)->axis;
	prOeOaxispET = efrmqc->prOeOpE->at(axis)->transpose();
}

void MbD::ForceBasicqcComp::fillAccICIterErroraFTO(FColDsptr col, FColDsptr aFTO)
{
	assert(false);
}

void MbD::ForceBasicqcComp::fillAccICIterJacobpFTOplam(SpMatDsptr mat, SpMatDsptr pFTOplam)
{
	assert(false);
}

void MbD::ForceBasicqcComp::fillDynErroraFTO(FColDsptr col, FColDsptr aFTO)
{
	assert(false);
}

void MbD::ForceBasicqcComp::fillpFpyaFTO(SpMatDsptr mat, FColDsptr aFTO)
{
	assert(false);
}

void MbD::ForceBasicqcComp::fillpFpypFTOpEjpartj(SpMatDsptr mat, FMatDsptr pFTOpEj, SpatialContainerFrame* partj)
{
	assert(false);
}

void MbD::ForceBasicqcComp::fillpFpypFTOpXjpartj(SpMatDsptr mat, FMatDsptr pFTOpXj, SpatialContainerFrame* partj)
{
	assert(false);
}

void MbD::ForceBasicqcComp::fillpFpypFTOpXjpFTOpEjpartj(SpMatDsptr mat, FMatDsptr pFTOpXj, FMatDsptr pFTOpEj, SpatialContainerFrame* partj)
{
	assert(false);
}

void MbD::ForceBasicqcComp::fillpFpydotpFTOpEdotjpartj(SpMatDsptr mat, FMatDsptr pFTOpEdotj, SpatialContainerFrame* partj)
{
	assert(false);
}

void MbD::ForceBasicqcComp::fillpFpydotpFTOpmudot(SpMatDsptr mat, SpMatDsptr pFTOpmudot)
{
	assert(false);
}

void MbD::ForceBasicqcComp::fillpFpydotpFTOpXdotjpartj(SpMatDsptr mat, FMatDsptr pFTOpXdotj, SpatialContainerFrame* partj)
{
	assert(false);
}

void MbD::ForceBasicqcComp::fillpFpydotpFTOpXdotjpFTOpEdotjpartj(SpMatDsptr mat, FMatDsptr pFTOpXdotj, FMatDsptr pFTOpEdotj, SpatialContainerFrame* partj)
{
	assert(false);
}

void MbD::ForceBasicqcComp::useEquationNumbers()
{
	assert(false);
}

void MbD::ForceBasicqcComp::fillAccICIterErroraFTOi(FColDsptr col, double aFTOi)
{
	col->atplusNumber(iqXaxis, aFTOi);
	col->atplusFullColumn(iqE, (prOeOaxispET->times(aFTOi)));
}
