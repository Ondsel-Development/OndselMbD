#include "ForTorActReact.h"

using namespace MbD;

std::shared_ptr<ForTorActReact> MbD::ForTorActReact::With()
{
	auto inst = std::make_shared<ForTorActReact>();
	inst->initialize();
	return inst;
}

FColDsptr MbD::ForTorActReact::getFTIeO() const
{
	return forTorAction->getFTIeO();
}

std::shared_ptr<ForTorFunction> MbD::ForTorActReact::getforTorFunction()
{
	return forTorAction->forTorFunction;
}

void MbD::ForTorActReact::setforTorFunction(std::shared_ptr<ForTorFunction> forTorFunction)
{
	assert(false);
}

void MbD::ForTorActReact::initializeGlobally()
{
	forTorAction->initializeGlobally();
	forTorBasicJ->initializeGlobally();
}

void MbD::ForTorActReact::initializeLocally()
{
	forTorAction->initializeLocally();
	forTorBasicJ->initializeLocally();
}

void MbD::ForTorActReact::postAccICIteration()
{
	forTorAction->postAccICIteration();
	forTorBasicJ->postAccICIteration();
	ForceTorqueItem::postAccICIteration();
}

void MbD::ForTorActReact::postCollisionCorrectorIteration()
{
	forTorAction->postCollisionCorrectorIteration();
	forTorBasicJ->postCollisionCorrectorIteration();
	ForceTorqueItem::postCollisionCorrectorIteration();
}

void MbD::ForTorActReact::postCollisionPredictor()
{
	forTorAction->postCollisionPredictor();
	forTorBasicJ->postCollisionPredictor();
	ForceTorqueItem::postCollisionPredictor();
}

void MbD::ForTorActReact::postDynCorrectorIteration()
{
	forTorAction->postDynCorrectorIteration();
	forTorBasicJ->postDynCorrectorIteration();
	ForceTorqueItem::postDynCorrectorIteration();
}

void MbD::ForTorActReact::postDynOutput()
{
	forTorAction->postDynOutput();
	forTorBasicJ->postDynOutput();
	ForceTorqueItem::postDynOutput();
}

void MbD::ForTorActReact::postDynPredictor()
{
	forTorAction->postDynPredictor();
	forTorBasicJ->postDynPredictor();
	ForceTorqueItem::postDynPredictor();
}

void MbD::ForTorActReact::postInput()
{
	forTorAction->postInput();
	forTorBasicJ->postInput();
	ForceTorqueItem::postInput();
}

void MbD::ForTorActReact::postStaticIteration()
{
	forTorAction->postStaticIteration();
	forTorBasicJ->postStaticIteration();
	ForceTorqueItem::postStaticIteration();
}

void MbD::ForTorActReact::preAccIC()
{
	forTorAction->preAccIC();
	forTorBasicJ->preAccIC();
	ForceTorqueItem::preAccIC();
}

void MbD::ForTorActReact::preDynOutput()
{
	forTorAction->preDynOutput();
	forTorBasicJ->preDynOutput();
	ForceTorqueItem::preDynOutput();
}

void MbD::ForTorActReact::preStatic()
{
	forTorAction->preStatic();
	forTorBasicJ->preStatic();
	ForceTorqueItem::preStatic();
}

void MbD::ForTorActReact::simUpdateAll()
{
	forTorAction->simUpdateAll();
	forTorBasicJ->simUpdateAll();
	ForceTorqueItem::simUpdateAll();
}

void MbD::ForTorActReact::useEquationNumbers()
{
	forTorAction->useEquationNumbers();
	forTorBasicJ->useEquationNumbers();
}
