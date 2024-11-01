/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "VelICSolver.h"
#include "SystemSolver.h"
#include "Part.h"
#include "Constraint.h"

using namespace MbD;

std::shared_ptr<VelICSolver> MbD::VelICSolver::With()
{
	auto inst = std::make_shared<VelICSolver>();
	inst->initialize();
	return inst;
}

void VelICSolver::assignEquationNumbers()
{
	auto parts = system->parts();
	//auto contactEndFrames = system->contactEndFrames();
	//auto uHolders = system->uHolders();
	auto constraints = system->allConstraints();
	size_t eqnNo = 0;
	for (auto& part : *parts) {
		part->iqX(eqnNo);
		eqnNo = eqnNo + 3;
		part->iqE(eqnNo);
		eqnNo = eqnNo + 4;
	}
	//for (auto& endFrm : *contactEndFrames) {
	//	endFrm->is(eqnNo);
	//	eqnNo = eqnNo + endFrm->sSize();
	//}
	//for (auto& uHolder : *uHolders) {
	//	uHolder->iu(eqnNo);
	//	eqnNo += 1;
	//}
	auto nEqns = eqnNo;	//C++ uses index 0.
	nqsu = nEqns;
	for (auto& con : *constraints) {
		con->iG = eqnNo;
		eqnNo += 1;
	}
	//auto lastEqnNo = eqnNo - 1;
	nEqns = eqnNo;	//C++ uses index 0.
	n = nEqns;
}

void VelICSolver::run()
{
	std::string str = "MbD: Solving for velocity initial conditions.";
	system->logString(str);
	runBasic();
}

void VelICSolver::runBasic()
{
	//| qsudotOld qsudotWeights qsudotlam |
		system->partsJointsMotionsDo([](std::shared_ptr<Item> item) { item->preVelIC(); });
		assignEquationNumbers();
		system->partsJointsMotionsDo([](std::shared_ptr<Item> item) { item->useEquationNumbers(); });
		auto qsudotOld = std::make_shared<FullColumn<double>>(nqsu);
		auto qsudotWeights = DiagonalMatrix<double>::With(nqsu);
		errorVector = std::make_shared<FullColumn<double>>(n);
		jacobian = std::make_shared<SparseMatrix<double>>(n, n);
		system->partsJointsMotionsDo([&](std::shared_ptr<Item> item) { item->fillqsudot(qsudotOld); });
		system->partsJointsMotionsDo([&](std::shared_ptr<Item> item) { item->fillqsudotWeights(qsudotWeights); });
		errorVector->zeroSelf();
		errorVector->atplusFullColumn(0, qsudotWeights->timesFullColumn(qsudotOld));
		system->partsJointsMotionsDo([&](std::shared_ptr<Item> item) { item->fillVelICError(errorVector); });
		jacobian->zeroSelf();
		jacobian->atandplusDiagonalMatrix(0, 0, qsudotWeights);
		system->partsJointsMotionsDo([&](std::shared_ptr<Item> item) { item->fillVelICJacob(jacobian); });
		matrixSolver = matrixSolverClassNew();
		solveEquations();
		auto& qsudotlam = x;
		system->partsJointsMotionsDo([&](std::shared_ptr<Item> item) { item->setqsudotlam(qsudotlam); });
		system->partsJointsMotionsDo([](std::shared_ptr<Item> item) { item->postVelIC(); });
}
