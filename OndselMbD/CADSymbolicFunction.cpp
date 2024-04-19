#include "CADSymbolicFunction.h"

using namespace MbD;

std::shared_ptr<CADSymbolicFunction> MbD::CADSymbolicFunction::With()
{
	auto inst = std::make_shared<CADSymbolicFunction>();
	inst->initialize();
	return inst;
}

Symsptr MbD::CADSymbolicFunction::expandUntil(Symsptr sptr, std::shared_ptr<std::unordered_set<Symsptr>> set)
{
	return sptr;
}

Symsptr MbD::CADSymbolicFunction::simplifyUntil(Symsptr sptr, std::shared_ptr<std::unordered_set<Symsptr>> set)
{
	return sptr;
}

bool MbD::CADSymbolicFunction::isConstant()
{
	return false;
}

void MbD::CADSymbolicFunction::fillKineIJs(std::shared_ptr<std::vector<std::shared_ptr<MbDSymbolicFunction>>> kineIJs)
{
	xx->fillKineIJs(kineIJs);
}

void MbD::CADSymbolicFunction::fillKinedotIJs(std::shared_ptr<std::vector<std::shared_ptr<MbDSymbolicFunction>>> kinedotIJs)
{
	xx->fillKinedotIJs(kinedotIJs);
}

void MbD::CADSymbolicFunction::fillJointForces(std::shared_ptr<std::vector<std::shared_ptr<MbDSymbolicFunction>>> jointForces)
{
	xx->fillJointForces(jointForces);
}

void MbD::CADSymbolicFunction::fillJointTorques(std::shared_ptr<std::vector<std::shared_ptr<MbDSymbolicFunction>>> jointTorques)
{
	xx->fillJointTorques(jointTorques);
}
