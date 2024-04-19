#include "ForceTorqueGeneral.h"

using namespace MbD;

MbD::ForceTorqueGeneral::ForceTorqueGeneral(EndFrmsptr frmi, EndFrmsptr frmj)
{
	assert(false);
}

MbD::ForceTorqueGeneral::ForceTorqueGeneral(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk)
{
	assert(false);
}

std::shared_ptr<ForceTorqueGeneral> MbD::ForceTorqueGeneral::With(EndFrmsptr frmi, EndFrmsptr frmj)
{
	auto inst = std::make_shared<ForceTorqueGeneral>(frmi, frmj);
	inst->initialize();
	return inst;
}

std::shared_ptr<ForceTorqueGeneral> MbD::ForceTorqueGeneral::With(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk)
{
	auto inst = std::make_shared<ForceTorqueGeneral>(frmi, frmj, frmk);
	inst->initialize();
	return inst;
}

void MbD::ForceTorqueGeneral::initializeGlobally()
{
	forceVector->initializeGlobally();
	torqueVector->initializeGlobally();
}

void MbD::ForceTorqueGeneral::initializeLocally()
{
	assert(false);
}

FColDsptr MbD::ForceTorqueGeneral::aFX() const
{
	assert(false);
	return FColDsptr();
}

FColDsptr MbD::ForceTorqueGeneral::aTX() const
{
	assert(false);
	return FColDsptr();
}

void MbD::ForceTorqueGeneral::postAccICIteration()
{
	forceVector->postAccICIteration();
	torqueVector->postAccICIteration();
}

void MbD::ForceTorqueGeneral::postCollisionCorrectorIteration()
{
	assert(false);
}

void MbD::ForceTorqueGeneral::postCollisionPredictor()
{
	assert(false);
}

void MbD::ForceTorqueGeneral::postDynCorrectorIteration()
{
	assert(false);
}

void MbD::ForceTorqueGeneral::postDynOutput()
{
	assert(false);
}

void MbD::ForceTorqueGeneral::postDynPredictor()
{
	assert(false);
}

void MbD::ForceTorqueGeneral::postInput()
{
	assert(false);
}

void MbD::ForceTorqueGeneral::postStaticIteration()
{
	assert(false);
}

void MbD::ForceTorqueGeneral::preAccIC()
{
	assert(false);
}

void MbD::ForceTorqueGeneral::preDynOutput()
{
	assert(false);
}

void MbD::ForceTorqueGeneral::preStatic()
{
	assert(false);
}

void MbD::ForceTorqueGeneral::simUpdateAll()
{
	assert(false);
}

void MbD::ForceTorqueGeneral::torqueFunctions(FColDsptr col)
{
	assert(false);
}

void MbD::ForceTorqueGeneral::fillAccICIterError(FColDsptr col)
{
	forceVector->fillAccICIterError(col);
	torqueVector->fillAccICIterError(col);
}

void MbD::ForceTorqueGeneral::fillAccICIterJacob(SpMatDsptr mat)
{
	forceVector->fillAccICIterJacob(mat);
	torqueVector->fillAccICIterJacob(mat);
}

void MbD::ForceTorqueGeneral::fillDynError(FColDsptr col)
{
	assert(false);
}

void MbD::ForceTorqueGeneral::fillpFpy(SpMatDsptr mat)
{
	assert(false);
}

void MbD::ForceTorqueGeneral::fillpFpydot(SpMatDsptr mat)
{
	assert(false);
}

void MbD::ForceTorqueGeneral::fillStaticError(FColDsptr col)
{
	assert(false);
}

void MbD::ForceTorqueGeneral::fillStaticJacob(SpMatDsptr mat)
{
	assert(false);
}

void MbD::ForceTorqueGeneral::forceFunctions(FColDsptr col)
{
	assert(false);
}

void MbD::ForceTorqueGeneral::useEquationNumbers()
{
	forceVector->useEquationNumbers();
	torqueVector->useEquationNumbers();
}
