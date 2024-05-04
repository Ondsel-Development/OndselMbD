#include "ForceBasicqcVector.h"
#include "PartFrame.h"

using namespace MbD;

std::shared_ptr<ForceBasicqcVector> MbD::ForceBasicqcVector::With()
{
	auto inst = std::make_shared<ForceBasicqcVector>();
	inst->initialize();
	return inst;
}

void MbD::ForceBasicqcVector::calcPostDynCorrectorIteration()
{
	//"rpep is not a constant for aMbDEndFrameqccq, qcs or qct."

	prOeOpET = std::static_pointer_cast<EndFrameqc>(endFrame)->prOeOpE->transpose();
}

void MbD::ForceBasicqcVector::fillAccICIterErroraFTO(FColDsptr col, FColDsptr aFTO)
{
	col->atplusFullColumn(iqX, aFTO);
	col->atplusFullColumn(iqE, (prOeOpET->timesFullColumn(aFTO)));
}

void MbD::ForceBasicqcVector::fillAccICIterJacobpFTOplam(SpMatDsptr mat, SpMatDsptr pFTOplam)
{
	assert(false);
}

void MbD::ForceBasicqcVector::fillDynErroraFTO(FColDsptr col, FColDsptr aFTO)
{
	col->atplusFullColumn(iqX, aFTO);
	col->atplusFullColumn(iqE, prOeOpET->timesFullColumn(aFTO));
}

void MbD::ForceBasicqcVector::fillpFpyaFTO(SpMatDsptr mat, FColDsptr aFTO)
{
	auto endFrmqc = std::static_pointer_cast<EndFrameqc>(endFrame);
	auto pprOeOpEpE = endFrmqc->pprOeOpEpE;
	for (size_t i = 0; i < 4; i++) {
		auto pprOeOpEpEi = pprOeOpEpE->at(i);
		auto mati = mat->at(iqE + i);
		for (size_t j = 0; j < 4; j++) {
			auto pprOeOpEpEij = pprOeOpEpEi->at(j);
			mati->atplusNumber(iqE + j, pprOeOpEpEij->dot(aFTO));
		}
	}
}

void MbD::ForceBasicqcVector::fillpFpypFTOpEjpartj(SpMatDsptr mat, FMatDsptr pFTOpEj, PartFrame* partj)
{
	auto iqEj = partj->iqE;
	mat->atandplusFullMatrix(iqX, iqEj, pFTOpEj);
	mat->atandplusFullMatrix(iqE, iqEj, prOeOpET->timesFullMatrix(pFTOpEj));
}

void MbD::ForceBasicqcVector::fillpFpypFTOpXjpartj(SpMatDsptr mat, FMatDsptr pFTOpXj, PartFrame* partj)
{
	auto iqXj = partj->iqX;
	mat->atandplusFullMatrix(iqX, iqXj, pFTOpXj);
	mat->atandplusFullMatrix(iqE, iqXj, prOeOpET->timesFullMatrix(pFTOpXj));
}

void MbD::ForceBasicqcVector::fillpFpypFTOpXjpFTOpEjpartj(SpMatDsptr mat, FMatDsptr pFTOpXj, FMatDsptr pFTOpEj, PartFrame* partj)
{
	fillpFpypFTOpXjpartj(mat, pFTOpXj, partj);
	fillpFpypFTOpEjpartj(mat, pFTOpEj, partj);
}

void MbD::ForceBasicqcVector::fillpFpydotpFTOpEdotjpartj(SpMatDsptr mat, FMatDsptr pFTOpEdotj, PartFrame* partj)
{
	auto iqEj = partj->iqE;
	mat->atandplusFullMatrix(iqX, iqEj, pFTOpEdotj);
	mat->atandplusFullMatrix(iqE, iqEj, prOeOpET->timesFullMatrix(pFTOpEdotj));
}

void MbD::ForceBasicqcVector::fillpFpydotpFTOpmudot(SpMatDsptr mat, SpMatDsptr pFTOpmudot)
{
	assert(false);
}

void MbD::ForceBasicqcVector::fillpFpydotpFTOpXdotjpartj(SpMatDsptr mat, FMatDsptr pFTOpXdotj, PartFrame* partj)
{
	auto iqXj = partj->iqX;
	mat->atandplusFullMatrix(iqX, iqXj, pFTOpXdotj);
	mat->atandplusFullMatrix(iqE, iqXj, prOeOpET->timesFullMatrix(pFTOpXdotj));
}

void MbD::ForceBasicqcVector::fillpFpydotpFTOpXdotjpFTOpEdotjpartj(SpMatDsptr mat, FMatDsptr pFTOpXdotj, FMatDsptr pFTOpEdotj, PartFrame* partj)
{
	fillpFpydotpFTOpXdotjpartj(mat, pFTOpXdotj, partj);
	fillpFpydotpFTOpEdotjpartj(mat, pFTOpEdotj, partj);
}

void MbD::ForceBasicqcVector::useEquationNumbers()
{
	ForceTorqueBasic::useEquationNumbers();
	iqX = std::static_pointer_cast<EndFrameqc>(endFrame)->iqX();
}
