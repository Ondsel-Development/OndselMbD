#pragma once

#include "ItemIJ.h"

namespace MbD {
    class ForceTorqueIJ : public ItemIJ
    {
    public:
        ForceTorqueIJ() {}
        ForceTorqueIJ(EndFrmsptr frmi, EndFrmsptr frmj) : ItemIJ(frmi, frmj) {}

        virtual FColDsptr aFX() const;
        virtual FColDsptr aTX() const;

    };
}

