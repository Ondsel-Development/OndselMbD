/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
//#include <windows.h>
#include <assert.h>
//#include <debugapi.h>
#include <sstream> 
#include <chrono>

#include "Item.h"
#include "System.h"
#include "Symbolic.h"

using namespace MbD;

Item::Item() {
}

std::shared_ptr<Item> MbD::Item::With(const char* str)
{
	auto inst = std::make_shared<Item>(str);
	inst->initialize();
	return inst;
}

void Item::initialize()
{
	auto now = std::chrono::high_resolution_clock::now();
	auto nanoseconds = now.time_since_epoch().count();
	name = std::to_string(nanoseconds);
}

System* Item::root()
{
	return owner->root();
}

void MbD::Item::noop()
{
	//No Operations
}

std::ostream& Item::printOn(std::ostream& s) const
{
	std::string str = typeid(*this).name();
	auto classname = str.substr(11, str.size() - 11);
	s << classname << std::endl;
	return s;
}

bool MbD::Item::isJointForce()
{
	return false;
}

bool MbD::Item::isJointTorque()
{
	return false;
}

bool MbD::Item::isKinedotIJ()
{
	return false;
}

bool MbD::Item::isKineIJ()
{
	return false;
}

void Item::initializeGlobally()
{
	//"Called once only."
	//"Initialize all constant dependent instance variables using local and global objects."
	//"Default is do nothing."
}

void MbD::Item::initializeLocally()
{
	//"Called once only."
	//"Assume that the independent instance variables are already set."
	//"Initialize all constant dependent instance variables using local objects only."
	//"Default is do nothing."
}

void Item::postInput()
{
	//Called once after input
	calcPostDynCorrectorIteration();
}

void Item::calcPostDynCorrectorIteration()
{
	assert(false);
}

void MbD::Item::checkForCollisionDiscontinuityBetweenand(double, double)
{
	assert(false);
}

void Item::removeRedundantConstraints(std::shared_ptr<std::vector<size_t>>)
{
	assert(false);
}

void MbD::Item::setpqsumu(FColDsptr)
{
	//Do nothing.
}

void MbD::Item::setpqsumuddot(FColDsptr)
{
	//Do nothing.
}

void MbD::Item::setpqsumudot(FColDsptr)
{
	//Do nothing.
}

void Item::reactivateRedundantConstraints()
{
	assert(false);
}

void MbD::Item::registerName()
{
	assert(false);
}

void Item::fillPosKineError(FColDsptr)
{
	assert(false);
}

void Item::fillPosKineJacob(SpMatDsptr)
{
	assert(false);
}

void MbD::Item::fillpqsumu(FColDsptr)
{
	//Do nothing.
}

void MbD::Item::fillpqsumudot(FColDsptr)
{
	//Do nothing.
}

void Item::fillEssenConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>>)
{
	assert(false);
}

void MbD::Item::fillPerpenConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>>)
{
	assert(false);
}

void MbD::Item::fillpFpy(SpMatDsptr)
{
	//Do nothing.
}

void MbD::Item::fillpFpydot(SpMatDsptr)
{
	//Do nothing.
}

void Item::fillRedundantConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>>)
{
	assert(false);
}

void MbD::Item::fillStaticError(FColDsptr)
{
	assert(false);
}

void MbD::Item::fillStaticJacob(SpMatDsptr mat)
{
	assert(false);
}

void Item::fillConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>>)
{
	assert(false);
}

void MbD::Item::fillDispConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>>)
{
	assert(false);
}

void MbD::Item::fillDynError(FColDsptr)
{
	//Do nothing.
}

void Item::fillqsu(FColDsptr)
{
	//Do nothing.
}

void Item::fillqsuWeights(DiagMatDsptr)
{
	//Do nothing.
}

void MbD::Item::fillqsuWeightsSmall(FColDsptr)
{
	assert(false);
}

void Item::fillqsulam(FColDsptr)
{
	//Do nothing.
}

void Item::setqsulam(FColDsptr)
{
	//Do nothing.
}

void MbD::Item::simUpdateAll()
{
	calcPostDynCorrectorIteration();
}

void Item::preDyn()
{
	//"Assume positions, velocities and accelerations are valid."
	//"Called once before solving for dynamic solution."
	//"Update all variable dependent instance variables needed for runDYNAMICS even if they 
	//have been calculated in postPosIC, postVelIC and postAccIC."
	//"Calculate p, pdot."
	//"Default is do nothing."
}

