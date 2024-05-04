#include <algorithm>

#include "ForceTorqueVector.h"
#include "ForceTorqueFunction.h"

using namespace MbD;

std::shared_ptr<ForceTorqueVector> MbD::ForceTorqueVector::With()
{
	auto inst = std::make_shared<ForceTorqueVector>();
	inst->initialize();
	return inst;
}

FColDsptr MbD::ForceTorqueVector::getFTIeO() const
{
	auto aFTIeO = FullColumn<double>::With();
	for (size_t i = 0; i < 3; i++)
	{
		auto compi = components->at(i);
		aFTIeO->equalSelfPlusFullColumnAt(compi->getFTIeO(), i);
	}
	return aFTIeO;
}

void MbD::ForceTorqueVector::fillAccICIterError(FColDsptr col)
{
	std::for_each(components->begin(), components->end(), [&](auto component) { component->fillAccICIterError(col); });
}

void MbD::ForceTorqueVector::fillAccICIterJacob(SpMatDsptr mat)
{
	std::for_each(components->begin(), components->end(), [&](auto component) { component->fillAccICIterJacob(mat); });
}

void MbD::ForceTorqueVector::fillDynError(FColDsptr col)
{
	std::for_each(components->begin(), components->end(), [&](auto component) { component->fillDynError(col); });
}

void MbD::ForceTorqueVector::fillpFpy(SpMatDsptr mat)
{
	std::for_each(components->begin(), components->end(), [&](auto component) { component->fillpFpy(mat); });
}

void MbD::ForceTorqueVector::fillpFpydot(SpMatDsptr mat)
{
	std::for_each(components->begin(), components->end(), [&](auto component) { component->fillpFpydot(mat); });
}

void MbD::ForceTorqueVector::functions(FColsptr<Symsptr> col)
{
	auto comps = FullColumn<std::shared_ptr<ForceTorqueActReactComp>>::With();
	for (size_t i = 0; i < 3; i++)
	{
		auto compi = components->at(i);
		//compi forTorFunction formula isNil ifFalse : [self error : #'StM: ForceTorque function can only be initialized once.'] .
		auto funci = col->at(i);
		compi->getforTorFunction()->setformula(funci);
		comps->push_back(compi);
	}
	components = comps;
}

void MbD::ForceTorqueVector::initializeGlobally()
{
	std::for_each(components->begin(), components->end(), [&](auto component) { component->initializeGlobally(); });
}

void MbD::ForceTorqueVector::initializeLocally()
{
	std::for_each(components->begin(), components->end(), [&](auto component) { component->initializeLocally(); });
}

void MbD::ForceTorqueVector::postAccICIteration()
{
	std::for_each(components->begin(), components->end(), [&](auto component) { component->postAccICIteration(); });
}

void MbD::ForceTorqueVector::postCollisionCorrectorIteration()
{
	std::for_each(components->begin(), components->end(), [&](auto component) { component->postCollisionCorrectorIteration(); });
}

void MbD::ForceTorqueVector::postCollisionPredictor()
{
	std::for_each(components->begin(), components->end(), [&](auto component) { component->postCollisionPredictor(); });
}

void MbD::ForceTorqueVector::postDynCorrectorIteration()
{
	std::for_each(components->begin(), components->end(), [&](auto component) { component->postDynCorrectorIteration(); });
}

void MbD::ForceTorqueVector::postDynOutput()
{
	std::for_each(components->begin(), components->end(), [&](auto component) { component->postDynOutput(); });
}

void MbD::ForceTorqueVector::preAccIC()
{
	std::for_each(components->begin(), components->end(), [&](auto component) { component->preAccIC(); });
}

void MbD::ForceTorqueVector::preDynOutput()
{
	std::for_each(components->begin(), components->end(), [&](auto component) { component->preDynOutput(); });
}

void MbD::ForceTorqueVector::postDynPredictor()
{
	std::for_each(components->begin(), components->end(), [&](auto component) { component->postDynPredictor(); });
}

void MbD::ForceTorqueVector::postInput()
{
	std::for_each(components->begin(), components->end(), [&](auto component) { component->postInput(); });
}

void MbD::ForceTorqueVector::preStatic()
{
	std::for_each(components->begin(), components->end(), [&](auto component) { component->preStatic(); });
}

void MbD::ForceTorqueVector::simUpdateAll()
{
	std::for_each(components->begin(), components->end(), [&](auto component) { component->simUpdateAll(); });
}

void MbD::ForceTorqueVector::useEquationNumbers()
{
	std::for_each(components->begin(), components->end(), [&](auto component) { component->useEquationNumbers(); });
}
