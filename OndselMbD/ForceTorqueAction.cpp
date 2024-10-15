#include "ForceTorqueAction.h"
#include "MarkerFrame.h"
#include "ForceTorqueFunction.h"
#include "ForceBasicqcVector.h"
#include "TorqueBasiccVector.h"

using namespace MbD;

MbD::ForceTorqueAction::ForceTorqueAction(size_t count)
{
	assert(false);
}

std::shared_ptr<ForceTorqueAction> MbD::ForceTorqueAction::With(size_t count)
{
	auto inst = std::make_shared<ForceTorqueAction>(count);
	inst->initialize();
	return inst;
}

void MbD::ForceTorqueAction::initialize()
{
	forTorFunction = ForceTorqueFunction::With();
}

std::shared_ptr<ForceTorqueFunction> MbD::ForceTorqueAction::getforTorFunction()
{
	assert(false);
	return std::shared_ptr<ForceTorqueFunction>();
}

void MbD::ForceTorqueAction::setforTorFunction(std::shared_ptr<ForceTorqueFunction> forTorFunction)
{
	assert(false);
}

void MbD::ForceTorqueAction::initializeGlobally()
{
	forTorFunction->initializeGlobally();
	forTorBasicI->initializeGlobally();
}

void MbD::ForceTorqueAction::initializeLocally()
{
	forTorFunction->initializeLocally();
	forTorBasicI->initializeLocally();
}

void MbD::ForceTorqueAction::postAccICIteration()
{
	forTorFunction->postAccICIteration();
	forTorBasicI->postAccICIteration();
	ForceTorqueItem::postAccICIteration();
}

void MbD::ForceTorqueAction::postCollisionCorrectorIteration()
{
	forTorFunction->postCollisionCorrectorIteration();
	forTorBasicI->postCollisionCorrectorIteration();
	ForceTorqueItem::postCollisionCorrectorIteration();
}

void MbD::ForceTorqueAction::postCollisionPredictor()
{
	forTorFunction->postCollisionPredictor();
	forTorBasicI->postCollisionPredictor();
	ForceTorqueItem::postCollisionPredictor();
}

void MbD::ForceTorqueAction::postDynCorrectorIteration()
{
	forTorFunction->postDynCorrectorIteration();
	forTorBasicI->postDynCorrectorIteration();
	ForceTorqueItem::postDynCorrectorIteration();
}

void MbD::ForceTorqueAction::postDynOutput()
{
	forTorFunction->postDynOutput();
	forTorBasicI->postDynOutput();
	ForceTorqueItem::postDynOutput();
}

void MbD::ForceTorqueAction::postDynPredictor()
{
	forTorFunction->postDynPredictor();
	forTorBasicI->postDynPredictor();
	ForceTorqueItem::postDynPredictor();
}

void MbD::ForceTorqueAction::postInput()
{
	forTorFunction->postInput();
	forTorBasicI->postInput();
	ForceTorqueItem::postInput();
}

void MbD::ForceTorqueAction::postStaticIteration()
{
	forTorFunction->postStaticIteration();
	forTorBasicI->postStaticIteration();
	ForceTorqueItem::postStaticIteration();
}

void MbD::ForceTorqueAction::preAccIC()
{
	forTorFunction->preAccIC();
	forTorBasicI->preAccIC();
	ForceTorqueItem::preAccIC();
}

void MbD::ForceTorqueAction::preDynOutput()
{
	forTorFunction->preDynOutput();
	forTorBasicI->preDynOutput();
	ForceTorqueItem::preDynOutput();
}

void MbD::ForceTorqueAction::preStatic()
{
	forTorFunction->preStatic();
	forTorBasicI->preStatic();
	ForceTorqueItem::preStatic();
}

void MbD::ForceTorqueAction::simUpdateAll()
{
	forTorFunction->simUpdateAll();
	forTorBasicI->simUpdateAll();
	ForceTorqueItem::simUpdateAll();
}

void MbD::ForceTorqueAction::useEquationNumbers()
{
	forTorFunction->useEquationNumbers();
	forTorBasicI->useEquationNumbers();
}

void MbD::ForceTorqueAction::forceOnFrmIaxis(EndFrmsptr frmi, size_t axis)
{
	assert(false);
}

void MbD::ForceTorqueAction::torqueOnFrmIaxis(EndFrmsptr frmi, size_t axis)
{
	assert(false);
}

void MbD::ForceTorqueAction::forceOnFrmIwrtFrmKaxis(EndFrmsptr frmi, EndFrmsptr frmk, size_t axis)
{
	assert(false);
}

void MbD::ForceTorqueAction::torqueOnFrmIwrtFrmKaxis(EndFrmsptr frmi, EndFrmsptr frmk, size_t axis)
{
	assert(false);
}
