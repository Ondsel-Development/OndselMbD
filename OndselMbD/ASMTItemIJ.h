/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include <vector>

#include "ASMTItem.h"

namespace MbD {
    template<typename T>
    class FullColumn;
    using FColDsptr = std::shared_ptr<FullColumn<double>>;
    
    class ASMTItemIJ : public ASMTItem
    {
        //
    public:
        ASMTItemIJ();
        void setMarkerI(std::string mkrI);
        void setMarkerJ(std::string mkrJ);
        void readMarkerI(std::vector<std::string>& lines);
        void readMarkerJ(std::vector<std::string>& lines);
        void readFXonIs(std::vector<std::string>& lines);
        void readFYonIs(std::vector<std::string>& lines);
        void readFZonIs(std::vector<std::string>& lines);
        void readTXonIs(std::vector<std::string>& lines);
        void readTYonIs(std::vector<std::string>& lines);
        void readTZonIs(std::vector<std::string>& lines);
        void storeOnLevel(std::ofstream& os, size_t level) override;
        void storeOnTimeSeries(std::ofstream& os) override;
        FColDsptr aFII(size_t i);
        FColDsptr aFIO(size_t i);
        FColDsptr aTII(size_t i);
        FColDsptr aTIO(size_t i);

        std::string markerI, markerJ;
        std::shared_ptr<std::vector<std::shared_ptr<FullColumn<double>>>> cFIO;
        std::shared_ptr<std::vector<std::shared_ptr<FullColumn<double>>>> cTIO;
        std::shared_ptr<std::vector<std::shared_ptr<FullColumn<double>>>> in_cFIO;
        std::shared_ptr<std::vector<std::shared_ptr<FullColumn<double>>>> in_cTIO;
        FRowDsptr infxs, infys, infzs, intxs, intys, intzs;

    };
}

