/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselMbD.                                       *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "ConstraintIJ.h"
#include "DispCompIecJecKec.h"

namespace MbD {
    class TranslationConstraintIJ : public ConstraintIJ
    {
        //riIeJeIe
    public:
        TranslationConstraintIJ(EndFrmsptr frmi, EndFrmsptr frmj, int axisi);

        void calcPostDynCorrectorIteration() override;
        void initialize() override;
        void initializeGlobally() override;
        void initializeLocally() override;
        virtual void initriIeJeIe();
        void postInput() override;
        void postPosICIteration() override;
        void preAccIC() override;
        void prePosIC()override;
        void preVelIC() override;
        void simUpdateAll() override;
        ConstraintType type() override;
        void postDynPredictor() override;
        void postDynCorrectorIteration() override;

        int axisI;
        std::shared_ptr<DispCompIecJecKec> riIeJeIe;
        //ToDo: Use DispCompIecJecIe instead of DispCompIecJecKec
    };
}

