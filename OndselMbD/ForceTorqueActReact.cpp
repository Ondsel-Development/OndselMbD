#include "ForceTorqueActReact.h"

using namespace MbD;

std::shared_ptr<ForceTorqueActReact> MbD::ForceTorqueActReact::With()
{
	auto inst = std::make_shared<ForceTorqueActReact>();
	inst->initialize();
	return inst;
}

FColDsptr MbD::ForceTorqueActReact::getFTIeO() const
{
	return forTorAction->getFTIeO();
}

std::shared_ptr<ForceTorqueFunction> MbD::ForceTorqueActReact::getforTorFunction()
{
	return forTorAction->forTorFunction;
}

void MbD::ForceTorqueActReact::setforTorFunction(std::shared_ptr<ForceTorqueFunction> forTorFunction)
{
	assert(false);
}

void MbD::ForceTorqueActReact::initializeGlobally()
{
	forTorAction->initializeGlobally();
	forTorBasicJ->initializeGlobally();
}

void MbD::ForceTorqueActReact::initializeLocally()
{
	forTorAction->initializeLocally();
	forTorBasicJ->initializeLocally();
}

void MbD::ForceTorqueActReact::postAccICIteration()
{
	forTorAction->postAccICIteration();
	forTorBasicJ->postAccICIteration();
	ForceTorqueItem::postAccICIteration();
}

void MbD::ForceTorqueActReact::postCollisionCorrectorIteration()
{
	forTorAction->postCollisionCorrectorIteration();
	forTorBasicJ->postCollisionCorrectorIteration();
	ForceTorqueItem::postCollisionCorrectorIteration();
}

void MbD::ForceTorqueActReact::postCollisionPredictor()
{
	forTorAction->postCollisionPredictor();
	forTorBasicJ->postCollisionPredictor();
	ForceTorqueItem::postCollisionPredictor();
}

void MbD::ForceTorqueActReact::postDynCorrectorIteration()
{
	forTorAction->postDynCorrectorIteration();
	forTorBasicJ->postDynCorrectorIteration();
	ForceTorqueItem::postDynCorrectorIteration();
}

void MbD::ForceTorqueActReact::postDynOutput()
{
	forTorAction->postDynOutput();
	forTorBasicJ->postDynOutput();
	ForceTorqueItem::postDynOutput();
}

void MbD::ForceTorqueActReact::postDynPredictor()
{
	forTorAction->postDynPredictor();
	forTorBasicJ->postDynPredictor();
	ForceTorqueItem::postDynPredictor();
}

void MbD::ForceTorqueActReact::postInput()
{
	forTorAction->postInput();
	forTorBasicJ->postInput();
	ForceTorqueItem::postInput();
}

void MbD::ForceTorqueActReact::postStaticIteration()
{
	forTorAction->postStaticIteration();
	forTorBasicJ->postStaticIteration();
	ForceTorqueItem::postStaticIteration();
}

void MbD::ForceTorqueActReact::preAccIC()
{
	forTorAction->preAccIC();
	forTorBasicJ->preAccIC();
	ForceTorqueItem::preAccIC();
}

void MbD::ForceTorqueActReact::preDynOutput()
{
	forTorAction->preDynOutput();
	forTorBasicJ->preDynOutput();
	ForceTorqueItem::preDynOutput();
}

void MbD::ForceTorqueActReact::preStatic()
{
	forTorAction->preStatic();
	forTorBasicJ->preStatic();
	ForceTorqueItem::preStatic();
}

void MbD::ForceTorqueActReact::simUpdateAll()
{
	forTorAction->simUpdateAll();
	forTorBasicJ->simUpdateAll();
	ForceTorqueItem::simUpdateAll();
}

void MbD::ForceTorqueActReact::useEquationNumbers()
{
	forTorAction->useEquationNumbers();
	forTorBasicJ->useEquationNumbers();
}
