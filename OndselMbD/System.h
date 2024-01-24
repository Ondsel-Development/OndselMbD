/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
/*****************************************************************//**
 * \file   System.h
 * \brief  Multibody system of parts, joints, forces.
 * 
 * \author askoh
 * \date   May 2023
 *********************************************************************/

#pragma once

#include <memory>
#include <vector>
#include <functional>

#include "Item.h"

namespace MbD {
	class Part;
	class Joint;
	class SystemSolver;
	class Time;
	class Constraint;
	class PrescribedMotion;
	class ForceTorqueItem;
	class ExternalSystem;
	class SolverStatistics;

	class System : public Item
	{
		//ToDo: Needed members admSystem namedItems mbdTime parts jointsMotions forcesTorques sensors variables hasChanged mbdSystemSolver
	public:
		System();
		System(const char* str);
		static std::shared_ptr<System> With();
		System* root() override;
		void initialize() override;
		void initializeLocally() override;
		void initializeGlobally() override;
		void clear();
		void runPreDrag(std::shared_ptr<System> self);
		void runDragStep(std::shared_ptr<std::vector<std::shared_ptr<Part>>> dragParts) const;
		void runKINEMATIC(std::shared_ptr<System> self);
		void runDYNAMIC(std::shared_ptr<System> self);
		std::shared_ptr<std::vector<std::string>> discontinuitiesAtIC();
		void jointsMotionsDo(const std::function <void(std::shared_ptr<Joint>)>& f) const;
		void partsJointsMotionsDo(const std::function <void(std::shared_ptr<Item>)>& f) const;
		void partsJointsMotionsForcesTorquesDo(const std::function <void(std::shared_ptr<Item>)>& f) const;
		void logString(std::string& str) override;
		double mbdTimeValue() const;
		void mbdTimeValue(double t) const;
		std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> essentialConstraints() const;
		std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> displacementConstraints() const;
		std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> perpendicularConstraints() const;
		std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> allRedundantConstraints() const;
		std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> allConstraints() const;
		void addPart(std::shared_ptr<Part> part);
		void addJoint(std::shared_ptr<Joint> joint);
		void addMotion(std::shared_ptr<PrescribedMotion> motion);
		void addForceTorque(std::shared_ptr<ForceTorqueItem> forTor);

		double maximumMass() const;
		double maximumMomentOfInertia() const;
		double translationLimit() const;
		double rotationLimit() const;
		void outputFor(AnalysisType type) const;
		void useKineTrialStepStats(std::shared_ptr<SolverStatistics> stats);
		void useDynTrialStepStats(std::shared_ptr<SolverStatistics> stats) const;

		std::shared_ptr<ExternalSystem> externalSystem;
		std::shared_ptr<std::vector<std::shared_ptr<Part>>> parts;
		std::shared_ptr<std::vector<std::shared_ptr<Joint>>> jointsMotions;
		std::shared_ptr<std::vector<std::shared_ptr<ForceTorqueItem>>> forcesTorques;
		bool hasChanged = false;
		std::shared_ptr<SystemSolver> systemSolver;

		std::shared_ptr<Time> time;
	};
}
