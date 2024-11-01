/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

//#include <vector>

#include "Integrator.h"

namespace MbD {
	class IntegratorInterface;
	class LinearMultiStepMethod;
	template<typename T>
	class FullColumn;
	using FColDsptr = std::shared_ptr<FullColumn<double>>;

	class BasicIntegrator : public Integrator
	{
		//istep iTry maxTry tpast t tnew h hnew order orderNew orderMax opBDF continue 
	public:
		static std::shared_ptr<BasicIntegrator> With();
		void initialize() override;
		
		virtual void calcOperatorMatrix();
		virtual void incrementTime();
		virtual void incrementTry();
		void initializeGlobally() override;
		void initializeLocally() override;
		void iStep(size_t i) override;
		void postFirstStep() override;
		void postStep() override;
		void postRun() override;
		void preFirstStep() override;
		void preRun() override;
		void preStep() override;
		void reportStats() override;
		void run() override;
		void selectOrder() override;
		void subsequentSteps() override;
		void setSystem(Solver* sys) override;
		void logString(std::string& str) override;
		
		virtual void setorder(size_t o);
		virtual void settnew(double t);
		virtual void sett(double t);
		virtual void settime(double t);
		double tprevious() const;
		virtual FColDsptr yDerivat(size_t _order, double tout);

		IntegratorInterface* system;
		size_t istep = 0, iTry = 0, maxTry = 0;
		std::shared_ptr<std::vector<double>> tpast;
		double t = 0.0, tnew = 0.0, h = 0.0, hnew = 0.0;
		size_t order = 0, orderNew = 0, orderMax = 0;
		std::shared_ptr<LinearMultiStepMethod> opBDF;
		bool _continue = false;
	};
}

