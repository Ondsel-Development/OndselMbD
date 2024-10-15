#include "ASMTrIJ.h"
#include "Units.h"
#include "DistIeqctJeqc.h"
#include "DistIeqcJeqc.h"
#include "DistIectJeqc.h"
#include "DistIecJeqc.h"

using namespace MbD;

std::shared_ptr<ASMTrIJ> MbD::ASMTrIJ::With()
{
	auto inst = std::make_shared<ASMTrIJ>();
	inst->initialize();
	return inst;
}

std::shared_ptr<KinematicIJ> MbD::ASMTrIJ::mbdClassNew()
{
	return DistIeqcJeqc::With();
}

std::shared_ptr<KinematicIJ> MbD::ASMTrIJ::mbdKineIqctJqc(EndFrmsptr frmi, EndFrmsptr frmj)
{
	return DistIeqctJeqc::With(frmi, frmj);
}

std::shared_ptr<KinematicIJ> MbD::ASMTrIJ::mbdKineIqcJqc(EndFrmsptr frmi, EndFrmsptr frmj)
{
	return DistIeqcJeqc::With(frmi, frmj);
}

std::shared_ptr<KinematicIJ> MbD::ASMTrIJ::mbdKineIctJqc(EndFrmsptr frmi, EndFrmsptr frmj)
{
	return DistIectJeqc::With(frmi, frmj);
}

std::shared_ptr<KinematicIJ> MbD::ASMTrIJ::mbdKineIcJqc(EndFrmsptr frmi, EndFrmsptr frmj)
{
	return DistIecJeqc::With(frmi, frmj);
}

double MbD::ASMTrIJ::asmtUnit()
{
	return asmtUnits()->length;
}
