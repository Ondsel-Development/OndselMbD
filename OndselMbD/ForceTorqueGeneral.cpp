#include "ForceTorqueGeneral.h"

using namespace MbD;

std::shared_ptr<ForceTorqueGeneral> MbD::ForceTorqueGeneral::OnFrmIandFrmJ(EndFrmsptr frmi, EndFrmsptr frmj)
{
	auto inst = std::make_shared<ForceTorqueGeneral>();
	inst->initialize();
	inst->onFrmIandFrmJ(frmi, frmj);
	return inst;
}

std::shared_ptr<ForceTorqueGeneral> MbD::ForceTorqueGeneral::OnFrmIandFrmJwrtFrmK(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk)
{
	auto inst = std::make_shared<ForceTorqueGeneral>();
	inst->initialize();
	inst->onFrmIandFrmJwrtFrmK(frmi, frmj, frmk);
	return inst;
}

void MbD::ForceTorqueGeneral::onFrmIandFrmJ(EndFrmsptr frmi, EndFrmsptr frmj)
{
	forceVector = ForceVector::OnFrmIandFrmJ(frmi, frmj);
	torqueVector = TorqueVector::OnFrmIandFrmJ(frmi, frmj);
}

void MbD::ForceTorqueGeneral::onFrmIandFrmJwrtFrmK(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk)
{
	efrmI = frmi;
	efrmJ = frmj;
	forceVector = ForceVector::OnFrmIandFrmJwrtFrmK(frmi, frmj, frmk);
	torqueVector = TorqueVector::OnFrmIandFrmJwrtFrmK(frmi, frmj, frmk);
}

void MbD::ForceTorqueGeneral::initializeGlobally()
{
	forceVector->initializeGlobally();
	torqueVector->initializeGlobally();
}

void MbD::ForceTorqueGeneral::initializeLocally()
{
	forceVector->initializeLocally();
	torqueVector->initializeLocally();
}

FColDsptr MbD::ForceTorqueGeneral::aFX() const
{
	return forceVector->getFTIeO();
}

FColDsptr MbD::ForceTorqueGeneral::aTX() const
{
	return torqueVector->getFTIeO();
}

void MbD::ForceTorqueGeneral::postAccICIteration()
{
	forceVector->postAccICIteration();
	torqueVector->postAccICIteration();
}

void MbD::ForceTorqueGeneral::postCollisionCorrectorIteration()
{
	forceVector->postCollisionCorrectorIteration();
	torqueVector->postCollisionCorrectorIteration();
}

void MbD::ForceTorqueGeneral::postCollisionPredictor()
{
	forceVector->postCollisionPredictor();
	torqueVector->postCollisionPredictor();
}

void MbD::ForceTorqueGeneral::postDynCorrectorIteration()
{
	forceVector->postDynCorrectorIteration();
	torqueVector->postDynCorrectorIteration();
}

void MbD::ForceTorqueGeneral::postDynOutput()
{
	forceVector->postDynOutput();
	torqueVector->postDynOutput();
}

void MbD::ForceTorqueGeneral::postDynPredictor()
{
	forceVector->postDynPredictor();
	torqueVector->postDynPredictor();
}

void MbD::ForceTorqueGeneral::postInput()
{
	forceVector->postInput();
	torqueVector->postInput();
}

void MbD::ForceTorqueGeneral::postStaticIteration()
{
	forceVector->postStaticIteration();
	torqueVector->postStaticIteration();
}

void MbD::ForceTorqueGeneral::preAccIC()
{
	forceVector->preAccIC();
	torqueVector->preAccIC();
}

void MbD::ForceTorqueGeneral::preDynOutput()
{
	forceVector->preDynOutput();
	torqueVector->preDynOutput();
}

void MbD::ForceTorqueGeneral::preStatic()
{
	forceVector->preStatic();
	torqueVector->preStatic();
}

void MbD::ForceTorqueGeneral::simUpdateAll()
{
	forceVector->simUpdateAll();
	torqueVector->simUpdateAll();
}

void MbD::ForceTorqueGeneral::torqueFunctions(FColsptr<Symsptr> col)
{
	torqueVector->functions(col);
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
	forceVector->fillDynError(col);
	torqueVector->fillDynError(col);
}

void MbD::ForceTorqueGeneral::fillpFpy(SpMatDsptr mat)
{
	forceVector->fillpFpy(mat);
	torqueVector->fillpFpy(mat);
}

void MbD::ForceTorqueGeneral::fillpFpydot(SpMatDsptr mat)
{
	forceVector->fillpFpydot(mat);
	torqueVector->fillpFpydot(mat);
}

void MbD::ForceTorqueGeneral::fillStaticError(FColDsptr col)
{
	forceVector->fillStaticError(col);
	torqueVector->fillStaticError(col);
}

void MbD::ForceTorqueGeneral::fillStaticJacob(SpMatDsptr mat)
{
	forceVector->fillStaticJacob(mat);
	torqueVector->fillStaticJacob(mat);
}

void MbD::ForceTorqueGeneral::forceFunctions(FColsptr<Symsptr> col)
{
	forceVector->functions(col);
}

void MbD::ForceTorqueGeneral::useEquationNumbers()
{
	forceVector->useEquationNumbers();
	torqueVector->useEquationNumbers();
}
