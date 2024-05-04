#include "ASMTSymbolicFunctionIJKi.h"
#include "MbDSymbolicFunction.h"
#include "Constant.h"

using namespace MbD;

std::shared_ptr<ASMTSymbolicFunctionIJKi> MbD::ASMTSymbolicFunctionIJKi::With()
{
	auto inst = std::make_shared<ASMTSymbolicFunctionIJKi>();
	inst->initialize();
	return inst;
}

void MbD::ASMTSymbolicFunctionIJKi::createMbD()
{
	auto eFrmI = std::static_pointer_cast<EndFrameqc>(geoIJ->markerI->mbdObject);
	auto eFrmJ = std::static_pointer_cast<EndFrameqc>(geoIJ->markerJ->mbdObject);
	std::shared_ptr<KinematicIJ> kineIJ;
	if (markerKSign == "O") {
		kineIJ = mbdClassNew();
		kineIJ->withFrmIfrmJaxis(eFrmI, eFrmJ, axisK);
	}
	else {
		std::shared_ptr<EndFrameqc> efrmK;
		if (markerKSign == "J") {
			efrmK = eFrmJ;
		}
		else {
			efrmK = eFrmI;
		}
		kineIJ = mbdClassNew();
		kineIJ->withFrmIfrmJfrmKaxis(eFrmI, eFrmJ, efrmK, axisK);
	}
	auto distIeJe = MbDSymbolicFunction::With(kineIJ);
	expression = Symbolic::times(distIeJe, sptrConstant(asmtUnit()));
	xx = distIeJe;
}

void MbD::ASMTSymbolicFunctionIJKi::withFrmIfrmJaxis(EndFrmsptr eFrmi, EndFrmsptr eFrmj, size_t axis)
{
	assert(false);
}

void MbD::ASMTSymbolicFunctionIJKi::withFrmIfrmJfrmK(EndFrmsptr eFrmi, EndFrmsptr eFrmj, EndFrmsptr eFrmK)
{
	assert(false);
}
