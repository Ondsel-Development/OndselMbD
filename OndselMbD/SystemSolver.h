/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

//#include <memory>
//#include <vector>
//#include <functional> 
//#include <set> 

#include "Solver.h"
#include "System.h"
//#include "Constraint.h"
//#include "NewtonRaphson.h"
//#include "QuasiIntegrator.h"

namespace MbD {
	class System;
	class Constraint;
	class Solver;
	class IntegratorInterface;

	class SystemSolver : public Solver
	{
		//system parts jointsMotions forcesTorques sensors variables icTypeSolver setsOfRedundantConstraints errorTolPosKine errorTolAccKine 
		//iterMaxPosKine iterMaxAccKine basicIntegrator tstartPasts tstart hmin hmax tend toutFirst hout direction corAbsTol corRelTol 
		//intAbsTol intRelTol iterMaxDyn orderMax translationLimit rotationLimit 
	public:
		SystemSolver() {}
		SystemSolver(System* x);
		static std::shared_ptr<SystemSolver> With();
		void initialize() override;

		void setSystem(Solver* sys) override;
		void initializeLocally() override;
		void initializeGlobally() override;
		void runAllIC();
		void runPosIC();
		void runVelIC();
		void runAccIC();
		bool needToRedoPosIC();
		void preCollision();
		void runCollisionDerivativeIC();
		void runBasicCollision();
		void runBasicKinematic();
		void runPreDrag();
		void runDragStep(std::shared_ptr<std::vector<std::shared_ptr<Part>>> dragParts);
		void runQuasiKinematic();
		void runBasicDynamic();
		void runPosKine();
		void runVelKine();
		void runAccKine();
		void runPosICDrag(std::shared_ptr<std::vector<std::shared_ptr<Part>>> dragParts);
		void runPosICKine();
		void runVelICKine();
		void runAccICKine();
		void partsJointsMotionsDo(const std::function <void(std::shared_ptr<Item>)>& f);
		void logString(std::string& str) override;
		std::shared_ptr<std::vector<std::shared_ptr<Part>>> parts();
		//std::shared_ptr<std::vector<ContactEndFrame>> contactEndFrames();
		//std::shared_ptr<std::vector<UHolder>> uHolders();
		std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> essentialConstraints();
		std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> displacementConstraints();
		std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> perpendicularConstraints();
		std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> allRedundantConstraints();
		std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> allConstraints();
		
		virtual void postNewtonRaphson();
		void partsJointsMotionsForcesTorquesDo(const std::function <void(std::shared_ptr<Item>)>& f);
		void discontinuityBlock();
		double startTime();
		double outputStepSize();
		double maxStepSize();
		double minStepSize();
		double firstOutputTime();
		double endTime();
		void settime(double tnew);
		void errorTol(double tol);
		double integrationRelativeTolerance();
		double integrationAbsoluteTolerance();
		double correctorRelativeTolerance();
		double correctorAbsoluteTolerance();

		System* system; //Use raw pointer when pointing backwards.
		std::shared_ptr<Solver> icTypeSolver;
		std::shared_ptr<std::vector<std::shared_ptr<std::set<std::string>>>> setsOfRedundantConstraints;
		void tstartPastsAddFirst(double t);
		void output();
		void time(double t);
		void useKineTrialStepStats(std::shared_ptr<SolverStatistics> stats);
		void useDynTrialStepStats(std::shared_ptr<SolverStatistics> stats);
		void useDAEStepStats(std::shared_ptr<SolverStatistics> stats);

		double errorTolPosKine = 1.0e-6;
		double errorTolAccKine = 1.0e-6;
		size_t iterMaxPosKine = 25;
		size_t iterMaxAccKine = 25;
		std::shared_ptr <IntegratorInterface> basicIntegrator;
		std::shared_ptr<std::vector<double>> tstartPasts;
		double tstart = 0.0;
		double tend = 25;
		double toutFirst = 0.0;
		double hmin = 1.0e-9;
		double hmax = 1.0;
		double hout = 1.0e-1;
		double direction = 1;
		double corAbsTol = 0.0;
		double corRelTol = 0.0;
		double intAbsTol = 0.0;
		double intRelTol = 0.0;
		size_t iterMaxDyn = 0;
		size_t orderMax = 0;
		double translationLimit = 0.0;
		double rotationLimit = 0.0;
	};
}

