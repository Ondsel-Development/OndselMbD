#include "ForTorActionInLine.h"
#include "ForTorFunction.h"
#include "ForceBasicqcVector.h"
#include "TorqueBasicVector.h"

using namespace MbD;

std::shared_ptr<ForTorActionInLine> MbD::ForTorActionInLine::With()
{
	auto inst = std::make_shared<ForTorActionInLine>();
	inst->initialize();
	return inst;
}

void MbD::ForTorActionInLine::initialize()
{
	distIeJe = DistIeqcJeqc::With();
	ForTorAction::initialize();
}

void MbD::ForTorActionInLine::calcPostDynCorrectorIteration()
{
	auto uIeJeO = distIeJe->uIeJeO;
	auto tension = forTorFunction->forTor();
	aFTIeO = uIeJeO->times(tension);
}

void MbD::ForTorActionInLine::fillAccICIterError(FColDsptr col)
{
	forTorBasicI->fillAccICIterErroraFTO(col, aFTIeO);
}

void MbD::ForTorActionInLine::fillAccICIterJacob(SpMatDsptr mat)
{
	forTorBasicI->fillAccICIterJacob(mat);
}

void MbD::ForTorActionInLine::fillDynError(FColDsptr col)
{
	forTorBasicI->fillDynErroraFTO(col, aFTIeO);
}

void MbD::ForTorActionInLine::fillpFpy(SpMatDsptr mat)
{
	auto forTor = forTorFunction->forTor();
	forTorBasicI->fillpFpyaFTO(mat, aFTIeO);
	auto block = [&](FMatDsptr puIeJeOpXi, FMatDsptr puIeJeOpEi, PartFrame* partFramei) -> void {
		forTorBasicI->fillpFpypFTOpXjpFTOpEjpartj(mat, puIeJeOpXi->times(forTor), puIeJeOpEi->times(forTor), partFramei); };
	block(distIeJe->puIeJeOpXI(), distIeJe->puIeJeOpEI(), distIeJe->partFrameI());
	block(distIeJe->puIeJeOpXJ(), distIeJe->puIeJeOpEJ(), distIeJe->partFrameJ());

	auto block2 = [&](std::shared_ptr<std::vector<std::shared_ptr<MbDSymbolicFunction>>> functions, 
		FColDsptr pFTpfunctions) -> void {
		for (size_t i = 0; i < functions->size(); i++) {
			fillpFpypFTpfunctionfunction(mat, pFTpfunctions->at(i), functions->at(i));
		}
		};
	block2(forTorFunction->kineIJs, forTorFunction->pFTpkineIJs());
	block2(forTorFunction->kinedotIJs, forTorFunction->pFTpkinedotIJs());
	block2(forTorFunction->jointActions, forTorFunction->pFTpJtActs());
}

void MbD::ForTorActionInLine::fillpFpypFTpfunctionfunction(SpMatDsptr mat, double pFTpfunction, Symsptr function)
{
	auto uIeJeO = distIeJe->uIeJeO;
	auto block = [&](FRowDsptr pvaluepXi,
		FRowDsptr pvaluepEi,
		PartFrame* partFramei) -> void {
			if (pvaluepXi->empty()) {
				if (pvaluepEi->empty()) {
					//Do nothing.
				}
				else {
					forTorBasicI->fillpFpypFTOpEjpartj(mat, FullMatrix<double>::colTimesRowTimesScalar(uIeJeO, pvaluepEi, pFTpfunction), partFramei);
				}
			}
			else {
				if (pvaluepEi->empty()) {
					forTorBasicI->fillpFpypFTOpXjpartj(mat, FullMatrix<double>::colTimesRowTimesScalar(uIeJeO, pvaluepXi, pFTpfunction), partFramei);
				}
				else {
					forTorBasicI->fillpFpypFTOpXjpFTOpEjpartj(mat,
						FullMatrix<double>::colTimesRowTimesScalar(uIeJeO, pvaluepXi, pFTpfunction),
						FullMatrix<double>::colTimesRowTimesScalar(uIeJeO, pvaluepEi, pFTpfunction),
						partFramei);
				};
			}
		};
	auto mdbfunc = std::static_pointer_cast<MbDSymbolicFunction>(function);
	block(mdbfunc->pvaluepXI(), mdbfunc->pvaluepEI(), mdbfunc->partFrameI());
	block(mdbfunc->pvaluepXJ(), mdbfunc->pvaluepEJ(), mdbfunc->partFrameJ());
	block(mdbfunc->pvaluepXK(), mdbfunc->pvaluepEK(), mdbfunc->partFrameK());
}

