#include "ASMTSymbolicFunctionIJ.h"
#include "MbDSymbolicFunction.h"
#include "Units.h"
#include "Constant.h"
#include "EndFrameqct.h"
#include "EndFrameqc.h"
#include "EndFramect.h"
#include "EndFramec.h"

using namespace MbD;

std::shared_ptr<ASMTSymbolicFunctionIJ> MbD::ASMTSymbolicFunctionIJ::With()
{
	auto inst = std::make_shared<ASMTSymbolicFunctionIJ>();
	inst->initialize();
	return inst;
}

MbD::ASMTSymbolicFunctionIJ::ASMTSymbolicFunctionIJ(std::shared_ptr<ASMTItemIJ> itemIJ) : geoIJ(itemIJ)
{
	assert(false);
}

std::shared_ptr<KinematicIJ> MbD::ASMTSymbolicFunctionIJ::mbdClassNew()
{
	//Should not create abstract class.
	assert(false);
	return std::shared_ptr<KinematicIJ>();
}

std::shared_ptr<KinematicIJ> MbD::ASMTSymbolicFunctionIJ::mbdKineIqctJqct(EndFrmsptr frmi, EndFrmsptr frmj)
{
	assert(false);
	return std::shared_ptr<KinematicIJ>();
}

std::shared_ptr<KinematicIJ> MbD::ASMTSymbolicFunctionIJ::mbdKineIqctJqc(EndFrmsptr frmi, EndFrmsptr frmj)
{
	assert(false);
	return std::shared_ptr<KinematicIJ>();
}

std::shared_ptr<KinematicIJ> MbD::ASMTSymbolicFunctionIJ::mbdKineIqctJct(EndFrmsptr frmi, EndFrmsptr frmj)
{
	assert(false);
	return std::shared_ptr<KinematicIJ>();
}

std::shared_ptr<KinematicIJ> MbD::ASMTSymbolicFunctionIJ::mbdKineIqctJc(EndFrmsptr frmi, EndFrmsptr frmj)
{
	assert(false);
	return std::shared_ptr<KinematicIJ>();
}

std::shared_ptr<KinematicIJ> MbD::ASMTSymbolicFunctionIJ::mbdKineIqcJqct(EndFrmsptr frmi, EndFrmsptr frmj)
{
	assert(false);
	return std::shared_ptr<KinematicIJ>();
}

std::shared_ptr<KinematicIJ> MbD::ASMTSymbolicFunctionIJ::mbdKineIqcJqc(EndFrmsptr frmi, EndFrmsptr frmj)
{
	assert(false);
	return std::shared_ptr<KinematicIJ>();
}

std::shared_ptr<KinematicIJ> MbD::ASMTSymbolicFunctionIJ::mbdKineIqcJct(EndFrmsptr frmi, EndFrmsptr frmj)
{
	assert(false);
	return std::shared_ptr<KinematicIJ>();
}

std::shared_ptr<KinematicIJ> MbD::ASMTSymbolicFunctionIJ::mbdKineIqcJc(EndFrmsptr frmi, EndFrmsptr frmj)
{
	assert(false);
	return std::shared_ptr<KinematicIJ>();
}

std::shared_ptr<KinematicIJ> MbD::ASMTSymbolicFunctionIJ::mbdKineIctJqct(EndFrmsptr frmi, EndFrmsptr frmj)
{
	assert(false);
	return std::shared_ptr<KinematicIJ>();
}

std::shared_ptr<KinematicIJ> MbD::ASMTSymbolicFunctionIJ::mbdKineIctJqc(EndFrmsptr frmi, EndFrmsptr frmj)
{
	assert(false);
	return std::shared_ptr<KinematicIJ>();
}

std::shared_ptr<KinematicIJ> MbD::ASMTSymbolicFunctionIJ::mbdKineIctJct(EndFrmsptr frmi, EndFrmsptr frmj)
{
	assert(false);
	return std::shared_ptr<KinematicIJ>();
}

std::shared_ptr<KinematicIJ> MbD::ASMTSymbolicFunctionIJ::mbdKineIctJc(EndFrmsptr frmi, EndFrmsptr frmj)
{
	assert(false);
	return std::shared_ptr<KinematicIJ>();
}

std::shared_ptr<KinematicIJ> MbD::ASMTSymbolicFunctionIJ::mbdKineIcJqct(EndFrmsptr frmi, EndFrmsptr frmj)
{
	assert(false);
	return std::shared_ptr<KinematicIJ>();
}

std::shared_ptr<KinematicIJ> MbD::ASMTSymbolicFunctionIJ::mbdKineIcJqc(EndFrmsptr frmi, EndFrmsptr frmj)
{
	assert(false);
	return std::shared_ptr<KinematicIJ>();
}

