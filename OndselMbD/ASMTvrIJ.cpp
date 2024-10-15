#include "ASMTvrIJ.h"
#include "Units.h"
#include "VelRadIeqctJeqc.h"
#include "VelRadIeqcJeqc.h"
#include "VelRadIectJeqc.h"
#include "VelRadIecJeqc.h"

using namespace MbD;

std::shared_ptr<ASMTvrIJ> MbD::ASMTvrIJ::With()
{
	auto inst = std::make_shared<ASMTvrIJ>();
	inst->initialize();
	return inst;
}

std::shared_ptr<KinematicIJ> MbD::ASMTvrIJ::mbdClassNew()
{
	return VelRadIeqcJeqc::With();
}

std::shared_ptr<KinematicIJ> MbD::ASMTvrIJ::mbdKineIqctJqc(EndFrmsptr frmi, EndFrmsptr frmj)
{
	return VelRadIeqctJeqc::With(frmi, frmj);
}

std::shared_ptr<KinematicIJ> MbD::ASMTvrIJ::mbdKineIqcJqc(EndFrmsptr frmi, EndFrmsptr frmj)
{
	return VelRadIeqcJeqc::With(frmi, frmj);
}

std::shared_ptr<KinematicIJ> MbD::ASMTvrIJ::mbdKineIctJqc(EndFrmsptr frmi, EndFrmsptr frmj)
{
	return VelRadIectJeqc::With(frmi, frmj);
}

std::shared_ptr<KinematicIJ> MbD::ASMTvrIJ::mbdKineIcJqc(EndFrmsptr frmi, EndFrmsptr frmj)
{
	return VelRadIecJeqc::With(frmi, frmj);
}

double MbD::ASMTvrIJ::asmtUnit()
{
	return asmtUnits()->velocity;
}
