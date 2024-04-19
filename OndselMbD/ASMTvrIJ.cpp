#include "ASMTvrIJ.h"
#include "VelRadIeqcJeqc.h"

using namespace MbD;

std::shared_ptr<KinematicIeJe> MbD::ASMTvrIJ::mbdClassNew()
{
	return VelRadIeqcJeqc::With();
}