void MbD::ForTorActionInLine::fillpFpydot(SpMatDsptr mat)
{
	auto uIeJeO = distIeJe->uIeJeO;
	auto kinedotIJs = forTorFunction->kinedotIJs;
	auto jointActions = forTorFunction->jointActions;
	auto pFTpkinedotIJs = forTorFunction->pFTpkinedotIJs();
	auto pFTpJtActs = forTorFunction->pFTpJtActs();
	for (size_t i = 0; i < kinedotIJs->size(); i++) {
		fillpFpydotpFTpfunctionfunction(mat, pFTpkinedotIJs->at(i), kinedotIJs->at(i));
	}
	for (size_t i = 0; i < jointActions->size(); i++) {
		forTorBasicI->fillpFpydotpFTOpmudot(mat, SparseMatrix<double>::colTimesRowTimesScalar(uIeJeO, jointActions->at(i)->pvalueplam(), -pFTpJtActs->at(i)));
	}
}

void MbD::ForTorActionInLine::fillpFpydotpFTpfunctionfunction(SpMatDsptr mat, double pFTpfunction, Symsptr function)
{
	auto uIeJeO = distIeJe->uIeJeO;
	auto block = [&](FRowDsptr pvaluepXdoti,
		FRowDsptr pvaluepEdoti,
		PartFrame* partFramei) -> void {
			if (pvaluepXdoti->empty()) {
				if (pvaluepEdoti->empty()) {
					//Do nothing.
				}
				else {
					forTorBasicI->fillpFpydotpFTOpEdotjpartj(mat, FullMatrix<double>::colTimesRowTimesScalar(uIeJeO, pvaluepEdoti, pFTpfunction), partFramei);
				}
			}
			else {
				if (pvaluepEdoti->empty()) {
					forTorBasicI->fillpFpydotpFTOpXdotjpartj(mat, FullMatrix<double>::colTimesRowTimesScalar(uIeJeO, pvaluepXdoti, pFTpfunction), partFramei);
				}
				else {
					forTorBasicI->fillpFpydotpFTOpXdotjpFTOpEdotjpartj(mat,
						FullMatrix<double>::colTimesRowTimesScalar(uIeJeO, pvaluepXdoti, pFTpfunction),
						FullMatrix<double>::colTimesRowTimesScalar(uIeJeO, pvaluepEdoti, pFTpfunction),
						partFramei);
				};
			}
		};
	auto mdbfunc = std::static_pointer_cast<MbDSymbolicFunction>(function);
	block(mdbfunc->pvaluepXdotI(), mdbfunc->pvaluepEdotI(), mdbfunc->partFrameI());
	block(mdbfunc->pvaluepXdotJ(), mdbfunc->pvaluepEdotJ(), mdbfunc->partFrameJ());
	block(mdbfunc->pvaluepXdotK(), mdbfunc->pvaluepEdotK(), mdbfunc->partFrameK());
}

void MbD::ForTorActionInLine::forceOnFrmIandFrmJ(EndFrmsptr eFrmI, EndFrmsptr eFrmJ)
{
	forTorBasicI = ForceBasicqcVector::With();
	forTorBasicI->parent = this;
	forTorBasicI->endFrame = eFrmI;
	distIeJe->withFrmIfrmJ(eFrmI, eFrmJ);
}

void MbD::ForTorActionInLine::initializeGlobally()
{
	distIeJe->initializeGlobally();
	ForTorAction::initializeGlobally();
}

