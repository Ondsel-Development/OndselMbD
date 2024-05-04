#include "ASMTSymbolicFunctionIJ.h"
#include "MbDSymbolicFunction.h"
#include "Units.h"
#include "Constant.h"

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

void MbD::ASMTSymbolicFunctionIJ::withFrmIfrmJ(EndFrmsptr eFrmI, EndFrmsptr eFrmJ)
{
	assert(false);
}

void MbD::ASMTSymbolicFunctionIJ::createMbD()
{
	auto eFrmI = std::static_pointer_cast<EndFrameqc>(geoIJ->markerI->mbdObject);
	auto eFrmJ = std::static_pointer_cast<EndFrameqc>(geoIJ->markerJ->mbdObject);
	auto kineIJ = mbdClassNew();
	kineIJ->withFrmIfrmJ(eFrmI, eFrmJ);
	auto distIeJe = MbDSymbolicFunction::With(kineIJ);
	expression = Symbolic::times(distIeJe, sptrConstant(asmtUnit()));
	xx = distIeJe;
}

double MbD::ASMTSymbolicFunctionIJ::asmtUnit()
{
	assert(false);
	return 0.0;
}
