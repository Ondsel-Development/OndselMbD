/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "RedundantConstraint.h"

using namespace MbD;

void RedundantConstraint::removeRedundantConstraints(std::shared_ptr<std::vector<int>>)
{
}

bool RedundantConstraint::isRedundant()
{
	return true;
}

std::string RedundantConstraint::classname()
{
	auto str = Item::classname() + "->" + constraint->classname();
	return str;
}

ConstraintType RedundantConstraint::type()
{
	return redundant;
}

void MbD::RedundantConstraint::fillqsuddotlam(FColDsptr)
{
}

void RedundantConstraint::fillqsulam(FColDsptr)
{
}

void MbD::RedundantConstraint::fillpqsumu(FColDsptr col)
{
}

void MbD::RedundantConstraint::fillpqsumudot(FColDsptr col)
{
}

void RedundantConstraint::postInput()
{
}

void RedundantConstraint::prePosIC()
{
}

void RedundantConstraint::fillEssenConstraints(std::shared_ptr<Constraint>, std::shared_ptr<std::vector<std::shared_ptr<Constraint>>>)
{
}

void RedundantConstraint::fillDispConstraints(std::shared_ptr<Constraint>, std::shared_ptr<std::vector<std::shared_ptr<Constraint>>>)
{
}

void RedundantConstraint::fillPerpenConstraints(std::shared_ptr<Constraint>, std::shared_ptr<std::vector<std::shared_ptr<Constraint>>>)
{
}

void RedundantConstraint::fillConstraints(std::shared_ptr<Constraint>, std::shared_ptr<std::vector<std::shared_ptr<Constraint>>>)
{
}

void RedundantConstraint::fillRedundantConstraints(std::shared_ptr<Constraint> sptr, std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> redunConstraints)
{
	redunConstraints->push_back(sptr);
}

void RedundantConstraint::setqsulam(FColDsptr)
{
}

void RedundantConstraint::setqsudotlam(FColDsptr)
{
}

void RedundantConstraint::fillPosICError(FColDsptr)
{
}

void RedundantConstraint::fillPosKineError(FColDsptr)
{
}

void RedundantConstraint::fillPosKineJacob(SpMatDsptr)
{
}

void RedundantConstraint::preVelIC()
{
}

void RedundantConstraint::preAccIC()
{
}

void RedundantConstraint::fillAccICIterError(FColDsptr)
{
}

void RedundantConstraint::setqsuddotlam(FColDsptr)
{
}

void RedundantConstraint::discontinuityAtaddTypeTo(double, std::shared_ptr<std::vector<DiscontinuityType>>)
{
	//"Reactivate all constraints."
	assert(false);
	//| newSelf |
	//newSelf : = self constraint.
	//newSelf discontinuityAt : tstartNew addTypeTo : collection.
	//self become : newSelf
}

void MbD::RedundantConstraint::setpqsumu(FColDsptr col)
{
}

void MbD::RedundantConstraint::setpqsumudot(FColDsptr col)
{
}

void MbD::RedundantConstraint::setpqsumuddot(FColDsptr col)
{
}

void MbD::RedundantConstraint::postDynPredictor()
{
}

void MbD::RedundantConstraint::fillDynError(FColDsptr col)
{
}

void MbD::RedundantConstraint::fillpFpy(SpMatDsptr mat)
{
}

void MbD::RedundantConstraint::fillpFpydot(SpMatDsptr mat)
{
}

void MbD::RedundantConstraint::postDynCorrectorIteration()
{
}

void MbD::RedundantConstraint::preDynOutput()
{
}

void MbD::RedundantConstraint::postDynOutput()
{
}