void MbD::ForTorActionInLine::initializeLocally()
{
	distIeJe->initializeLocally();
	ForTorAction::initializeLocally();
}

void MbD::ForTorActionInLine::postAccICIteration()
{
	distIeJe->postAccICIteration();
	forTorFunction->postAccICIteration();
	forTorBasicI->postAccICIteration();
	ForTorAction::postAccICIteration();
}

void MbD::ForTorActionInLine::postCollisionCorrectorIteration()
{
	distIeJe->postCollisionCorrectorIteration();
	forTorFunction->postCollisionCorrectorIteration();
	forTorBasicI->postCollisionCorrectorIteration();
	ForTorAction::postCollisionCorrectorIteration();
}

void MbD::ForTorActionInLine::postCollisionPredictor()
{
	distIeJe->postCollisionPredictor();
	forTorFunction->postCollisionPredictor();
	forTorBasicI->postCollisionPredictor();
	ForTorAction::postCollisionPredictor();
}

void MbD::ForTorActionInLine::postDynCorrectorIteration()
{
	distIeJe->postDynCorrectorIteration();
	forTorFunction->postDynCorrectorIteration();
	forTorBasicI->postDynCorrectorIteration();
	ForTorAction::postDynCorrectorIteration();
}

void MbD::ForTorActionInLine::postDynOutput()
{
	distIeJe->postDynOutput();
	forTorFunction->postDynOutput();
	forTorBasicI->postDynOutput();
	ForTorAction::postDynOutput();
}

void MbD::ForTorActionInLine::postDynPredictor()
{
	distIeJe->postDynPredictor();
	forTorFunction->postDynPredictor();
	forTorBasicI->postDynPredictor();
	ForTorAction::postDynPredictor();
}

void MbD::ForTorActionInLine::postInput()
{
	distIeJe->postInput();
	forTorFunction->postInput();
	forTorBasicI->postInput();
	ForTorAction::postInput();
}

void MbD::ForTorActionInLine::postStaticIteration()
{
	distIeJe->postStaticIteration();
	forTorFunction->postStaticIteration();
	forTorBasicI->postStaticIteration();
	ForTorAction::postStaticIteration();
}

void MbD::ForTorActionInLine::preAccIC()
{
	distIeJe->preAccIC();
	forTorFunction->preAccIC();
	forTorBasicI->preAccIC();
	ForTorAction::preAccIC();
}

void MbD::ForTorActionInLine::preDynOutput()
{
	distIeJe->preDynOutput();
	forTorFunction->preDynOutput();
	forTorBasicI->preDynOutput();
	ForTorAction::preDynOutput();
}

void MbD::ForTorActionInLine::preStatic()
{
	distIeJe->preStatic();
	forTorFunction->preStatic();
	forTorBasicI->preStatic();
	ForTorAction::preStatic();
}

void MbD::ForTorActionInLine::simUpdateAll()
{
	distIeJe->simUpdateAll();
	forTorFunction->simUpdateAll();
	forTorBasicI->simUpdateAll();
	ForTorAction::simUpdateAll();
}

std::shared_ptr<ForTorFunction> MbD::ForTorActionInLine::tension()
{
	return forTorFunction;
}

void MbD::ForTorActionInLine::torqueOnFrmIandFrmJ(EndFrmsptr eFrmI, EndFrmsptr eFrmJ)
{
	forTorBasicI = TorqueBasicVector::With();
	forTorBasicI->parent = this;
	forTorBasicI->endFrame = eFrmI;
	distIeJe->withFrmIfrmJ(eFrmI, eFrmJ);
}

FColDsptr MbD::ForTorActionInLine::uIeJeO()
{
	return distIeJe->uIeJeO;
}

void MbD::ForTorActionInLine::useEquationNumbers()
{
	distIeJe->useEquationNumbers();
	forTorFunction->useEquationNumbers();
	forTorBasicI->useEquationNumbers();
}

FColDsptr MbD::ForTorActionInLine::getFTIeO() const
{
	return aFTIeO;
}
