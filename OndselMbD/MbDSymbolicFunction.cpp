#include <memory>

#include "MbDSymbolicFunction.h"
#include "Constant.h"
#include "KinematicDotIeJe.h"
#include "DispCompIecJecKec.h"
#include "KinematicIJ.h"

using namespace MbD;

std::shared_ptr<MbDSymbolicFunction> MbD::MbDSymbolicFunction::With(std::shared_ptr<KinematicIJ> kineIJ)
{
	auto inst = std::make_shared<MbDSymbolicFunction>(kineIJ);
	inst->initialize();
	return inst;
}

void MbD::MbDSymbolicFunction::initialize()
{
	mbdObject->initialize();
}

double MbD::MbDSymbolicFunction::getValue()
{
	return mbdObject->value();
}

Symsptr MbD::MbDSymbolicFunction::differentiateWRT(Symsptr var)
{
	if (this == var.get()) {
		return Constant::With(1.0);
	}
	else {
		return Constant::With(0.0);
	}
}

void MbD::MbDSymbolicFunction::fillKineIJs(std::shared_ptr<std::vector<std::shared_ptr<MbDSymbolicFunction>>> kineIJs)
{
	if (!mbdObject->isKineIJ()) return;
	auto it = std::find_if(kineIJs->begin(), kineIJs->end(), [&](auto funcPtr) {return funcPtr.get() == this; });
	if (it == kineIJs->end()) kineIJs->push_back(std::static_pointer_cast<MbDSymbolicFunction>(shared_from_this()));
}

void MbD::MbDSymbolicFunction::fillKinedotIJs(std::shared_ptr<std::vector<std::shared_ptr<MbDSymbolicFunction>>> kinedotIJs)
{
	if (!mbdObject->isKinedotIJ()) return;
	auto it = std::find_if(kinedotIJs->begin(), kinedotIJs->end(), [&](auto funcPtr) {return funcPtr.get() == this; });
	if (it == kinedotIJs->end()) kinedotIJs->push_back(std::static_pointer_cast<MbDSymbolicFunction>(shared_from_this()));
}

void MbD::MbDSymbolicFunction::fillJointForces(std::shared_ptr<std::vector<std::shared_ptr<MbDSymbolicFunction>>> jointActions)
{
	if (!mbdObject->isJointForce()) return;
	auto it = std::find_if(jointActions->begin(), jointActions->end(), [&](auto funcPtr) {return funcPtr.get() == this; });
	if (it == jointActions->end()) jointActions->push_back(std::static_pointer_cast<MbDSymbolicFunction>(shared_from_this()));
}

void MbD::MbDSymbolicFunction::fillJointTorques(std::shared_ptr<std::vector<std::shared_ptr<MbDSymbolicFunction>>> jointActions)
{
	if (!mbdObject->isJointTorque()) return;
	auto it = std::find_if(jointActions->begin(), jointActions->end(), [&](auto funcPtr) {return funcPtr.get() == this; });
	if (it == jointActions->end()) jointActions->push_back(std::static_pointer_cast<MbDSymbolicFunction>(shared_from_this()));
}

void MbD::MbDSymbolicFunction::initializeGlobally()
{
	mbdObject->initializeGlobally();
}

void MbD::MbDSymbolicFunction::initializeLocally()
{
	mbdObject->initializeLocally();
}

void MbD::MbDSymbolicFunction::postAccICIteration()
{
	mbdObject->postAccICIteration();
}

void MbD::MbDSymbolicFunction::postCollisionCorrectorIteration()
{
	mbdObject->postCollisionCorrectorIteration();
}

void MbD::MbDSymbolicFunction::postCollisionPredictor()
{
	mbdObject->postCollisionPredictor();
}

void MbD::MbDSymbolicFunction::postDynCorrectorIteration()
{
	mbdObject->postDynCorrectorIteration();
}

void MbD::MbDSymbolicFunction::postDynOutput()
{
	mbdObject->postDynOutput();
}

