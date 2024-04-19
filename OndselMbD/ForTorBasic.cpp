#include "ForTorBasic.h"
#include "EndFramec.h"
#include "PartFrame.h"

using namespace MbD;

std::shared_ptr<ForTorBasic> MbD::ForTorBasic::With()
{
	auto inst = std::make_shared<ForTorBasic>();
	inst->initialize();
	return inst;
}

void MbD::ForTorBasic::fillAccICIterErroraFTO(FColDsptr col, FColDsptr aFTO)
{
	assert(false);
}

void MbD::ForTorBasic::fillAccICIterJacobpFTOplam(SpMatDsptr mat, SpMatDsptr pFTOplam)
{
	assert(false);
}

void MbD::ForTorBasic::fillDynErroraFTO(FColDsptr col, FColDsptr aFTO)
{
	assert(false);
}

void MbD::ForTorBasic::fillpFpyaFTO(SpMatDsptr mat, FColDsptr aFTO)
{
	assert(false);
}

void MbD::ForTorBasic::fillpFpypFTOpEjpartj(SpMatDsptr mat, FMatDsptr pFTOpEj, PartFrame* partj)
{
	assert(false);
}

void MbD::ForTorBasic::fillpFpypFTOpXjpartj(SpMatDsptr mat, FMatDsptr pFTOpXj, PartFrame* partj)
{
	assert(false);
}

void MbD::ForTorBasic::fillpFpypFTOpXjpFTOpEjpartj(SpMatDsptr mat, FMatDsptr pFTOpXj, FMatDsptr pFTOpEj, PartFrame* partj)
{
	assert(false);
}

void MbD::ForTorBasic::fillpFpydotpFTOpEdotjpartj(SpMatDsptr mat, FMatDsptr pFTOpEdotj, PartFrame* partj)
{
	assert(false);
}

void MbD::ForTorBasic::fillpFpydotpFTOpmudot(SpMatDsptr mat, SpMatDsptr pFTOpmudot)
{
	assert(false);
}

void MbD::ForTorBasic::fillpFpydotpFTOpXdotjpartj(SpMatDsptr mat, FMatDsptr pFTOpXdotj, PartFrame* partj)
{
	assert(false);
}

void MbD::ForTorBasic::fillpFpydotpFTOpXdotjpFTOpEdotjpartj(SpMatDsptr mat, FMatDsptr pFTOpXdotj, FMatDsptr pFTOpEdotj, PartFrame* partj)
{
	assert(false);
}

void MbD::ForTorBasic::useEquationNumbers()
{
	iqE = endFrame->getPartFrame()->iqE;
}

void MbD::ForTorBasic::fillAccICIterErroraFTOi(FColDsptr col, double aFTOi)
{
	assert(false);
}
