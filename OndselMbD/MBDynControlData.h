/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once
#include "MBDynBlock.h"

namespace MbD {
	class MBDynOutputMeter;

	class MBDynControlData : public MBDynBlock
	{
	public:
		static std::shared_ptr<MBDynControlData> With();
		void initialize() override;

		void parseMBDyn(std::vector<std::string>& lines) override;
		void readMaxIterations(std::vector<std::string>& lines);
		void readDefaultOrientation(std::vector<std::string>& lines);
		void readOmegaRotates(std::vector<std::string>& lines);
		void readPrint(std::vector<std::string>& lines);
		void readInitialStiffness(std::vector<std::string>& lines);
		void readOutputMeter(std::vector<std::string>& lines);
		void readStructuralNodes(std::vector<std::string>& lines);
		void readRigidBodies(std::vector<std::string>& lines);
		void readAbstractNodes(std::vector<std::string>& lines);
		void readJoints(std::vector<std::string>& lines);
		void readForces(std::vector<std::string>& lines);
		void readGravity(std::vector<std::string>& lines);
		void readGenels(std::vector<std::string>& lines);

		size_t maxIterations = 1000;
		std::string defaultOrientation = "euler321";
		std::string omegaRotates = "no";
		std::string print = "none";
		std::string initialStiffness = "1.0, 1.0";
		std::shared_ptr<MBDynOutputMeter> outputMeter;
		size_t structuralNodes = SIZE_MAX, rigidBodies = SIZE_MAX, abstractnodes = SIZE_MAX, joints = SIZE_MAX, forces = SIZE_MAX, genels = SIZE_MAX;
	};
}
