/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include<algorithm>
#include <memory>
#include <typeinfo>

#include "JointIJ.h"
#include "Constraint.h"
#include "EndFrameqc.h"
#include "EndFrameqct.h"
#include "RedundantConstraint.h"
#include "MarkerFrame.h"
#include "ForceTorqueData.h"
#include "System.h"

using namespace MbD;

std::shared_ptr<JointIJ> MbD::JointIJ::With()
{
	auto inst = std::make_shared<JointIJ>();
	inst->initialize();
	return inst;
}

std::shared_ptr<JointIJ> MbD::JointIJ::With(const char* str)
{
	auto inst = std::make_shared<JointIJ>(str);
	inst->initialize();
	return inst;
}

void JointIJ::initialize()
{
	constraints = std::make_shared<std::vector<std::shared_ptr<Constraint>>>();
}

void JointIJ::connectsItoJ(EndFrmsptr frmi, EndFrmsptr frmj)
{
	efrmI = frmi;
	efrmJ = frmj;
}

void JointIJ::initializeLocally()
{
	auto frmIqc = std::dynamic_pointer_cast<EndFrameqc>(efrmI);
	if (frmIqc) {
		if (frmIqc->endFrameqct) {
			efrmI = frmIqc->endFrameqct;
		}
	}
	constraintsDo([](std::shared_ptr<Constraint> constraint) { constraint->initializeLocally(); });
}

void JointIJ::initializeGlobally()
{
	constraintsDo([](std::shared_ptr<Constraint> constraint) { constraint->initializeGlobally(); });
}

void JointIJ::constraintsDo(const std::function<void(std::shared_ptr<Constraint>)>& f) const
{
	std::for_each(constraints->begin(), constraints->end(), f);
}

void JointIJ::postInput()
{
	constraintsDo([](std::shared_ptr<Constraint> constraint) { constraint->postInput(); });

}

void JointIJ::addConstraint(std::shared_ptr<Constraint> con)
{
	con->container = this;
	constraints->push_back(con);
}

FColDsptr MbD::JointIJ::aFIeJtIe() const
{
	//"aFIeJtIe is joint force on end frame Ie expresses in Ie components."
	auto frmIqc = std::dynamic_pointer_cast<EndFrameqc>(efrmI);
	return frmIqc->aAeO()->timesFullColumn(aFIeJtO());
}

FColDsptr MbD::JointIJ::aFIeJtO() const
{
	//"aFIeJtO is joint force on end frame Ie expresses in O components."
	auto aFIeJtO = std::make_shared <FullColumn<double>>(3);
	constraintsDo([&](std::shared_ptr<Constraint> con) { con->addToJointForceI(aFIeJtO); });
	return aFIeJtO;
}

void JointIJ::prePosIC()
{
	constraintsDo([](std::shared_ptr<Constraint> constraint) { constraint->prePosIC(); });
}

void JointIJ::prePosKine()
{
	constraintsDo([](std::shared_ptr<Constraint> constraint) { constraint->prePosKine(); });
}

void JointIJ::fillEssenConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> essenConstraints)
{
	constraintsDo([&](std::shared_ptr<Constraint> con) { con->fillEssenConstraints(con, essenConstraints); });
}

void JointIJ::fillDispConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> dispConstraints)
{
	constraintsDo([&](std::shared_ptr<Constraint> con) { con->fillDispConstraints(con, dispConstraints); });
}

void JointIJ::fillPerpenConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> perpenConstraints)
{
	constraintsDo([&](std::shared_ptr<Constraint> con) { con->fillPerpenConstraints(con, perpenConstraints); });
}

void JointIJ::fillRedundantConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> redunConstraints)
{
	constraintsDo([&](std::shared_ptr<Constraint> con) { con->fillRedundantConstraints(con, redunConstraints); });
}

void JointIJ::fillConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> allConstraints)
{
	constraintsDo([&](std::shared_ptr<Constraint> con) { con->fillConstraints(con, allConstraints); });
}

void JointIJ::fillqsulam(FColDsptr col)
{
	constraintsDo([&](std::shared_ptr<Constraint> con) { con->fillqsulam(col); });
}

void MbD::JointIJ::fillpqsumu(FColDsptr col)
{
	constraintsDo([&](std::shared_ptr<Constraint> con) { con->fillpqsumu(col); });
}

void MbD::JointIJ::fillpqsumudot(FColDsptr col)
{
	constraintsDo([&](std::shared_ptr<Constraint> con) { con->fillpqsumudot(col); });
}

