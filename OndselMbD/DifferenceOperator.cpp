/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <cmath>

#include "DifferenceOperator.h"
#include "CREATE.h"
#include "SingularMatrixError.h"
#include "FullRow.h"
#include "LDUFullMatParPvRobust.h"

using namespace MbD;

FRowDsptr DifferenceOperator::OneOverFactorials = []() {
	auto oneOverFactorials = std::make_shared<FullRow<double>>(10);
	for (int i = 0; i < oneOverFactorials->size(); i++)
	{
		oneOverFactorials->at(i) = 1.0 / std::tgamma(i + 1);
	}
	return oneOverFactorials;
}();

void DifferenceOperator::calcOperatorMatrix()
{
	//Compute operatorMatrix such that 
	//value(time) : = (operatorMatrix at : 1) timesColumn : series.
	//valuedot(time) : = (operatorMatrix at : 2) timesColumn : series.
	//valueddot(time) : = (operatorMatrix at : 3) timesColumn : series.

	this->formTaylorMatrix();
	try {
		auto matrixSolver = std::make_shared<LDUFullMatParPvRobust>();
		operatorMatrix = matrixSolver->inversesaveOriginal(taylorMatrix, false);
		noop();	//For Debug
	}
	catch (SingularMatrixError ex) {
		assert(false);
	}
}

void DifferenceOperator::initialize()
{
	//Do nothing
}

void MbD::DifferenceOperator::initializeLocally()
{
	assert(false);
}

void DifferenceOperator::setiStep(int i)
{
	iStep = i;
}

void DifferenceOperator::setorder(int o)
{
	order = o;
}

void MbD::DifferenceOperator::formTaylorMatrix()
{
	assert(false);
}

void DifferenceOperator::instantiateTaylorMatrix()
{
	if (taylorMatrix == nullptr || (taylorMatrix->nrow() != (order + 1))) {
		taylorMatrix = std::make_shared<FullMatrix<double>>(order + 1, order + 1);
	}
}

void DifferenceOperator::formTaylorRowwithTimeNodederivative(int i, int ii, int k)
{
	//| rowi hi hipower aij |
	auto& rowi = taylorMatrix->at(i);
	for (int j = 0; j < k; j++)
	{
		rowi->at(j) = 0.0;
	}
	rowi->at(k) = 1.0;
	auto hi = timeNodes->at(ii) - time;
	auto hipower = 1.0;
	for (int j = k + 1; j < order + 1; j++)
	{
		hipower = hipower * hi;
		auto aij = hipower * OneOverFactorials->at((size_t)j - k);
		rowi->atiput(j, aij);
	}
}

void DifferenceOperator::settime(double t)
{
	time = t;
}

void MbD::DifferenceOperator::formDegenerateTaylorRow(int i)
{
	auto& rowi = taylorMatrix->at(i);
	rowi->atiput(0, 1.0);
	for (int i = 1; i < order + 1; i++)
	{
		rowi->atiput(i, 0.0);
	}
}

double MbD::DifferenceOperator::currentStepSize()
{
	return time - timeNodes->at(1);
}

int MbD::DifferenceOperator::direction()
{
	return timeNodes->at(1) < time ? 1 : -1;
}

bool MbD::DifferenceOperator::isConstantStepFor(int nsteps)
{
	auto nPastNodes = timeNodes->size();
	if (nPastNodes < nsteps) return false;
	auto dt = time - timeNodes->at(1);
	auto tol = std::abs(1.0e-6 * dt);
	for (int i = 1; i < nsteps; i++)
	{
		auto dti = timeNodes->at((size_t)i - 1)
			- timeNodes->at(i);
		if (std::abs(dti - dt) > tol) return false;
	}
	return true;
}

bool MbD::DifferenceOperator::isDecreasingStepFor(int nsteps)
{
	auto nPastNodes = timeNodes->size();
	if (nPastNodes < nsteps) return false;
	auto oneMinusTolFactor = 1.0 - 1.0e-6;
	auto dtPast = time - timeNodes->at(1);
	dtPast = std::abs(dtPast);
	for (int i = 1; i < nsteps; i++)
	{
		auto dtNow = dtPast;
		dtPast = timeNodes->at((size_t)i - 1) - timeNodes->at(i);
		dtPast = std::abs(dtPast);

		if (dtNow > (oneMinusTolFactor * dtPast)) return false;
	}
	return true;
}

bool MbD::DifferenceOperator::isIncreasingStepFor(int nsteps)
{
	auto nPastNodes = timeNodes->size();
	if (nPastNodes < ((size_t)nsteps + 1)) return false;
	auto onePlusTolFactor = 1.0 + 1.0e-6;
	auto dtPast = time - timeNodes->at(1);
	dtPast = std::abs(dtPast);
	for (int i = 1; i < nsteps + 1; i++)
	{
		auto dtNow = dtPast;
		dtPast = timeNodes->at((size_t)i - 1) - timeNodes->at(i);
		dtPast = std::abs(dtPast);

		if (dtNow > (onePlusTolFactor * dtPast)) return false;
	}
	return true;
}

FColDsptr MbD::DifferenceOperator::valueWith(std::shared_ptr<std::vector<FColDsptr>> ypast)
{
	//"series stores past values for Extrapolator."
	//"series stores present and past values for BackwardDifference."

	return derivativewith(0, ypast);
}

FColDsptr MbD::DifferenceOperator::derivativewith(int deriv, std::shared_ptr<std::vector<FColDsptr>> series)
{
	//"Answer ith derivative given past values in series."
	auto& coeffs = operatorMatrix->at(deriv);
	auto answer = coeffs->dot(series);
	return std::static_pointer_cast<FullColumn<double>>(answer);
}

FColDsptr MbD::DifferenceOperator::derivativeatpresentpast(int n, double t, FColDsptr y, std::shared_ptr<std::vector<FColDsptr>> ypast)
{
	assert(false);
	return FColDsptr();
}

void MbD::DifferenceOperator::noop()
{
	//No Operations
}
