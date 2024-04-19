#include "ForTorActReactInLine.h"
#include "MarkerFrame.h"
#include "ForTorActionInLine.h"
#include "ForceBasicqcVector.h"
#include "TorqueBasicVector.h"
#include "ForTorFunction.h"
#include "Constant.h"

using namespace MbD;

std::shared_ptr<ForTorActReactInLine> MbD::ForTorActReactInLine::With()
{
	auto inst = std::make_shared<ForTorActReactInLine>();
	inst->initialize();
	return inst;
}

void MbD::ForTorActReactInLine::initialize()
{
	forTorAction = ForTorActionInLine::With();
}

std::shared_ptr<ForTorActReactInLine> MbD::ForTorActReactInLine::ForceOnFrmIandFrmJ(EndFrmsptr eFrmI, EndFrmsptr eFrmJ)
{
	auto forTorActReactInLine = ForTorActReactInLine::With();
	forTorActReactInLine->forceOnFrmIandFrmJ(eFrmI, eFrmJ);
	return forTorActReactInLine;
}

std::shared_ptr<ForTorActReactInLine> MbD::ForTorActReactInLine::TorqueOnFrmIandFrmJ(EndFrmsptr eFrmI, EndFrmsptr eFrmJ)
{
	auto forTorActReactInLine = ForTorActReactInLine::With();
	forTorActReactInLine->torqueOnFrmIandFrmJ(eFrmI, eFrmJ);
	return forTorActReactInLine;
}

void MbD::ForTorActReactInLine::calcPostDynCorrectorIteration()
{
	auto forTorActionInLine = std::static_pointer_cast<ForTorActionInLine>(forTorAction);
	aFTJeO = forTorActionInLine->aFTIeO->negated();
}

void MbD::ForTorActReactInLine::fillAccICIterError(FColDsptr col)
{
	forTorAction->fillAccICIterError(col);
	forTorBasicJ->fillAccICIterErroraFTO(col, aFTJeO);
}

void MbD::ForTorActReactInLine::fillAccICIterJacob(SpMatDsptr mat)
{
	forTorAction->fillAccICIterJacob(mat);
	forTorBasicJ->fillAccICIterJacob(mat);
}

void MbD::ForTorActReactInLine::fillDynError(FColDsptr col)
{
	forTorAction->fillDynError(col);
	forTorBasicJ->fillDynErroraFTO(col, aFTJeO);
}

void MbD::ForTorActReactInLine::fillpFpy(SpMatDsptr mat)
{
	auto forTorActionInLine = std::static_pointer_cast<ForTorActionInLine>(forTorAction);
	forTorActionInLine->fillpFpy(mat);
	auto distIeJe = forTorActionInLine->distIeJe;
	auto tension = forTorActionInLine->tension();
	auto mforTor = -tension->forTor();
	forTorBasicJ->fillpFpyaFTO(mat, aFTJeO);
	auto block = [&](FMatDsptr puIeJeOpXi, FMatDsptr puIeJeOpEi, PartFrame* partFramei) -> void {
		forTorBasicJ->fillpFpypFTOpXjpFTOpEjpartj(mat, puIeJeOpXi->times(mforTor), puIeJeOpEi->times(mforTor), partFramei); };
	block(distIeJe->puIeJeOpXI(), distIeJe->puIeJeOpEI(), distIeJe->partFrameI());
	block(distIeJe->puIeJeOpXJ(), distIeJe->puIeJeOpEJ(), distIeJe->partFrameJ());

	auto block2 = [&](std::shared_ptr<std::vector<std::shared_ptr<MbDSymbolicFunction>>> functions,
		FColDsptr pFTpfunctions) -> void {
			for (size_t i = 0; i < functions->size(); i++) {
				fillpFpypFTpfunctionfunction(mat, -pFTpfunctions->at(i), functions->at(i));
			}
		};
	block2(tension->kineIJs, tension->pFTpkineIJs());
	block2(tension->kinedotIJs, tension->pFTpkinedotIJs());
	block2(tension->jointActions, tension->pFTpJtActs());
}

