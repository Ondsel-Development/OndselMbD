#pragma once
#include "KinematicDotIeJe.h"

namespace MbD {
    class OmeCompIecJecKec : public KinematicDotIeJe
    {
		//efrmK axisK omeiIeJeKe aAjOKe omeIeJeO 
	public:
		OmeCompIecJecKec() {}
		OmeCompIecJecKec(EndFrmsptr frmi, EndFrmsptr frmj) : KinematicDotIeJe(frmi, frmj) {}
		static std::shared_ptr<OmeCompIecJecKec> With();
		static std::shared_ptr<OmeCompIecJecKec> With(EndFrmsptr frmi, EndFrmsptr frmj);
		void withFrmIfrmJfrmKaxis(EndFrmsptr frmi, EndFrmsptr frmj, EndFrmsptr frmk, size_t axis) override;

		double value() override;
		void calcPostDynCorrectorIteration() override;

		EndFrmsptr efrmK;
		size_t axisK;
		double omeiIeJeKe;
		FColDsptr aAjOKe;
		FColDsptr omeIeJeO;
	};
}
