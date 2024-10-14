/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include<algorithm>

#include "System.h"
#include "Part.h"
#include "AssemblyFrame.h"
#include "EndFramec.h"
#include "EndFrameqc.h"
#include "JointIJ.h"
#include "ForceTorqueIJ.h"
#include "SystemSolver.h"
#include "Time.h"
#include "ExternalSystem.h"
#include "PrescribedMotion.h"

using namespace MbD;

System::System(const char* str) : Item(str) {
	assert(false);
}

std::shared_ptr<System> MbD::System::With()
{
	auto inst = std::make_shared<System>();
	inst->initialize();
	return inst;
}

std::shared_ptr<System> MbD::System::With(const char* str)
{
	auto inst = std::make_shared<System>(str);
	inst->initialize();
	return inst;
}

void System::initialize()
{
	externalSystem = std::make_shared<ExternalSystem>();
	time = std::make_shared<Time>();
	createAssemblyFrame();
	parts = std::make_shared<std::vector<std::shared_ptr<Part>>>();
	jointsMotions = std::make_shared<std::vector<std::shared_ptr<JointIJ>>>();
	forcesTorques = std::make_shared<std::vector<std::shared_ptr<ForceTorqueIJ>>>();
	fields = std::make_shared<std::vector<std::shared_ptr<ConstantGravity>>>();
	systemSolver = std::make_shared<SystemSolver>(this);
}

void MbD::System::createAssemblyFrame()
{
	asmFrame = AssemblyFrame::With();
	asmFrame->setAssembly(this);
}

System* MbD::System::root()
{
	return this;
}

void System::addPart(std::shared_ptr<Part> part)
{
	part->setSystem(this);
	parts->push_back(part);
}

void MbD::System::addJoint(std::shared_ptr<JointIJ> joint)
{
	joint->container = this;
	jointsMotions->push_back(joint);
}

void MbD::System::addMotion(std::shared_ptr<PrescribedMotion> motion)
{
	motion->container = this;
	jointsMotions->push_back(motion);
}

void MbD::System::addForceTorque(std::shared_ptr<ForceTorqueIJ> forTor)
{
	forTor->container = this;
	forcesTorques->push_back(forTor);
}

void MbD::System::addGravity(std::shared_ptr<ConstantGravity> grav)
{
	grav->container = this;
	fields->push_back(grav);
}

void MbD::System::calcCharacteristicDimensions()
{
	//mbdUnits are in SI units at input.
	auto unitTime = calcCharacteristicTime();
	auto unitMass = calcCharacteristicMass();
	auto unitLength = calcCharacteristicLength();
	auto unitAngle = 1.0;
	mbdUnits = std::make_shared<Units>(unitTime, unitMass, unitLength, unitAngle);
	mbdUnits = std::make_shared<Units>(1.0, 1.0, 1.0, 1.0);	//for debug
}

double MbD::System::calcCharacteristicTime() const
{
	return std::abs(systemSolver->hout);
}

double MbD::System::calcCharacteristicMass() const
{
	auto n = parts->size();
	double sumOfSquares = 0.0;
	for (size_t i = 0; i < n; i++)
	{
		auto mass = parts->at(i)->m;
		sumOfSquares += mass * mass;
	}
	auto rmsMass = std::sqrt(sumOfSquares / n);
	if (rmsMass <= 0) rmsMass = 1.0;
	return rmsMass;
}

double MbD::System::calcCharacteristicLength() const
{
	auto lengths = std::make_shared<std::vector<double>>();
	auto connectorList = this->connectorList();
	for (auto& connector : *connectorList) {
		std::vector<EndFrmsptr> efrms = { connector->efrmI, connector->efrmJ };
		for (const EndFrmsptr& efrm : efrms) {
			auto xc = std::dynamic_pointer_cast<EndFramec>(efrm);
			auto efrmqc = std::dynamic_pointer_cast<EndFrameqc>(efrm);
			if (efrmqc) {
				lengths->push_back(efrmqc->rpep()->length());
			}
			else {
				auto efrmc = std::dynamic_pointer_cast<EndFramec>(efrm);
				if (efrmc) {
					lengths->push_back(efrmc->rOeO->length());
				}
				else {
					assert(false);
				}
			}
		}
	}
	auto n = lengths->size();
	double sumOfSquares = std::accumulate(lengths->begin(), lengths->end(), 0.0, [](double sum, double l) { return sum + l * l; });
	auto rmsLength = std::sqrt(sumOfSquares / std::max(n, size_t(1)));
	if (rmsLength <= 0) rmsLength = 1.0;
	return rmsLength;
}

void System::runKINEMATIC(std::shared_ptr<System> self)
{
	externalSystem->preMbDrun(self);
	while (true)
	{
		initializeLocally();
		initializeGlobally();
		if (!hasChanged) break;
	}
	partsJointsMotionsForcesTorquesDo([](std::shared_ptr<Item> item) { item->postInput(); });
	externalSystem->outputFor(INPUT);
	systemSolver->runAllIC();
	externalSystem->outputFor(INITIALCONDITION);
	systemSolver->runBasicKinematic();
	externalSystem->postMbDrun();
}

void MbD::System::runDYNAMIC(std::shared_ptr<System> self)
{
	externalSystem->preMbDrun(self);
	calcCharacteristicDimensions();
	while (true)
	{
		initializeLocally();
		initializeGlobally();
		if (!hasChanged) break;
	}
	partsJointsMotionsForcesTorquesDo([](std::shared_ptr<Item> item) { item->postInput(); });
	externalSystem->outputFor(INPUT);
	systemSolver->runAllIC();
	externalSystem->outputFor(INITIALCONDITION);
	systemSolver->runBasicDynamic();
	externalSystem->postMbDrun();
}

