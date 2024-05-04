#include "ForceTorqueActReactOComp.h"
#include "ForceBasicqccqComp.h"
#include "ForceTorqueActionOComp.h"
#include "TorqueBasicComp.h"

using namespace MbD;

std::shared_ptr<ForceTorqueActReactOComp> MbD::ForceTorqueActReactOComp::With()
{
	auto inst = std::make_shared<ForceTorqueActReactOComp>();
	inst->initialize();
	return inst;
}

void MbD::ForceTorqueActReactOComp::initialize()
{
	forTorAction = ForceTorqueActionOComp::With();
}

std::shared_ptr<ForceTorqueActReactOComp> MbD::ForceTorqueActReactOComp::ForceOnFrmIandFrmJaxis(EndFrmsptr eFrmI, EndFrmsptr eFrmJ, size_t axis)
{
	auto forTor = ForceTorqueActReactOComp::With();
	forTor->forceOnFrmIandFrmJaxis(eFrmI, eFrmJ, axis);
	return forTor;
}

std::shared_ptr<ForceTorqueActReactOComp> MbD::ForceTorqueActReactOComp::TorqueOnFrmIandFrmJaxis(EndFrmsptr eFrmI, EndFrmsptr eFrmJ, size_t axis)
{
	auto forTor = ForceTorqueActReactOComp::With();
	forTor->torqueOnFrmIandFrmJaxis(eFrmI, eFrmJ, axis);
	return forTor;
}

void MbD::ForceTorqueActReactOComp::forceOnFrmIandFrmJaxis(EndFrmsptr frmi, EndFrmsptr frmj, size_t axis)
{
	forTorAction->forceOnFrmIaxis(frmi, axis);
	forTorBasicJ = ForceBasicqccqComp::With();
	forTorBasicJ->parent = this;
	forTorBasicJ->endFramefollowEndFrame(frmj, frmi);
}

void MbD::ForceTorqueActReactOComp::torqueOnFrmIandFrmJaxis(EndFrmsptr frmi, EndFrmsptr frmj, size_t axis)
{
	forTorAction->torqueOnFrmIaxis(frmi, axis);
	forTorBasicJ = TorqueBasicComp::With();
	forTorBasicJ->parent = this;
	forTorBasicJ->endFrame = frmj;
}

void MbD::ForceTorqueActReactOComp::postDynPredictor()
{
	assert(false);
}
