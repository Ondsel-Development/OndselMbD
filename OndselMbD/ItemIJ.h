#pragma once

#include "Item.h"
#include "EndFrameqc.h"

namespace MbD {
    class ItemIJ : public Item
    {
    public:
        ItemIJ() {}
        ItemIJ(const char* str) : Item(str) {}
        ItemIJ(EndFrmsptr frmi, EndFrmsptr frmj) : efrmI(frmi), efrmJ(frmj) {}

        EndFrmsptr efrmI, efrmJ;
    };
}
