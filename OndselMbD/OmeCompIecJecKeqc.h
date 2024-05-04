#pragma once
#include "OmeCompIecJecKec.h"

namespace MbD {
    class OmeCompIecJecKeqc : public OmeCompIecJecKec
    {
		//pomeiIeJeKepEK 
	public:
		OmeCompIecJecKeqc() {}
		OmeCompIecJecKeqc(EndFrmsptr frmi, EndFrmsptr frmj) : OmeCompIecJecKec(frmi, frmj) {}
		static std::shared_ptr<OmeCompIecJecKeqc> With();
		static std::shared_ptr<OmeCompIecJecKeqc> With(EndFrmsptr frmi, EndFrmsptr frmj);
		void initialize() override;

		void calcPostDynCorrectorIteration() override;
		FRowDsptr pvaluepEK() override;

		FRowDsptr pomeiIeJeKepEK;
	};
}