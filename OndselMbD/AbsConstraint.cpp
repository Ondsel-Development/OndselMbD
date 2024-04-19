/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "AbsConstraint.h"
#include "PartFrame.h"

using namespace MbD;

AbsConstraint::AbsConstraint(size_t i)
{
	axis = i;
}

std::shared_ptr<AbsConstraint> MbD::AbsConstraint::With(size_t axis)
{
	auto inst = std::make_shared<AbsConstraint>(axis);
	inst->initialize();
	return inst;
}

void AbsConstraint::calcPostDynCorrectorIteration()
{
	if (axis < 3) {
		aG = static_cast<PartFrame*>(owner)->qX->at(axis);
	}
	else {
		aG = static_cast<PartFrame*>(owner)->qE->at(axis - 3);
	}
}

void AbsConstraint::useEquationNumbers()
{
	iqXminusOnePlusAxis = static_cast<PartFrame*>(owner)->iqX + axis;
}

void MbD::AbsConstraint::fillpFpy(SpMatDsptr mat)
{
	mat->atandplusNumber(iG, iqXminusOnePlusAxis, 1.0);
}

void MbD::AbsConstraint::fillpFpydot(SpMatDsptr mat)
{
	mat->atandplusNumber(iqXminusOnePlusAxis, iG, 1.0);
}

void AbsConstraint::fillPosICJacob(SpMatDsptr mat)
{
	mat->atandplusNumber(iG, iqXminusOnePlusAxis, 1.0);
	mat->atandplusNumber(iqXminusOnePlusAxis, iG, 1.0);
}

void AbsConstraint::fillPosICError(FColDsptr col)
{
	Constraint::fillPosICError(col);
	col->atplusNumber(iqXminusOnePlusAxis, lam);
}

void AbsConstraint::fillPosKineJacob(SpMatDsptr mat)
{
	mat->atandplusNumber(iG, iqXminusOnePlusAxis, 1.0);
}

void AbsConstraint::fillVelICJacob(SpMatDsptr mat)
{
	this->fillPosICJacob(mat);
}

void AbsConstraint::fillAccICIterError(FColDsptr col)
{
	col->atplusNumber(iqXminusOnePlusAxis, lam);
	auto partFrame = static_cast<PartFrame*>(owner);
		double sum;
		if (axis < 3) {
			sum = partFrame->qXddot->at(axis);
		}
		else {
			sum = partFrame->qEddot->at(axis - 3);
		}
		col->atplusNumber(iG, sum);
}
