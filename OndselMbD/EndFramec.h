/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include <memory>

#include "CartesianFrame.h"
#include "MarkerFrame.h"
#include "FullColumn.h"     //FColDsptr is defined
#include "FullMatrix.h"     //FMatDsptr is defined

namespace MbD {
	class SpatialContainerFrame;
	//class MarkerFrame;
	class EndFrameqc;
	class EndFramec;
	class EndFramect;
	using EndFrmsptr = std::shared_ptr<EndFramec>;

	class EndFramec : public CartesianFrame
	{
		//markerFrame rOeO aAOe 
	public:
		EndFramec() {}
		EndFramec(const char* str) : CartesianFrame(str) {}
		static std::shared_ptr<EndFramec> With();
		static std::shared_ptr<EndFramec> With(const char* str);
		void initialize() override;
		System* root() override;
		virtual void initEndFrameqct();
		virtual void initEndFrameqct2();

		FMatDsptr aAeO() const;
		FColDsptr aAjOe(size_t j) const;
		void aApm(FMatDsptr mat);
		void calcPostDynCorrectorIteration() override;
		virtual void fillContactEndFrames(std::set<EndFramec*> efrms);
		FColDsptr ieO() const;
		FColDsptr jeO() const;
		FColDsptr keO() const;
		MarkerFrame* getMarkerFrame() const;
		void setMarkerFrame(MarkerFrame* markerFrm);
		std::shared_ptr<EndFrameqc> newCopyEndFrameqc();
		virtual std::shared_ptr<EndFrameqc> followEndFrame(EndFrmsptr frmi);
		SpatialContainerFrame* getPartFrame() const;
		std::shared_ptr<EulerParameters<double>> qEOe() const;
		double riOeO(size_t i) const;
		virtual FColDsptr rpmp();
		virtual FColDsptr rmeO();
		virtual FColDsptr rpep();
		virtual FColFMatDsptr pAOppE();
		virtual FMatDsptr aBOp();
		virtual bool isEndFrameqc();
		FColDsptr vOeO() const;
		FColDsptr aOeO() const;

		FColDsptr rmem = std::make_shared<FullColumn<double>>(3);
		FMatDsptr aAme = FullMatrix<double>::identitysptr(3);
		MarkerFrame* markerFrame = nullptr; //Use raw pointer when pointing backwards.
		FColDsptr rOeO = std::make_shared<FullColumn<double>>(3);
		FMatDsptr aAOe = FullMatrix<double>::identitysptr(3);
		std::shared_ptr<EndFramect> endFramect;
	};
	//using EndFrmsptr = std::shared_ptr<EndFramec>;
}