void System::initializeLocally()
{
	hasChanged = false;
	time->value = systemSolver->tstart;
	partsJointsMotionsForcesTorquesDo([](std::shared_ptr<Item> item) { item->initializeLocally(); });
	systemSolver->initializeLocally();
}

void System::initializeGlobally()
{
	partsJointsMotionsForcesTorquesDo([](std::shared_ptr<Item> item) { item->initializeGlobally(); });
	systemSolver->initializeGlobally();
}

void System::clear()
{
	name = std::string();
	parts->clear();
	jointsMotions->clear();
	forcesTorques->clear();
	fields->clear();
}

void MbD::System::runPreDrag(std::shared_ptr<System> self)
{
	externalSystem->preMbDrun(self);
	while (true)
	{
		initializeLocally();
		initializeGlobally();
		if (!hasChanged) break;
	}
	partsJointsMotionsForcesTorquesDo([](std::shared_ptr<Item> item) { item->postInput(); });
	systemSolver->runPreDrag();
	externalSystem->updateFromMbD();
}

void MbD::System::runDragStep(std::shared_ptr<std::vector<std::shared_ptr<Part>>> dragParts) const
{
	partsJointsMotionsForcesTorquesDo([](std::shared_ptr<Item> item) { item->postInput(); });
	systemSolver->runDragStep(dragParts);
	externalSystem->updateFromMbD();
}

std::shared_ptr<std::vector<std::string>> System::discontinuitiesAtIC()
{
	return std::make_shared<std::vector<std::string>>();
}

void System::jointsMotionsDo(const std::function<void(std::shared_ptr<JointIJ>)>& f) const
{
	std::for_each(jointsMotions->begin(), jointsMotions->end(), f);
}

void System::partsJointsMotionsDo(const std::function<void(std::shared_ptr<Item>)>& f) const
{
	f(asmFrame);
	std::for_each(parts->begin(), parts->end(), f);
	std::for_each(jointsMotions->begin(), jointsMotions->end(), f);
}

void System::partsJointsMotionsForcesTorquesDo(const std::function<void(std::shared_ptr<Item>)>& f) const
{
	f(asmFrame);
	std::for_each(parts->begin(), parts->end(), f);
	std::for_each(jointsMotions->begin(), jointsMotions->end(), f);
	std::for_each(forcesTorques->begin(), forcesTorques->end(), f);
	std::for_each(fields->begin(), fields->end(), f);
}

void System::logString(std::string& str)
{
	externalSystem->logString(str);
}

double System::mbdTimeValue() const
{
	return time->getValue();
}

void System::mbdTimeValue(double t) const
{
	time->setValue(t);
}

std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> System::essentialConstraints() const
{
	auto essenConstraints = std::make_shared<std::vector<std::shared_ptr<Constraint>>>();
	partsJointsMotionsDo([&](std::shared_ptr<Item> item) { item->fillEssenConstraints(essenConstraints); });
	return essenConstraints;
}

std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> System::displacementConstraints() const
{
	auto dispConstraints = std::make_shared<std::vector<std::shared_ptr<Constraint>>>();
	jointsMotionsDo([&](std::shared_ptr<JointIJ> joint) { joint->fillDispConstraints(dispConstraints); });
	return dispConstraints;
}

std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> System::perpendicularConstraints() const
{
	auto perpenConstraints = std::make_shared<std::vector<std::shared_ptr<Constraint>>>();
	jointsMotionsDo([&](std::shared_ptr<JointIJ> joint) { joint->fillPerpenConstraints(perpenConstraints); });
	return perpenConstraints;
}

std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> System::allRedundantConstraints() const
{
	auto redunConstraints = std::make_shared<std::vector<std::shared_ptr<Constraint>>>();
	partsJointsMotionsDo([&](std::shared_ptr<Item> item) { item->fillRedundantConstraints(redunConstraints); });
	return redunConstraints;
}

std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> System::allConstraints() const
{
	auto constraints = std::make_shared<std::vector<std::shared_ptr<Constraint>>>();
	partsJointsMotionsDo([&](std::shared_ptr<Item> item) { item->fillConstraints(constraints); });
	return constraints;
}

std::shared_ptr<std::vector<std::shared_ptr<ItemIJ>>> MbD::System::connectorList() const
{
	auto list = std::make_shared<std::vector<std::shared_ptr<ItemIJ>>>();
	list->insert(list->end(), jointsMotions->begin(), jointsMotions->end());
	list->insert(list->end(), forcesTorques->begin(), forcesTorques->end());
	return list;
}

double System::maximumMass() const
{
	auto maxPart = std::max_element(parts->begin(), parts->end(), [](auto& a, auto& b) { return a->m < b->m; });
	return maxPart->get()->m;
}

double System::maximumMomentOfInertia() const
{
	double max = 0.0;
	for (size_t i = 0; i < parts->size(); i++)
	{
		auto& part = parts->at(i);
		for (size_t j = 0; j < 3; j++)
		{
			auto& aJ = part->aJ;
			auto aJi = aJ->at(j);
			if (max < aJi) max = aJi;
		}
	}
	return max;
}

double System::translationLimit() const
{
	return systemSolver->translationLimit;
}

double System::rotationLimit() const
{
	return systemSolver->rotationLimit;
}

void System::outputFor(AnalysisType type) const
{
	externalSystem->outputFor(type);
}

void MbD::System::useKineTrialStepStats(std::shared_ptr<SolverStatistics> stats)
{
	externalSystem->useKineTrialStepStats(stats);
}

void MbD::System::useDynTrialStepStats(std::shared_ptr<SolverStatistics> stats) const
{
	externalSystem->useDynTrialStepStats(stats);
}
