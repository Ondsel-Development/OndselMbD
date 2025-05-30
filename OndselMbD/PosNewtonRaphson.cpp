/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include <iostream>
#include <sstream> 

#include "PosNewtonRaphson.h"
#include "SystemSolver.h"
#include "SimulationStoppingError.h"

using namespace MbD;

std::shared_ptr<PosNewtonRaphson> MbD::PosNewtonRaphson::With()
{
	//Should not create abstract class.
	assert(false);
	return std::shared_ptr<PosNewtonRaphson>();
}

void PosNewtonRaphson::preRun()
{
	system->partsJointsMotionsDo([&](std::shared_ptr<Item> item) { item->prePosIC(); });
}

void PosNewtonRaphson::incrementIterNo()
{
	iterNo++;
	if (iterNo > iterMax)
	{
		std::stringstream ss;
		ss << "MbD: No convergence after " << iterNo << " iterations.";
		auto str = ss.str();
		system->logString(str);
		ss.str("");
		ss << "MbD: A geometrically incompatible system has been specified.";
		str = ss.str();
		system->logString(str);
		ss.str("");
		ss << "MbD: Or the system parts are distributed too far apart from the assembled positions.";
		str = ss.str();
		system->logString(str);

		throw SimulationStoppingError("");
	}	
}

void PosNewtonRaphson::askSystemToUpdate()
{
	system->partsJointsMotionsDo([&](std::shared_ptr<Item> item) { item->postPosICIteration(); });
}

void PosNewtonRaphson::postRun()
{
	system->partsJointsMotionsDo([&](std::shared_ptr<Item> item) { item->postPosIC(); });
}

void MbD::PosNewtonRaphson::run()
{
	assert(false);
}

void MbD::PosNewtonRaphson::iterate()
{
	assert(false);
}