void JointIJ::fillqsudot(FColDsptr col)
{
	constraintsDo([&](std::shared_ptr<Constraint> con) { con->fillqsudot(col); });
}

void JointIJ::useEquationNumbers()
{
	constraintsDo([](std::shared_ptr<Constraint> constraint) { constraint->useEquationNumbers(); });
}

void MbD::JointIJ::setpqsumu(FColDsptr col)
{
	constraintsDo([&](std::shared_ptr<Constraint> con) { con->setpqsumu(col); });
}

void MbD::JointIJ::setpqsumudot(FColDsptr col)
{
	constraintsDo([&](std::shared_ptr<Constraint> con) { con->setpqsumudot(col); });
}

void MbD::JointIJ::postDynPredictor()
{
	constraintsDo([](std::shared_ptr<Constraint> con) { con->postDynPredictor(); });
}

void MbD::JointIJ::fillDynError(FColDsptr col)
{
	constraintsDo([&](std::shared_ptr<Constraint> con) { con->fillDynError(col); });
}

void MbD::JointIJ::fillpFpy(SpMatDsptr mat)
{
	constraintsDo([&](std::shared_ptr<Constraint> con) { con->fillpFpy(mat); });
}

void MbD::JointIJ::fillpFpydot(SpMatDsptr mat)
{
	constraintsDo([&](std::shared_ptr<Constraint> con) { con->fillpFpydot(mat); });
}

void MbD::JointIJ::postDynCorrectorIteration()
{
	constraintsDo([](std::shared_ptr<Constraint> con) { con->postDynCorrectorIteration(); });
}

void MbD::JointIJ::postDynOutput()
{
	constraintsDo([](std::shared_ptr<Constraint> con) { con->postDynOutput(); });
}

void MbD::JointIJ::preDynOutput()
{
	constraintsDo([](std::shared_ptr<Constraint> con) { con->preDynOutput(); });
}

void JointIJ::setqsulam(FColDsptr col)
{
	constraintsDo([&](std::shared_ptr<Constraint> con) { con->setqsulam(col); });
}

void MbD::JointIJ::setpqsumuddot(FColDsptr col)
{
	constraintsDo([&](std::shared_ptr<Constraint> con) { con->setpqsumuddot(col); });
}

void JointIJ::setqsudotlam(FColDsptr col)
{
	constraintsDo([&](std::shared_ptr<Constraint> con) { con->setqsudotlam(col); });
}

void JointIJ::postPosICIteration()
{
	constraintsDo([](std::shared_ptr<Constraint> constraint) { constraint->postPosICIteration(); });
}

void JointIJ::fillPosICError(FColDsptr col)
{
	constraintsDo([&](std::shared_ptr<Constraint> con) { con->fillPosICError(col); });
}

void JointIJ::fillPosICJacob(SpMatDsptr mat)
{
	constraintsDo([&](std::shared_ptr<Constraint> con) { con->fillPosICJacob(mat); });
}

void JointIJ::removeRedundantConstraints(std::shared_ptr<std::vector<size_t>> redundantEqnNos)
{
	for (size_t i = 0; i < constraints->size(); i++)
	{
		auto& constraint = constraints->at(i);
		if (std::find(redundantEqnNos->begin(), redundantEqnNos->end(), constraint->iG) != redundantEqnNos->end()) {
			auto redunCon = RedundantConstraint::With();
			redunCon->constraint = constraint;
			constraints->at(i) = redunCon;
		}
	}
}

void JointIJ::reactivateRedundantConstraints()
{
	for (size_t i = 0; i < constraints->size(); i++)
	{
		auto& con = constraints->at(i);
		if (con->isRedundant()) {
			constraints->at(i) = std::static_pointer_cast<RedundantConstraint>(con)->constraint;
		}
	}
}

void JointIJ::constraintsReport()
{
	auto redunCons = std::make_shared<std::vector<std::shared_ptr<Constraint>>>();
	constraintsDo([&](std::shared_ptr<Constraint> con) {
		if (con->isRedundant()) {
			redunCons->push_back(con);
		}
		});
	if (redunCons->size() > 0) {
		std::string str = "MbD: " + classname() + std::string(" ") + name + " has the following constraint(s) removed: ";
		logString(str);
		std::for_each(redunCons->begin(), redunCons->end(), [&](auto& con) {
			str = "MbD: " + std::string("    ") + con->classname();
			logString(str);
			});
	}
}

