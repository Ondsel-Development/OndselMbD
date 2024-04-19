#include "ForTorAction.h"
#include "MarkerFrame.h"
#include "ForTorFunction.h"
#include "ForceBasicqcVector.h"
#include "TorqueBasicVector.h"

using namespace MbD;

MbD::ForTorAction::ForTorAction(size_t count)
{
	assert(false);
}

std::shared_ptr<ForTorAction> MbD::ForTorAction::With(size_t count)
{
	auto inst = std::make_shared<ForTorAction>(count);
	inst->initialize();
	return inst;
}

void MbD::ForTorAction::initialize()
{
	forTorFunction = ForTorFunction::With();
}

std::shared_ptr<ForTorFunction> MbD::ForTorAction::getforTorFunction()
{
	assert(false);
	return std::shared_ptr<ForTorFunction>();
}

void MbD::ForTorAction::setforTorFunction(std::shared_ptr<ForTorFunction> forTorFunction)
{
	assert(false);
}

void MbD::ForTorAction::initializeGlobally()
{
	forTorFunction->initializeGlobally();
	forTorBasicI->initializeGlobally();
}

void MbD::ForTorAction::initializeLocally()
{
	forTorFunction->initializeLocally();
	forTorBasicI->initializeLocally();
}

void MbD::ForTorAction::postAccICIteration()
{
	forTorFunction->postAccICIteration();
	forTorBasicI->postAccICIteration();
	ForceTorqueItem::postAccICIteration();
}

void MbD::ForTorAction::postCollisionCorrectorIteration()
{
	forTorFunction->postCollisionCorrectorIteration();
	forTorBasicI->postCollisionCorrectorIteration();
	ForceTorqueItem::postCollisionCorrectorIteration();
}

void MbD::ForTorAction::postCollisionPredictor()
{
	forTorFunction->postCollisionPredictor();
	forTorBasicI->postCollisionPredictor();
	ForceTorqueItem::postCollisionPredictor();
}

void MbD::ForTorAction::postDynCorrectorIteration()
{
	forTorFunction->postDynCorrectorIteration();
	forTorBasicI->postDynCorrectorIteration();
	ForceTorqueItem::postDynCorrectorIteration();
}

void MbD::ForTorAction::postDynOutput()
{
	forTorFunction->postDynOutput();
	forTorBasicI->postDynOutput();
	ForceTorqueItem::postDynOutput();
}

void MbD::ForTorAction::postDynPredictor()
{
	forTorFunction->postDynPredictor();
	forTorBasicI->postDynPredictor();
	ForceTorqueItem::postDynPredictor();
}

void MbD::ForTorAction::postInput()
{
	forTorFunction->postInput();
	forTorBasicI->postInput();
	ForceTorqueItem::postInput();
}

void MbD::ForTorAction::postStaticIteration()
{
	forTorFunction->postStaticIteration();
	forTorBasicI->postStaticIteration();
	ForceTorqueItem::postStaticIteration();
}

void MbD::ForTorAction::preAccIC()
{
	forTorFunction->preAccIC();
	forTorBasicI->preAccIC();
	ForceTorqueItem::preAccIC();
}

void MbD::ForTorAction::preDynOutput()
{
	forTorFunction->preDynOutput();
	forTorBasicI->preDynOutput();
	ForceTorqueItem::preDynOutput();
}

void MbD::ForTorAction::preStatic()
{
	forTorFunction->preStatic();
	forTorBasicI->preStatic();
	ForceTorqueItem::preStatic();
}

void MbD::ForTorAction::simUpdateAll()
{
	forTorFunction->simUpdateAll();
	forTorBasicI->simUpdateAll();
	ForceTorqueItem::simUpdateAll();
}

void MbD::ForTorAction::useEquationNumbers()
{
	forTorFunction->useEquationNumbers();
	forTorBasicI->useEquationNumbers();
}
