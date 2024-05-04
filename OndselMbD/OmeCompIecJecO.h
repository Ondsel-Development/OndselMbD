#pragma once
#include "KinematicDotIeJe.h"

namespace MbD {
    class OmeCompIecJecO : public KinematicDotIeJe
    {
    public:
        void withFrmIfrmJaxis(EndFrmsptr frmi, EndFrmsptr frmj, size_t axis) override;

        size_t axis = SIZE_MAX;
    };
}
