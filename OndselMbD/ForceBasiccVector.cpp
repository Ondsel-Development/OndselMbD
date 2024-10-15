#include "ForceBasiccVector.h"
#include "ForceBasicqcVector.h"
#include "SpatialContainerFrame.h"
#include "EndFrameqct.h"
#include "EndFrameqc.h"
#include "EndFramect.h"
#include "EndFramec.h"

using namespace MbD;

std::shared_ptr<ForceBasiccVector> MbD::ForceBasiccVector::With()
{
    auto inst = std::make_shared<ForceBasiccVector>();
    inst->initialize();
    return inst;
}

std::shared_ptr<ForceBasiccVector> MbD::ForceBasiccVector::With(EndFrmsptr efrmI)
{
    if (std::dynamic_pointer_cast<EndFrameqct>(efrmI)) {
        assert(false);
    }
    else if (std::dynamic_pointer_cast<EndFrameqc>(efrmI)) {
        auto forVecI = ForceBasicqcVector::With();
        forVecI->endFrame = efrmI;
        return forVecI;
    }
    else if (std::dynamic_pointer_cast<EndFramect>(efrmI)) {
        assert(false);
    }
    else if (std::dynamic_pointer_cast<EndFramec>(efrmI)) {
        auto forVecI = ForceBasiccVector::With();
        forVecI->endFrame = efrmI;
        return forVecI;
    }
    assert(false);
    return std::shared_ptr<ForceBasiccVector>();
}

void MbD::ForceBasiccVector::calcPostDynCorrectorIteration()
{
    //"rpep is not a constant for aMbDEndFrameqccq, qcs or qct."
}

void MbD::ForceBasiccVector::fillAccICIterErroraFTO(FColDsptr col, FColDsptr aFTO)
{
    //Do nothing.
}

void MbD::ForceBasiccVector::fillAccICIterJacobpFTOplam(SpMatDsptr mat, SpMatDsptr pFTOplam)
{
    assert(false);
}

void MbD::ForceBasiccVector::fillDynErroraFTO(FColDsptr col, FColDsptr aFTO)
{
    //Do nothing.
}

void MbD::ForceBasiccVector::fillpFpyaFTO(SpMatDsptr mat, FColDsptr aFTO)
{
    //Do nothing.
}

void MbD::ForceBasiccVector::fillpFpypFTOpEjpartj(SpMatDsptr mat, FMatDsptr pFTOpEj, SpatialContainerFrame* partj)
{
    //Do nothing.
}

void MbD::ForceBasiccVector::fillpFpypFTOpXjpartj(SpMatDsptr mat, FMatDsptr pFTOpXj, SpatialContainerFrame* partj)
{
    //Do nothing.
}

void MbD::ForceBasiccVector::fillpFpypFTOpXjpFTOpEjpartj(SpMatDsptr mat, FMatDsptr pFTOpXj, FMatDsptr pFTOpEj, SpatialContainerFrame* partj)
{
    fillpFpypFTOpXjpartj(mat, pFTOpXj, partj);
    fillpFpypFTOpEjpartj(mat, pFTOpEj, partj);
}

void MbD::ForceBasiccVector::fillpFpydotpFTOpEdotjpartj(SpMatDsptr mat, FMatDsptr pFTOpEdotj, SpatialContainerFrame* partj)
{
    //Do nothing.
}

void MbD::ForceBasiccVector::fillpFpydotpFTOpmudot(SpMatDsptr mat, SpMatDsptr pFTOpmudot)
{
    assert(false);
}

void MbD::ForceBasiccVector::fillpFpydotpFTOpXdotjpartj(SpMatDsptr mat, FMatDsptr pFTOpXdotj, SpatialContainerFrame* partj)
{
    //Do nothing.
}

void MbD::ForceBasiccVector::fillpFpydotpFTOpXdotjpFTOpEdotjpartj(SpMatDsptr mat, FMatDsptr pFTOpXdotj, FMatDsptr pFTOpEdotj, SpatialContainerFrame* partj)
{
    fillpFpydotpFTOpXdotjpartj(mat, pFTOpXdotj, partj);
    fillpFpydotpFTOpEdotjpartj(mat, pFTOpEdotj, partj);
}

void MbD::ForceBasiccVector::useEquationNumbers()
{
    //Do nothing.
}
