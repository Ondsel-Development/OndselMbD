#include "OmeCompIecJecO.h"

using namespace MbD;

void MbD::OmeCompIecJecO::withFrmIfrmJaxis(EndFrmsptr frmi, EndFrmsptr frmj, size_t axs)
{
	efrmI = frmi;
	efrmJ = frmj;
	axis = axs;
}
