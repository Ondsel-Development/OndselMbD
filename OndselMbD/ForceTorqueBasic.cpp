#include "ForceTorqueBasic.h"
#include "EndFramec.h"
#include "PartFrame.h"

using namespace MbD;

std::shared_ptr<ForceTorqueBasic> MbD::ForceTorqueBasic::With()
{
	auto inst = std::make_shared<ForceTorqueBasic>();
	inst->initialize();
	return inst;
}

void MbD::ForceTorqueBasic::fillAccICIterErroraFTO(FColDsptr col, FColDsptr aFTO)
{
	assert(false);
}

void MbD::ForceTorqueBasic::fillAccICIterJacobpFTOplam(SpMatDsptr mat, SpMatDsptr pFTOplam)
{
	assert(false);
}

void MbD::ForceTorqueBasic::fillDynErroraFTO(FColDsptr col, FColDsptr aFTO)
{
	assert(false);
}

void MbD::ForceTorqueBasic::fillpFpyaFTO(SpMatDsptr mat, FColDsptr aFTO)
{
	assert(false);
}

void MbD::ForceTorqueBasic::fillpFpypFTOpEjpartj(SpMatDsptr mat, FMatDsptr pFTOpEj, PartFrame* partj)
{
	assert(false);
}

void MbD::ForceTorqueBasic::fillpFpypFTOpXjpartj(SpMatDsptr mat, FMatDsptr pFTOpXj, PartFrame* partj)
{
	assert(false);
}

void MbD::ForceTorqueBasic::fillpFpypFTOpXjpFTOpEjpartj(SpMatDsptr mat, FMatDsptr pFTOpXj, FMatDsptr pFTOpEj, PartFrame* partj)
{
	assert(false);
}

void MbD::ForceTorqueBasic::fillpFpydotpFTOpEdotjpartj(SpMatDsptr mat, FMatDsptr pFTOpEdotj, PartFrame* partj)
{
	assert(false);
}

void MbD::ForceTorqueBasic::fillpFpydotpFTOpmudot(SpMatDsptr mat, SpMatDsptr pFTOpmudot)
{
	assert(false);
}

void MbD::ForceTorqueBasic::fillpFpydotpFTOpXdotjpartj(SpMatDsptr mat, FMatDsptr pFTOpXdotj, PartFrame* partj)
{
	assert(false);
}

void MbD::ForceTorqueBasic::fillpFpydotpFTOpXdotjpFTOpEdotjpartj(SpMatDsptr mat, FMatDsptr pFTOpXdotj, FMatDsptr pFTOpEdotj, PartFrame* partj)
{
	assert(false);
}

void MbD::ForceTorqueBasic::useEquationNumbers()
{
	iqE = endFrame->getPartFrame()->iqE;
}

void MbD::ForceTorqueBasic::fillAccICIterErroraFTOi(FColDsptr col, double aFTOi)
{
	assert(false);
}

void MbD::ForceTorqueBasic::fillpFpydotpFOpmudot(SpMatDsptr mat, SpMatDsptr pFOpmudot)
{
	assert(false);
}

void MbD::ForceTorqueBasic::endFramefollowEndFrame(EndFrmsptr frmj, EndFrmsptr frmi)
{
	endFrame = frmj->followEndFrame(frmi);
}