std::shared_ptr<KinematicIJ> MbD::ASMTSymbolicFunctionIJ::mbdKineIcJct(EndFrmsptr frmi, EndFrmsptr frmj)
{
	assert(false);
	return std::shared_ptr<KinematicIJ>();
}

std::shared_ptr<KinematicIJ> MbD::ASMTSymbolicFunctionIJ::mbdKineIcJc(EndFrmsptr frmi, EndFrmsptr frmj)
{
	assert(false);
	return std::shared_ptr<KinematicIJ>();
}

std::shared_ptr<KinematicIJ> MbD::ASMTSymbolicFunctionIJ::mbdKineIJWith(EndFrmsptr frmi, EndFrmsptr frmj)
{
	std::shared_ptr<KinematicIJ> inst;
	if (std::dynamic_pointer_cast<EndFrameqct>(frmi)) {
		if (std::dynamic_pointer_cast<EndFrameqct>(frmj)) {
			inst = mbdKineIqctJqct(frmi, frmj);
		}
		else if (std::dynamic_pointer_cast<EndFrameqc>(frmj)) {
			inst = mbdKineIqctJqc(frmi, frmj);
		}
		else if (std::dynamic_pointer_cast<EndFramect>(frmj)) {
			inst = mbdKineIqctJct(frmi, frmj);
		}
		else if (std::dynamic_pointer_cast<EndFramec>(frmj)) {
			inst = mbdKineIqctJc(frmi, frmj);
		}
	}
	else if (std::dynamic_pointer_cast<EndFrameqc>(frmi)) {
		if (std::dynamic_pointer_cast<EndFrameqct>(frmj)) {
			inst = mbdKineIqcJqct(frmi, frmj);
		}
		else if (std::dynamic_pointer_cast<EndFrameqc>(frmj)) {
			inst = mbdKineIqcJqc(frmi, frmj);
		}
		else if (std::dynamic_pointer_cast<EndFramect>(frmj)) {
			inst = mbdKineIqcJct(frmi, frmj);
		}
		else if (std::dynamic_pointer_cast<EndFramec>(frmj)) {
			inst = mbdKineIqcJc(frmi, frmj);
		}
	}
	else if (std::dynamic_pointer_cast<EndFramect>(frmi)) {
		if (std::dynamic_pointer_cast<EndFrameqct>(frmj)) {
			inst = mbdKineIctJqct(frmi, frmj);
		}
		else if (std::dynamic_pointer_cast<EndFrameqc>(frmj)) {
			inst = mbdKineIctJqc(frmi, frmj);
		}
		else if (std::dynamic_pointer_cast<EndFramect>(frmj)) {
			inst = mbdKineIctJct(frmi, frmj);
		}
		else if (std::dynamic_pointer_cast<EndFramec>(frmj)) {
			inst = mbdKineIctJc(frmi, frmj);
		}
	}
	else if (std::dynamic_pointer_cast<EndFramec>(frmi)) {
		if (std::dynamic_pointer_cast<EndFrameqct>(frmj)) {
			inst = mbdKineIcJqct(frmi, frmj);
		}
		else if (std::dynamic_pointer_cast<EndFrameqc>(frmj)) {
			inst = mbdKineIcJqc(frmi, frmj);
		}
		else if (std::dynamic_pointer_cast<EndFramect>(frmj)) {
			inst = mbdKineIcJct(frmi, frmj);
		}
		else if (std::dynamic_pointer_cast<EndFramec>(frmj)) {
			inst = mbdKineIcJc(frmi, frmj);
		}
	}
	assert(inst);
	inst->initialize();
	return inst;
}

void MbD::ASMTSymbolicFunctionIJ::withFrmIfrmJ(EndFrmsptr eFrmI, EndFrmsptr eFrmJ)
{
	assert(false);
}

void MbD::ASMTSymbolicFunctionIJ::createMbD()
{
	auto eFrmI = std::static_pointer_cast<EndFrameqc>(geoIJ->markerI->mbdObject);
	auto eFrmJ = std::static_pointer_cast<EndFrameqc>(geoIJ->markerJ->mbdObject);
	auto kineIJ = mbdKineIJWith(eFrmI, eFrmJ);
	auto distIeJe = MbDSymbolicFunction::With(kineIJ);
	expression = Symbolic::times(distIeJe, sptrConstant(asmtUnit()));
	xx = distIeJe;
}

double MbD::ASMTSymbolicFunctionIJ::asmtUnit()
{
	assert(false);
	return 0.0;
}