void MbD::Item::preDynCorrector()
{
	//Do nothing
}

void MbD::Item::preDynCorrectorIteration()
{
	assert(false);
}

void Item::postDyn()
{
	//"Assume runDYNAMICS ended successfully."
	//"Called once at the end of runDYNAMICS."
	//"Update all instance variables dependent on p,q,s,u,mu,pdot,qdot,sdot,udot,mudot (lam) 
	//regardless of whether they are needed."
	//"This is a subset of update."
	//"Default is do nothing."
}

void MbD::Item::postDynCorrector()
{
	//Do nothing.
}

void MbD::Item::postDynCorrectorIteration()
{
	//"Called after the predictor stage in the dynamic solution."
	//"Update only instance variables dependent on p,q,s,u,mu,pdot,qdot,sdot,udot,mudot (lam) that are needed for the corrector stage."

	calcPostDynCorrectorIteration();
}

std::string Item::classname()
{
	std::string str = typeid(*this).name();
	auto answer = str.substr(11, str.size() - 11);
	return answer;
}

void Item::preDynFirstStep()
{
	//"Called before the start of the first step in the dynamic solution."
	this->preDynStep();
}

void MbD::Item::preDynOutput()
{
	//"Calculate all instance variables just before output."
	calcPostDynCorrectorIteration();
}

void MbD::Item::preDynPredictor()
{
	//"Do nothing"
}

void Item::postDynFirstStep()
{
	this->postDynStep();
}

void MbD::Item::postDynOutput()
{
	//"Calculate all instance variables just after output."
	calcPostDynCorrectorIteration();
}

void MbD::Item::postDynPredictor()
{
	//"Called after the predictor stage in the dynamic solution."
	//"Update only instance variables dependent on p,q,s,u,mu,pdot,qdot,sdot,udot,mudot (lam) 
	//that are needed for the corrector stage."
	//"Needless updating can be expensive here."
	//"This is a subset of update."
	//"Default is do nothing."
	//"updateInSimulation is the interface to the old system."

	calcPostDynCorrectorIteration();
}

void Item::preDynStep()
{
	//Do nothing.
}

void MbD::Item::preICRestart()
{
	assert(false);
}

void Item::postDynStep()
{
	//"Called after the end of a complete step in the dynamic solution."
	//"Update info before checking for discontinuities."
	//"Default is do nothing."
}

void Item::storeDynState()
{
	//Do nothing.
}

double MbD::Item::suggestSmallerOrAcceptCollisionFirstStepSize(double)
{
	assert(false);
	return 0.0;
}

double MbD::Item::suggestSmallerOrAcceptCollisionStepSize(double)
{
	assert(false);
	return 0.0;
}

double Item::suggestSmallerOrAcceptDynFirstStepSize(double hnew)
{
	//"Default is return hnew."
	//"Best to do nothing so as not to disrupt the starting algorithm."
	return hnew;
}

double Item::suggestSmallerOrAcceptDynStepSize(double hnew)
{
	//"Default is return hnew."
	return hnew;
}

void Item::preVelIC()
{
	//"Assume positions are valid."
	//"Called once before solving for velocity initial conditions."
	//"Update all variable dependent instance variables needed for velIC even if they have 
	//been calculated in postPosIC."
	//"Variables dependent on t are updated."

	calcPostDynCorrectorIteration();
}

void Item::postVelIC()
{
	//Do nothing.
}

void Item::fillqsudot(FColDsptr)
{
	//Do nothing.
}

void MbD::Item::fillqsudotPlam(FColDsptr)
{
	assert(false);
}

void MbD::Item::fillqsudotPlamDeriv(FColDsptr)
{
	assert(false);
}

void Item::fillqsudotWeights(DiagMatDsptr)
{
	//Do nothing.
}

void Item::fillVelICError(FColDsptr)
{
	//Do nothing.
}

void Item::fillVelICJacob(SpMatDsptr)
{
	//Do nothing.
}

void MbD::Item::getString(std::string)
{
	assert(false);
}

void Item::setqsudotlam(FColDsptr)
{
	//Do nothing.
}

void MbD::Item::setqsudotPlam(FColDsptr)
{
	assert(false);
}

