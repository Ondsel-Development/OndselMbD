#include "ForTorActionKComp.h"
#include "ForTorBasic.h"
#include "ForTorFunction.h"

using namespace MbD;

std::shared_ptr<ForTorActionKComp> MbD::ForTorActionKComp::With()
{
	auto inst = std::make_shared<ForTorActionKComp>();
	inst->initialize();
	return inst;
}

void MbD::ForTorActionKComp::calcPostDynCorrectorIteration()
{
	assert(false);
}

void MbD::ForTorActionKComp::fillAccICIterError(FColDsptr col)
{
	forTorBasicI->fillAccICIterErroraFTO(col, aFTIeO);
}

void MbD::ForTorActionKComp::fillAccICIterJacob(SpMatDsptr mat)
{
	auto jointActions = forTorFunction->jointActions;
		auto pFTpJtActs = forTorFunction->pFTpJtActs();
		for (size_t i = 0; jointActions->size(); i++) {
			auto jointAction = jointActions->at(i);
			auto pFTpJtAct = pFTpJtActs->at(i);
			forTorBasicI->fillAccICIterJacobpFTOplam(mat, SparseMatrix<double>::colTimesRowTimesScalar(aAjOKe, jointAction->pvalueplam(), pFTpJtAct));
		}
}

void MbD::ForTorActionKComp::fillDynError(FColDsptr col)
{
	assert(false);
}

void MbD::ForTorActionKComp::fillpFpy(SpMatDsptr mat)
{
	assert(false);
}

void MbD::ForTorActionKComp::fillpFpypFTpfunctionfunction(SpMatDsptr mat, Symsptr pFTpfunction, Symsptr function)
{
	assert(false);
}

void MbD::ForTorActionKComp::fillpFpydot(SpMatDsptr mat)
{
	assert(false);
}

void MbD::ForTorActionKComp::fillpFpydotpFTpfunctionfunction(SpMatDsptr mat, Symsptr pFTpfunction, Symsptr function)
{
	assert(false);
}

void MbD::ForTorActionKComp::forceOnFrmIandFrmJ(EndFrmsptr eFrmI, EndFrmsptr eFrmJ)
{
	assert(false);
}

void MbD::ForTorActionKComp::torqueOnFrmIandFrmJ(EndFrmsptr eFrmI, EndFrmsptr eFrmJ)
{
	assert(false);
}

FColDsptr MbD::ForTorActionKComp::getFTIeO() const
{
	return aFTIeO;
}