void MbD::MbDSymbolicFunction::postDynPredictor()
{
	mbdObject->postDynPredictor();
}

void MbD::MbDSymbolicFunction::postInput()
{
	mbdObject->postInput();
}

void MbD::MbDSymbolicFunction::postStaticIteration()
{
	mbdObject->postStaticIteration();
}

void MbD::MbDSymbolicFunction::preAccIC()
{
	mbdObject->preAccIC();
}

void MbD::MbDSymbolicFunction::preDynOutput()
{
	mbdObject->preDynOutput();
}

void MbD::MbDSymbolicFunction::preStatic()
{
	mbdObject->preStatic();
}

void MbD::MbDSymbolicFunction::simUpdateAll()
{
	mbdObject->simUpdateAll();
}

void MbD::MbDSymbolicFunction::useEquationNumbers()
{
	mbdObject->useEquationNumbers();
}

FRowDsptr MbD::MbDSymbolicFunction::pvaluepEI()
{
	return std::static_pointer_cast<KinematicIJ>(mbdObject)->pvaluepEI();
}

FRowDsptr MbD::MbDSymbolicFunction::pvaluepXI()
{
	return std::static_pointer_cast<KinematicIJ>(mbdObject)->pvaluepXI();
}

FRowDsptr MbD::MbDSymbolicFunction::pvaluepEJ()
{
	return std::static_pointer_cast<KinematicIJ>(mbdObject)->pvaluepEJ();
}

FRowDsptr MbD::MbDSymbolicFunction::pvaluepXJ()
{
	return std::static_pointer_cast<KinematicIJ>(mbdObject)->pvaluepXJ();
}

FRowDsptr MbD::MbDSymbolicFunction::pvaluepEK()
{
	return std::static_pointer_cast<KinematicIJ>(mbdObject)->pvaluepEK();
}

FRowDsptr MbD::MbDSymbolicFunction::pvaluepXK()
{
	return std::static_pointer_cast<KinematicIJ>(mbdObject)->pvaluepXK();
}

FRowDsptr MbD::MbDSymbolicFunction::pvaluepEdotI()
{
	return std::static_pointer_cast<KinematicDotIeJe>(mbdObject)->pvaluepEdotI();
}

FRowDsptr MbD::MbDSymbolicFunction::pvaluepXdotI()
{
	return std::static_pointer_cast<KinematicDotIeJe>(mbdObject)->pvaluepXdotI();
}

FRowDsptr MbD::MbDSymbolicFunction::pvaluepEdotJ()
{
	return std::static_pointer_cast<KinematicDotIeJe>(mbdObject)->pvaluepEdotJ();
}

FRowDsptr MbD::MbDSymbolicFunction::pvaluepXdotJ()
{
	return std::static_pointer_cast<KinematicDotIeJe>(mbdObject)->pvaluepXdotJ();
}

FRowDsptr MbD::MbDSymbolicFunction::pvaluepEdotK()
{
	return std::static_pointer_cast<KinematicDotIeJe>(mbdObject)->pvaluepEdotK();
}

FRowDsptr MbD::MbDSymbolicFunction::pvaluepXdotK()
{
	return std::static_pointer_cast<KinematicDotIeJe>(mbdObject)->pvaluepXdotK();
}

SpRowDsptr MbD::MbDSymbolicFunction::pvalueplam()
{
	assert(false);
	return SpRowDsptr();
}

PartFrame* MbD::MbDSymbolicFunction::partFrameI()
{
	return std::static_pointer_cast<KinematicIJ>(mbdObject)->partFrameI();
}

PartFrame* MbD::MbDSymbolicFunction::partFrameJ()
{
	return std::static_pointer_cast<KinematicIJ>(mbdObject)->partFrameJ();
}

PartFrame* MbD::MbDSymbolicFunction::partFrameK()
{
	auto frmIqc = std::dynamic_pointer_cast<DispCompIecJecKec>(mbdObject);
	if (frmIqc) {
		return frmIqc->partFrameK();
	}
	return nullptr;
}