void MbD::Item::setqsudotPlamDeriv(FColDsptr)
{
	assert(false);
}

void Item::preAccIC()
{
	calcPostDynCorrectorIteration();
}

void MbD::Item::preCollision()
{
	assert(false);
}

void MbD::Item::preCollisionCorrector()
{
	assert(false);
}

void MbD::Item::preCollisionCorrectorIteration()
{
	assert(false);
}

void MbD::Item::preCollisionDerivativeIC()
{
	assert(false);
}

void MbD::Item::preCollisionPredictor()
{
	assert(false);
}

void MbD::Item::preCollisionStep()
{
	assert(false);
}

void Item::postAccIC()
{
	//Do nothing.
}

void Item::postAccICIteration()
{
	//Do nothing.
}

void MbD::Item::postCollisionCorrector()
{
	assert(false);
}

void MbD::Item::postCollisionCorrectorIteration()
{
	assert(false);
}

void MbD::Item::postCollisionDerivativeIC()
{
	assert(false);
}

void MbD::Item::postCollisionPredictor()
{
	assert(false);
}

void MbD::Item::postCollisionStep()
{
	assert(false);
}

void Item::fillqsuddotlam(FColDsptr)
{
	//Do nothing.
}

void Item::fillAccICIterError(FColDsptr)
{
	//Do nothing.
}

void Item::fillAccICIterJacob(SpMatDsptr)
{
	//Do nothing.
}

void MbD::Item::fillCollisionDerivativeICError(FColDsptr)
{
	assert(false);
}

void MbD::Item::fillCollisionDerivativeICJacob(SpMatDsptr)
{
	assert(false);
}

void MbD::Item::fillCollisionError(FColDsptr)
{
	assert(false);
}

void MbD::Item::fillCollisionpFpy(SpMatDsptr)
{
	assert(false);
}

void MbD::Item::fillCollisionpFpydot(SpMatDsptr)
{
	assert(false);
}

void Item::setqsudot(FColDsptr)
{
	assert(false);
}

void Item::setqsuddotlam(FColDsptr)
{
	//Do nothing.
}

std::shared_ptr<StateData> Item::stateData()
{
	assert(false);
	return std::shared_ptr<StateData>();
}

void MbD::Item::storeCollisionState()
{
	assert(false);
}

void Item::discontinuityAtaddTypeTo(double, std::shared_ptr<std::vector<DiscontinuityType>>)
{
	assert(false);
}

void MbD::Item::discontinuityAtICAddTo(std::shared_ptr<std::vector<DiscontinuityType>>)
{
	assert(false);
}

double Item::checkForDynDiscontinuityBetweenand(double, double t)
{
	//"Check for discontinuity in the last step defined by the interval (tprevious,t]."
	//"Default is assume no discontinuity and return t."

	return t;
}

void Item::constraintsReport()
{
	assert(false);
}

void Item::setqsu(FColDsptr)
{
	//Do nothing.
}

void Item::useEquationNumbers()
{
	//Do nothing.
}

double MbD::Item::value()
{
	assert(false);
	return 0.0;
}

void Item::logString(std::string& str)
{
	this->root()->logString(str);
}

void Item::logString(const char* chars)
{
	std::string str = chars;
	this->logString(str);
}

void MbD::Item::logStringwithArgument(const char*, const char*)
{
	assert(false);
}

void MbD::Item::logStringwithArguments(const char*, std::shared_ptr<std::vector<char*>>)
{
	assert(false);
}

void MbD::Item::normalImpulse(double)
{
	assert(false);
}

void Item::prePosIC()
{
	//"Called once before solving for position initial conditions."
	//"Update all variable dependent instance variables needed for posIC."
	//"This is a subset of update."

	calcPostDynCorrectorIteration();
}

void Item::prePosKine()
{
	this->prePosIC();
}

void MbD::Item::preStatic()
{
	assert(false);
}

void Item::postPosIC()
{
	//Do nothing.
}

void Item::postPosICIteration()
{
	calcPostDynCorrectorIteration();
}

void MbD::Item::postStatic()
{
	assert(false);
}

void MbD::Item::postStaticIteration()
{
	assert(false);
}

void Item::fillPosICError(FColDsptr)
{
	//Do nothing.
}

void Item::fillPosICJacob(SpMatDsptr)
{
	//Do nothing.
}
