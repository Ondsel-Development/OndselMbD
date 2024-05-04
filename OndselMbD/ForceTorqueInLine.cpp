#include "ForceTorqueInLine.h"
#include "ForceTorqueFunction.h"

using namespace MbD;

std::shared_ptr<ForceTorqueInLine> MbD::ForceTorqueInLine::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
	auto inst = std::make_shared<ForceTorqueInLine>(frmi, frmj);
	//inst->initialize();	//Need to pass arguments.
	inst->forceInLine = ForceTorqueActReactInLine::ForceOnFrmIandFrmJ(frmi, frmj);
	inst->torqueInLine = ForceTorqueActReactInLine::TorqueOnFrmIandFrmJ(frmi, frmj);
	return inst;
}

void MbD::ForceTorqueInLine::initializeGlobally()
{
	forceInLine->initializeGlobally();
	torqueInLine->initializeGlobally();
}

void MbD::ForceTorqueInLine::initializeLocally()
{
	forceInLine->initializeLocally();
	torqueInLine->initializeLocally();
}

void MbD::ForceTorqueInLine::postDynPredictor()
{
	forceInLine->postDynPredictor();
	torqueInLine->postDynPredictor();
}

void MbD::ForceTorqueInLine::postInput()
{
	forceInLine->postInput();
	torqueInLine->postInput();
}

void MbD::ForceTorqueInLine::postStaticIteration()
{
	assert(false);
}

void MbD::ForceTorqueInLine::preAccIC()
{
	forceInLine->preAccIC();
	torqueInLine->preAccIC();
}

void MbD::ForceTorqueInLine::preDynOutput()
{
	forceInLine->preDynOutput();
	torqueInLine->preDynOutput();
}

void MbD::ForceTorqueInLine::preStatic()
{
	assert(false);
}

void MbD::ForceTorqueInLine::simUpdateAll()
{
	assert(false);
}

void MbD::ForceTorqueInLine::fillAccICIterError(FColDsptr col)
{
	forceInLine->fillAccICIterError(col);
	torqueInLine->fillAccICIterError(col);
}

void MbD::ForceTorqueInLine::fillAccICIterJacob(SpMatDsptr mat)
{
	forceInLine->fillAccICIterJacob(mat);
	torqueInLine->fillAccICIterJacob(mat);
}

void MbD::ForceTorqueInLine::fillDynError(FColDsptr col)
{
	forceInLine->fillDynError(col);
	torqueInLine->fillDynError(col);
}

void MbD::ForceTorqueInLine::fillpFpy(SpMatDsptr mat)
{
	forceInLine->fillpFpy(mat);
	torqueInLine->fillpFpy(mat);
}

void MbD::ForceTorqueInLine::fillpFpydot(SpMatDsptr mat)
{
	forceInLine->fillpFpydot(mat);
	torqueInLine->fillpFpydot(mat);
}

void MbD::ForceTorqueInLine::fillStaticError(FColDsptr col)
{
	assert(false);
}

void MbD::ForceTorqueInLine::fillStaticJacob(SpMatDsptr mat)
{
	assert(false);
}

void MbD::ForceTorqueInLine::useEquationNumbers()
{
	forceInLine->useEquationNumbers();
	torqueInLine->useEquationNumbers();
}

void MbD::ForceTorqueInLine::tension(Symsptr tensionFunc)
{
	forceInLine->getforTorFunction()->setformula(tensionFunc);
}

void MbD::ForceTorqueInLine::twist(Symsptr twistFunc)
{
	torqueInLine->getforTorFunction()->setformula(twistFunc);
}

FColDsptr MbD::ForceTorqueInLine::aFX() const
{
	return forceInLine->getFTIeO();
}

FColDsptr MbD::ForceTorqueInLine::aTX() const
{
	return torqueInLine->getFTIeO();
}

void MbD::ForceTorqueInLine::postAccICIteration()
{
	forceInLine->postAccICIteration();
	torqueInLine->postAccICIteration();
}

void MbD::ForceTorqueInLine::postCollisionCorrectorIteration()
{
	assert(false);
}

void MbD::ForceTorqueInLine::postCollisionPredictor()
{
	assert(false);
}

void MbD::ForceTorqueInLine::postDynCorrectorIteration()
{
	forceInLine->postDynCorrectorIteration();
	torqueInLine->postDynCorrectorIteration();
}

void MbD::ForceTorqueInLine::postDynOutput()
{
	forceInLine->postDynOutput();
	torqueInLine->postDynOutput();
}
