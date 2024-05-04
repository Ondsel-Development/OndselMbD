/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "VelKineSolver.h"
#include "NotKinematicError.h"
#include "SystemSolver.h"
#include "Part.h"
#include "Constraint.h"

using namespace MbD;

std::shared_ptr<VelKineSolver> MbD::VelKineSolver::With()
{
	auto inst = std::make_shared<VelKineSolver>();
	inst->initialize();
	return inst;
}

void VelKineSolver::assignEquationNumbers()
{
	//"Equation order is q,s,u."
	auto parts = system->parts();
	//auto contactEndFrames = system->contactEndFrames();
	//auto uHolders = system->uHolders();
	auto constraints = system->allConstraints();
	size_t varNo = 0;
	for (auto& part : *parts) {
		part->iqX(varNo);
		varNo = varNo + 3;
		part->iqE(varNo);
		varNo = varNo + 4;
	}
	//for (auto& endFrm : *contactEndFrames) {
	//	endFrm->is(varNo);
	//	varNo = varNo + endFrm->sSize();
	//}
	//for (auto& uHolder : *uHolders) {
	//	uHolder->iu(varNo);
	//	varNo += 1;
	//}
	auto eqnNo = 0;
	for (auto& con : *constraints) {
		con->iG = eqnNo;
		eqnNo += 1;
	}
	n = eqnNo;	//C++ uses index 0.
	if (varNo != eqnNo) {
		throw NotKinematicError("");
	}
}

void VelKineSolver::run()
{
	system->Solver::logString("MbD: Solving for kinematic velocity.");
	system->partsJointsMotionsDo([](std::shared_ptr<Item> item) { item->preVelIC(); });
	assignEquationNumbers();
	system->partsJointsMotionsDo([](std::shared_ptr<Item> item) { item->useEquationNumbers(); });
	errorVector = std::make_shared<FullColumn<double>>(n);
	jacobian = std::make_shared<SparseMatrix<double>>(n, n);
	errorVector->zeroSelf();
	system->partsJointsMotionsDo([&](std::shared_ptr<Item> item) { item->fillVelICError(errorVector); });
	jacobian->zeroSelf();
	system->partsJointsMotionsDo([&](std::shared_ptr<Item> item) { item->fillPosKineJacob(jacobian); });
	matrixSolver = matrixSolverClassNew();
	//outputSpreadsheet();
	solveEquations();
	auto& qsudot = x;
	system->partsJointsMotionsDo([&](std::shared_ptr<Item> item) { item->setqsudot(qsudot); });
	system->partsJointsMotionsDo([](std::shared_ptr<Item> item) { item->postVelIC(); });
}

void MbD::VelKineSolver::outputSpreadsheet()
{
	std::ofstream os("../testapp/spreadsheetcpp.csv");
	os << std::setprecision(std::numeric_limits<double>::max_digits10);
	for (size_t i = 0; i < jacobian->nrow(); i++)
	{
		auto rowi = jacobian->at(i);
		for (size_t j = 0; j < jacobian->ncol(); j++)
		{
			if (rowi->find(j) == rowi->end()) {
				os << 0.0;
			}
			else {
				os << rowi->at(j);
			}
			os << '\t';
		}
		os << "\t" << errorVector->at(i) << std::endl;
	}
}
