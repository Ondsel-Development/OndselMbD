/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "FunctionWithManyArgs.h"
#include "Symbolic.h"

using namespace MbD;

FunctionWithManyArgs::FunctionWithManyArgs()
{
	terms = std::make_shared<std::vector<Symsptr>>();
}

FunctionWithManyArgs::FunctionWithManyArgs(Symsptr term) : FunctionWithManyArgs()
{
	terms->push_back(term);
}

FunctionWithManyArgs::FunctionWithManyArgs(Symsptr term, Symsptr term1) : FunctionWithManyArgs(term)
{
	terms->push_back(term1);
}

FunctionWithManyArgs::FunctionWithManyArgs(Symsptr term, Symsptr term1, Symsptr term2) : FunctionWithManyArgs(term, term1)
{
	terms->push_back(term2);
}

FunctionWithManyArgs::FunctionWithManyArgs(std::shared_ptr<std::vector<Symsptr>> _terms) {
	terms = std::make_shared<std::vector<Symsptr>>();
	for (size_t i = 0; i < _terms->size(); i++)
		terms->push_back(_terms->at(i));
}

std::shared_ptr<FunctionWithManyArgs> MbD::FunctionWithManyArgs::With()
{
	auto inst = std::make_shared<FunctionWithManyArgs>();
	inst->initialize();
	return inst;
}

std::shared_ptr<std::vector<Symsptr>> FunctionWithManyArgs::getTerms()
{
	return terms;
}

void MbD::FunctionWithManyArgs::createMbD()
{
	for (auto& term : *terms) term->createMbD();
}

void MbD::FunctionWithManyArgs::arguments(Symsptr)
{
	assert(false);
}

bool MbD::FunctionWithManyArgs::isConstant()
{
	for (auto& term : *terms) {
		if (!term->isConstant()) return false;
	}
	return true;
}

void MbD::FunctionWithManyArgs::fillKineIJs(std::shared_ptr<std::vector<std::shared_ptr<MbDSymbolicFunction>>> kineIJs)
{
	for (auto& term : *terms) {
		term->fillKineIJs(kineIJs);
	}
}

void MbD::FunctionWithManyArgs::fillKinedotIJs(std::shared_ptr<std::vector<std::shared_ptr<MbDSymbolicFunction>>> kinedotIJs)
{
	for (auto& term : *terms) {
		term->fillKinedotIJs(kinedotIJs);
	}
}

void MbD::FunctionWithManyArgs::fillJointForces(std::shared_ptr<std::vector<std::shared_ptr<MbDSymbolicFunction>>> jointForces)
{
	for (auto& term : *terms) {
		term->fillJointForces(jointForces);
	}
}

void MbD::FunctionWithManyArgs::fillJointTorques(std::shared_ptr<std::vector<std::shared_ptr<MbDSymbolicFunction>>> jointTorques)
{
	for (auto& term : *terms) {
		term->fillJointTorques(jointTorques);
	}
}

