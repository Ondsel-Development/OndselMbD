#pragma once
#include "EndFrameqc.h"

namespace MbD {
    class EndFrameqccq : public EndFrameqc
    {
        //targetFrame rpep pprOeOpEpEtarget 
    public:
        static std::shared_ptr<EndFrameqccq> With();

        EndFrmsptr targetFrame;
        FColDsptr rpep;
        FMatFColDsptr pprOeOpEpEtarget;
    };
}
