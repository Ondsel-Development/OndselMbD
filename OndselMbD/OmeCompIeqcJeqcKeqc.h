#pragma once
#include "OmeCompIeqcJecKeqc.h"

namespace MbD {
    class OmeCompIeqcJeqcKeqc : public OmeCompIeqcJecKeqc
    {
		//pomeiIeJeKepEJ pomeiIeJeKepEdotJ 
	public:
		OmeCompIeqcJeqcKeqc() {}
		OmeCompIeqcJeqcKeqc(EndFrmsptr frmi, EndFrmsptr frmj) : OmeCompIeqcJecKeqc(frmi, frmj) {}
		static std::shared_ptr<OmeCompIeqcJeqcKeqc> With();
		static std::shared_ptr<OmeCompIeqcJeqcKeqc> With(EndFrmsptr frmi, EndFrmsptr frmj);
		void initialize() override;

		void calcPostDynCorrectorIteration() override;
		FRowDsptr pvaluepEJ() override;
		FRowDsptr pvaluepEdotJ() override;

		FRowDsptr pomeiIeJeKepEJ, pomeiIeJeKepEdotJ;
	};
}
