/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include <iostream>
#include <limits>
#include <memory>
#include <chrono>

#include "MatrixSolver.h"
#include "SparseMatrix.h"
#include "FullMatrix.h"
#include "SingularMatrixError.h"

using namespace MbD;

void MatrixSolver::initialize()
{
	Solver::initialize();
	singularPivotTolerance = 4 * std::numeric_limits<double>::epsilon();
}

void MatrixSolver::setSystem(Solver*)
{
	assert(false);
}

FColDsptr MatrixSolver::solvewithsaveOriginal(SpMatDsptr spMat, FColDsptr fullCol, bool saveOriginal)
{
	this->timedSolvewithsaveOriginal(spMat, fullCol, saveOriginal);
	return answerX;
}

FColDsptr MatrixSolver::solvewithsaveOriginal(FMatDsptr fullMat, FColDsptr fullCol, bool saveOriginal)
{
	this->timedSolvewithsaveOriginal(fullMat, fullCol, saveOriginal);
	return answerX;
}

FColDsptr MatrixSolver::timedSolvewithsaveOriginal(SpMatDsptr spMat, FColDsptr fullCol, bool saveOriginal)
{
	auto start = std::chrono::steady_clock::now();

	this->basicSolvewithsaveOriginal(spMat, fullCol, saveOriginal);

	auto end = std::chrono::steady_clock::now();
	auto diff = end - start;
	millisecondsToRun = std::chrono::duration<double, std::milli>(diff).count();
	//std::cout << "milliseconds to run = " << millisecondsToRun << std::endl;
	return answerX;
}

FColDsptr MatrixSolver::timedSolvewithsaveOriginal(FMatDsptr, FColDsptr, bool)
{
	assert(false);
	return FColDsptr();
}

FColDsptr MbD::MatrixSolver::basicSolvewithsaveOriginal(FMatDsptr fullMat, FColDsptr fullCol, bool saveOriginal)
{
	assert(false);
	return FColDsptr();
}

FColDsptr MbD::MatrixSolver::basicSolvewithsaveOriginal(SpMatDsptr spMat, FColDsptr fullCol, bool saveOriginal)
{
	assert(false);
	return FColDsptr();
}

void MbD::MatrixSolver::preSolvewithsaveOriginal(FMatDsptr fullMat, FColDsptr fullCol, bool saveOriginal)
{
	assert(false);
}

void MbD::MatrixSolver::preSolvewithsaveOriginal(SpMatDsptr spMat, FColDsptr fullCol, bool saveOriginal)
{
	assert(false);
}

void MbD::MatrixSolver::doPivoting(size_t p)
{
	assert(false);
}

void MbD::MatrixSolver::forwardEliminateWithPivot(size_t p)
{
	assert(false);
}

void MbD::MatrixSolver::backSubstituteIntoDU()
{
	assert(false);
}

void MbD::MatrixSolver::postSolve()
{
	assert(false);
}

void MatrixSolver::findScalingsForRowRange(size_t begin, size_t end)
{
	//"Row element * scaling <= 1.0."
	rowScalings = std::make_shared<FullColumn<double>>(m);
	for (size_t i = begin; i < end; i++)
	{
		double maxRowMagnitude = this->getmatrixArowimaxMagnitude(i);
		if (maxRowMagnitude == 0.0) throwSingularMatrixError("");
		rowScalings->at(i) = 1.0 / maxRowMagnitude;
	}
}

double MbD::MatrixSolver::getmatrixArowimaxMagnitude(size_t i)
{
	assert(false);
	return 0.0;
}

void MatrixSolver::throwSingularMatrixError(const char* chars)
{
	throw SingularMatrixError(chars);
}

void MatrixSolver::throwSingularMatrixError(const char* chars, std::shared_ptr<FullColumn<size_t>> redunEqnNos)
{
	throw SingularMatrixError(chars, redunEqnNos);
}