void MbD::ForTorActReactInLine::fillpFpypFTpfunctionfunction(SpMatDsptr mat, double pFTpfunction, Symsptr function)
{
	auto uIeJeO = std::static_pointer_cast<ForTorActionInLine>(forTorAction)->uIeJeO();
	auto block = [&](FRowDsptr pvaluepXi,
		FRowDsptr pvaluepEi,
		PartFrame* partFramei) -> void {
			if (pvaluepXi->empty()) {
				if (pvaluepEi->empty()) {
					//Do nothing.
				}
				else {
					forTorBasicJ->fillpFpypFTOpEjpartj(mat, FullMatrix<double>::colTimesRowTimesScalar(uIeJeO, pvaluepEi, pFTpfunction), partFramei);
				}
			}
			else {
				if (pvaluepEi->empty()) {
					forTorBasicJ->fillpFpypFTOpXjpartj(mat, FullMatrix<double>::colTimesRowTimesScalar(uIeJeO, pvaluepXi, pFTpfunction), partFramei);
				}
				else {
					forTorBasicJ->fillpFpypFTOpXjpFTOpEjpartj(mat,
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

void MbD::ForTorActReactInLine::fillpFpydot(SpMatDsptr mat)
{
	forTorAction->fillpFpydot(mat);
	auto forTorActionInLine = std::static_pointer_cast<ForTorActionInLine>(forTorAction);
	auto distIeJe = forTorActionInLine->distIeJe;
	auto uIeJeO = distIeJe->uIeJeO;
	auto tension = forTorActionInLine->tension();
	auto kinedotIJs = tension->kinedotIJs;
	auto jointActions = tension->jointActions;
	auto pFTpkinedotIJs = tension->pFTpkinedotIJs();
	auto pFTpJtActs = tension->pFTpJtActs();
	for (size_t i = 0; i < kinedotIJs->size(); i++) {
		fillpFpydotpFTpfunctionfunction(mat, -pFTpkinedotIJs->at(i), kinedotIJs->at(i));
	}
	for (size_t i = 0; i < jointActions->size(); i++) {
		forTorBasicJ->fillpFpydotpFTOpmudot(mat, SparseMatrix<double>::colTimesRowTimesScalar(uIeJeO, jointActions->at(i)->pvalueplam(), -pFTpJtActs->at(i)));
	}
}

void MbD::ForTorActReactInLine::fillpFpydotpFTpfunctionfunction(SpMatDsptr mat, double pFTpfunction, Symsptr function)
{
	auto uIeJeO = std::static_pointer_cast<ForTorActionInLine>(forTorAction)->uIeJeO();
	auto block = [&](FRowDsptr pvaluepXdoti,
		FRowDsptr pvaluepEdoti,
		PartFrame* partFramei) -> void {
			if (pvaluepXdoti->empty()) {
				if (pvaluepEdoti->empty()) {
					//Do nothing.
				}
				else {
					forTorBasicJ->fillpFpydotpFTOpEdotjpartj(mat, FullMatrix<double>::colTimesRowTimesScalar(uIeJeO, pvaluepEdoti, pFTpfunction), partFramei);
				}
			}
			else {
				if (pvaluepEdoti->empty()) {
					forTorBasicJ->fillpFpydotpFTOpXdotjpartj(mat, FullMatrix<double>::colTimesRowTimesScalar(uIeJeO, pvaluepXdoti, pFTpfunction), partFramei);
				}
				else {
					forTorBasicJ->fillpFpydotpFTOpXdotjpFTOpEdotjpartj(mat,
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

void MbD::ForTorActReactInLine::forceOnFrmIandFrmJ(EndFrmsptr eFrmI, EndFrmsptr eFrmJ)
{
	forTorAction->forceOnFrmIandFrmJ(eFrmI, eFrmJ);
	forTorBasicJ = ForceBasicqcVector::With();
	forTorBasicJ->parent = this;
	forTorBasicJ->endFrame = eFrmJ;
}

void MbD::ForTorActReactInLine::initializeGlobally()
{
	forTorAction->initializeGlobally();
	forTorBasicJ->initializeGlobally();
}

void MbD::ForTorActReactInLine::initializeLocally()
{
	forTorAction->initializeLocally();
	forTorBasicJ->initializeLocally();
}

void MbD::ForTorActReactInLine::postAccICIteration()
{
	forTorAction->postAccICIteration();
	forTorBasicJ->postAccICIteration();
	ForTorActReact::postAccICIteration();
}

void MbD::ForTorActReactInLine::postCollisionCorrectorIteration()
{
	forTorAction->postCollisionCorrectorIteration();
	forTorBasicJ->postCollisionCorrectorIteration();
	ForTorActReact::postCollisionCorrectorIteration();
}

void MbD::ForTorActReactInLine::postCollisionPredictor()
{
	forTorAction->postCollisionPredictor();
	forTorBasicJ->postCollisionPredictor();
	ForTorActReact::postCollisionPredictor();
}

void MbD::ForTorActReactInLine::postDynCorrectorIteration()
{
	forTorAction->postDynCorrectorIteration();
	forTorBasicJ->postDynCorrectorIteration();
	ForTorActReact::postDynCorrectorIteration();
}

void MbD::ForTorActReactInLine::postDynOutput()
{
	forTorAction->postDynOutput();
	forTorBasicJ->postDynOutput();
	ForTorActReact::postDynOutput();
}

void MbD::ForTorActReactInLine::postDynPredictor()
{
	forTorAction->postDynPredictor();
	forTorBasicJ->postDynPredictor();
	ForTorActReact::postDynPredictor();
}

void MbD::ForTorActReactInLine::postInput()
{
	forTorAction->postInput();
	forTorBasicJ->postInput();
	ForTorActReact::postInput();
}

void MbD::ForTorActReactInLine::postStaticIteration()
{
	forTorAction->postStaticIteration();
	forTorBasicJ->postStaticIteration();
	ForTorActReact::postStaticIteration();
}

void MbD::ForTorActReactInLine::preAccIC()
{
	forTorAction->preAccIC();
	forTorBasicJ->preAccIC();
	ForTorActReact::preAccIC();
}

void MbD::ForTorActReactInLine::preDynOutput()
{
	forTorAction->preDynOutput();
	forTorBasicJ->preDynOutput();
	ForTorActReact::preDynOutput();
}

void MbD::ForTorActReactInLine::preStatic()
{
	forTorAction->preStatic();
	forTorBasicJ->preStatic();
	ForTorActReact::preStatic();
}

void MbD::ForTorActReactInLine::simUpdateAll()
{
	forTorAction->simUpdateAll();
	forTorBasicJ->simUpdateAll();
	ForTorActReact::simUpdateAll();
}

void MbD::ForTorActReactInLine::torqueOnFrmIandFrmJ(EndFrmsptr eFrmI, EndFrmsptr eFrmJ)
{
	forTorAction->torqueOnFrmIandFrmJ(eFrmI, eFrmJ);
	forTorBasicJ = TorqueBasicVector::With();
	forTorBasicJ->parent = this;
	forTorBasicJ->endFrame = eFrmJ;
}
