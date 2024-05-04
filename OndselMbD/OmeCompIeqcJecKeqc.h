#pragma once
#include "OmeCompIecJecKeqc.h"

namespace MbD {
    class OmeCompIeqcJecKeqc : public OmeCompIecJecKeqc
    {
		//pomeiIeJeKepEI pomeiIeJeKepEdotI 
	public:
		OmeCompIeqcJecKeqc() {}
		OmeCompIeqcJecKeqc(EndFrmsptr frmi, EndFrmsptr frmj) : OmeCompIecJecKeqc(frmi, frmj) {}
		static std::shared_ptr<OmeCompIeqcJecKeqc> With();
		static std::shared_ptr<OmeCompIeqcJecKeqc> With(EndFrmsptr frmi, EndFrmsptr frmj);
		void initialize() override;

		void calcPostDynCorrectorIteration() override;
		FRowDsptr pvaluepEI() override;
		FRowDsptr pvaluepEdotI() override;

		FRowDsptr pomeiIeJeKepEI, pomeiIeJeKepEdotI;
	};
}
