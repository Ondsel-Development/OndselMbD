#include "ForceBasiccComp.h"
#include "ForceTorqueActionComp.h"

using namespace MbD;

std::shared_ptr<ForceBasiccComp> MbD::ForceBasiccComp::With()
{
	auto inst = std::make_shared<ForceBasiccComp>();
	inst->initialize();
	return inst;
}

void MbD::ForceBasiccComp::calcPostDynCorrectorIteration()
{
	//"rpep is not a constant for aMbDEndFrameqccq, qcs or qct."
}

void MbD::ForceBasiccComp::fillAccICIterErroraFTO(FColDsptr col, FColDsptr aFTO)
{
	assert(false);
}

void MbD::ForceBasiccComp::fillAccICIterJacobpFTOplam(SpMatDsptr mat, SpMatDsptr pFTOplam)
{
	assert(false);
}

void MbD::ForceBasiccComp::fillDynErroraFTO(FColDsptr col, FColDsptr aFTO)
{
	assert(false);
}

void MbD::ForceBasiccComp::fillpFpyaFTO(SpMatDsptr mat, FColDsptr aFTO)
{
	assert(false);
}

void MbD::ForceBasiccComp::fillpFpypFTOpEjpartj(SpMatDsptr mat, FMatDsptr pFTOpEj, SpatialContainerFrame* partj)
{
	assert(false);
}

void MbD::ForceBasiccComp::fillpFpypFTOpXjpartj(SpMatDsptr mat, FMatDsptr pFTOpXj, SpatialContainerFrame* partj)
{
	assert(false);
}

void MbD::ForceBasiccComp::fillpFpypFTOpXjpFTOpEjpartj(SpMatDsptr mat, FMatDsptr pFTOpXj, FMatDsptr pFTOpEj, SpatialContainerFrame* partj)
{
	assert(false);
}

void MbD::ForceBasiccComp::fillpFpydotpFTOpEdotjpartj(SpMatDsptr mat, FMatDsptr pFTOpEdotj, SpatialContainerFrame* partj)
{
	assert(false);
}

void MbD::ForceBasiccComp::fillpFpydotpFTOpmudot(SpMatDsptr mat, SpMatDsptr pFTOpmudot)
{
	assert(false);
}

void MbD::ForceBasiccComp::fillpFpydotpFTOpXdotjpartj(SpMatDsptr mat, FMatDsptr pFTOpXdotj, SpatialContainerFrame* partj)
{
	assert(false);
}

void MbD::ForceBasiccComp::fillpFpydotpFTOpXdotjpFTOpEdotjpartj(SpMatDsptr mat, FMatDsptr pFTOpXdotj, FMatDsptr pFTOpEdotj, SpatialContainerFrame* partj)
{
	assert(false);
}

void MbD::ForceBasiccComp::useEquationNumbers()
{
	assert(false);
}

void MbD::ForceBasiccComp::fillAccICIterErroraFTOi(FColDsptr col, double aFTOi)
{
	//Do nothing.
}