void JointIJ::postPosIC()
{
	constraintsDo([](std::shared_ptr<Constraint> constraint) { constraint->postPosIC(); });
}

void JointIJ::preDyn()
{
	constraintsDo([](std::shared_ptr<Constraint> constraint) { constraint->preDyn(); });
}

void JointIJ::fillPosKineError(FColDsptr col)
{
	constraintsDo([&](std::shared_ptr<Constraint> con) { con->fillPosKineError(col); });
}

void JointIJ::fillPosKineJacob(SpMatDsptr mat)
{
	constraintsDo([&](std::shared_ptr<Constraint> constraint) { constraint->fillPosKineJacob(mat); });
}

void MbD::JointIJ::fillqsuddotlam(FColDsptr col)
{
	constraintsDo([&](std::shared_ptr<Constraint> constraint) { constraint->fillqsuddotlam(col); });
}

void JointIJ::preVelIC()
{
	constraintsDo([](std::shared_ptr<Constraint> constraint) { constraint->preVelIC(); });
}

void JointIJ::fillVelICError(FColDsptr col)
{
	constraintsDo([&](std::shared_ptr<Constraint> con) { con->fillVelICError(col); });
}

void JointIJ::fillVelICJacob(SpMatDsptr mat)
{
	constraintsDo([&](std::shared_ptr<Constraint> constraint) { constraint->fillVelICJacob(mat); });
}

void JointIJ::preAccIC()
{
	constraintsDo([](std::shared_ptr<Constraint> constraint) { constraint->preAccIC(); });
}

void JointIJ::fillAccICIterError(FColDsptr col)
{
	constraintsDo([&](std::shared_ptr<Constraint> con) { con->fillAccICIterError(col); });
}

void JointIJ::fillAccICIterJacob(SpMatDsptr mat)
{
	constraintsDo([&](std::shared_ptr<Constraint> con) { con->fillAccICIterJacob(mat); });
}

void JointIJ::setqsuddotlam(FColDsptr col)
{
	constraintsDo([&](std::shared_ptr<Constraint> con) { con->setqsuddotlam(col); });
}

std::shared_ptr<StateData> JointIJ::stateData()
{
	//"
	//MbD returns aFIeO and aTIeO.
	//GEO needs aFImO and aTImO.
	//For Motion rImIeO is not zero and is changing.
	//aFImO : = aFIeO.
	//aTImO : = aTIeO + (rImIeO cross : aFIeO).
	//"

	auto answer = std::make_shared<ForceTorqueData>();
	auto aFIeO = aFX();
	auto aTIeO = aTX();
	auto rImIeO = efrmI->rmeO();
	answer->aFIO = aFIeO;
	answer->aTIO = aTIeO->plusFullColumn(rImIeO->cross(aFIeO));
	return answer;
}

FColDsptr JointIJ::aFX() const
{
	return jointForceI();
}

FColDsptr MbD::JointIJ::aTIeJtIe() const
{
	//"aTIeJtIe is torque on part containing end frame Ie expressed in Ie components."
	return efrmI->aAeO()->timesFullColumn(aTIeJtO());
}

FColDsptr MbD::JointIJ::aTIeJtO() const
{
	//"aTIeJtO is torque on part containing end frame Ie expressed in O components."
	auto aTIeJtO = std::make_shared <FullColumn<double>>(3);
	constraintsDo([&](std::shared_ptr<Constraint> con) { con->addToJointTorqueI(aTIeJtO); });
	return aTIeJtO;
}

FColDsptr JointIJ::jointForceI() const
{
	//"jointForceI is force on MbD marker I."
	auto jointForce = std::make_shared <FullColumn<double>>(3);
	constraintsDo([&](std::shared_ptr<Constraint> con) { con->addToJointForceI(jointForce); });
	return jointForce;
}

FColDsptr JointIJ::aTX() const
{
	return jointTorqueI();
}

FColDsptr JointIJ::jointTorqueI() const
{
	//"jointTorqueI is torque on MbD marker I."
	auto jointTorque = std::make_shared <FullColumn<double>>(3);
	constraintsDo([&](std::shared_ptr<Constraint> con) { con->addToJointTorqueI(jointTorque); });
	return jointTorque;
}

void JointIJ::postDynStep()
{
	constraintsDo([](std::shared_ptr<Constraint> constraint) { constraint->postDynStep(); });
}
