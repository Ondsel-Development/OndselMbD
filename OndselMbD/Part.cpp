/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "Part.h"
#include "PartFrame.h"
#include "System.h"
#include "EulerParameters.h"
#include "PosVelAccData.h"
#include "FullColumn.h"
#include "FullMatrix.h"
#include "DiagonalMatrix.h"


using namespace MbD;

std::shared_ptr<Part> MbD::Part::With()
{
	auto inst = std::make_shared<Part>();
	inst->initialize();
	return inst;
}

std::shared_ptr<Part> MbD::Part::With(const char* str)
{
	auto inst = std::make_shared<Part>(str);
	inst->initialize();
	return inst;
}

void Part::initialize()
{
	partFrame = PartFrame::With();
	partFrame->setPart(this);
	pTpE = std::make_shared<FullColumn<double>>(4);
	ppTpEpE = FullMatrix<double>::With(4, 4);
	ppTpEpEdot = FullMatrix<double>::With(4, 4);
}

System* MbD::Part::root()
{
	return system;
}

void Part::initializeLocally()
{
	partFrame->initializeLocally();
	if (m > 0) {
		mX = DiagonalMatrix<double>::With(3, m);
	}
	else {
		mX = DiagonalMatrix<double>::With(3, 0.0);
	}
}

void Part::initializeGlobally()
{
	partFrame->initializeGlobally();
}

void Part::setqX(FColDsptr x) const {
	partFrame->setqX(x);
}

FColDsptr Part::getqX() const {
	return partFrame->getqX();
}

void Part::setaAap(FMatDsptr mat) {
	partFrame->setaAap(mat);
}

void Part::setqE(FColDsptr x) {
	partFrame->setqE(x);
}

FColDsptr Part::getqE() {
	return partFrame->getqE();
}

void Part::setqXdot(FColDsptr x) {
	partFrame->setqXdot(x);
}

FColDsptr Part::getqXdot() {
	return partFrame->getqXdot();
}

void Part::setomeOpO(FColDsptr x) {
	partFrame->setomeOpO(x);
}

FColDsptr Part::getomeOpO() {
	return partFrame->getomeOpO();
}

void Part::setqXddot(FColDsptr x)
{
	partFrame->setqXddot(x);
}

FColDsptr Part::getqXddot()
{
	return partFrame->getqXddot();
}

void Part::setqEddot(FColDsptr x)
{
	partFrame->setqEddot(x);
}

FColDsptr Part::getqEddot()
{
	return partFrame->getqEddot();
}

void Part::qX(FColDsptr x)
{
	partFrame->qX = x;
}

FColDsptr Part::qX()
{
	return partFrame->qX;
}

void Part::qE(std::shared_ptr<EulerParameters<double>> x)
{
	partFrame->qE = x;
}

std::shared_ptr<EulerParameters<double>> Part::qE()
{
	return partFrame->qE;
}

void Part::qXdot(FColDsptr x)
{
	partFrame->qXdot = x;
}

FColDsptr Part::qXdot()
{
	return partFrame->qXdot;
}

void Part::omeOpO(FColDsptr x)
{
	partFrame->setomeOpO(x);
}

FColDsptr Part::omeOpO()
{
	return partFrame->omeOpO();
}

void Part::qXddot(FColDsptr x)
{
	partFrame->qXddot = x;
}

FColDsptr Part::qXddot()
{
	return partFrame->qXddot;
}

void Part::qEddot(FColDsptr x)
{
	//ToDo: Should store EulerParametersDDot
	//ToDo: Need alpOpO too
	partFrame->qEddot = x;
}

FColDsptr Part::qEddot()
{
	return partFrame->qEddot;
}

FMatDsptr Part::aAOp()
{
	return partFrame->aAOp();
}

FColDsptr Part::alpOpO()
{
	return partFrame->alpOpO();
}

void Part::setSystem(System* sys)
{
	system = sys;
}

void Part::asFixed()
{
	partFrame->asFixed();
}

void Part::postInput()
{
	partFrame->postInput();
	Item::postInput();
}

void Part::calcPostDynCorrectorIteration()
{
	calcmE();
	calcmEdot();
	calcpTpE();
	calcppTpEpE();
	calcppTpEpEdot();
}

void Part::prePosIC()
{
	partFrame->prePosIC();
}

void Part::prePosKine()
{
	partFrame->prePosKine();
}

size_t MbD::Part::iqX()
{
	return partFrame->iqX;
}

size_t MbD::Part::iqE()
{
	return partFrame->iqE;
}

void Part::iqX(size_t eqnNo)
{
	partFrame->iqX = eqnNo;
}

void Part::iqE(size_t eqnNo)
{
	partFrame->iqE = eqnNo;

}

void Part::fillEssenConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> essenConstraints)
{
	partFrame->fillEssenConstraints(essenConstraints);
}

void Part::fillRedundantConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> redunConstraints)
{
	partFrame->fillRedundantConstraints(redunConstraints);
}

void Part::fillConstraints(std::shared_ptr<std::vector<std::shared_ptr<Constraint>>> allConstraints)
{
	partFrame->fillConstraints(allConstraints);
}

void Part::fillqsu(FColDsptr col)
{
	partFrame->fillqsu(col);
}

void Part::fillqsuWeights(DiagMatDsptr diagMat)
{
	//"Map wqX and wqE according to inertias. (0 to maximum inertia) map to (minw to maxw)"
	//"When the inertias are zero, they are set to a small number for positive definiteness."
	//"They are not set to zero because inertialess part may be underconstrained."
	//"Avoid having two kinds of singularities to confuse redundant constraint removal."
	//"Redundant constraint removal likes equal weights."
	//"wqE(4) = 0.0d is ok because there is always the euler parameter constraint."

	auto mMax = root()->maximumMass();
	auto aJiMax = root()->maximumMomentOfInertia();
	double minw = 1.0e3;
	double maxw = 1.0e6;
	auto wqX = DiagonalMatrix<double>::With(3);
	auto wqE = DiagonalMatrix<double>::With(4);
	if (mMax == 0) { mMax = 1.0; }
	for (size_t i = 0; i < 3; i++)
	{
		wqX->at(i) = (maxw * m / mMax) + minw;
	}
	if (aJiMax == 0) { aJiMax = 1.0; }
	for (size_t i = 0; i < 3; i++)
	{
		auto aJi = aJ->at(i);
		wqE->at(i) = (maxw * aJi / aJiMax) + minw;
	}
	wqE->at(3) = minw;
	diagMat->atputDiagonalMatrix(partFrame->iqX, wqX);
	diagMat->atputDiagonalMatrix(partFrame->iqE, wqE);
	partFrame->fillqsuWeights(diagMat);
}

void MbD::Part::fillqsuddotlam(FColDsptr col)
{
	partFrame->fillqsuddotlam(col);
}

void Part::fillqsulam(FColDsptr col)
{
	partFrame->fillqsulam(col);
}

void MbD::Part::fillpqsumu(FColDsptr col)
{
	col->atputFullColumn(ipX, pX);
	col->atputFullColumn(ipE, pE);
	partFrame->fillpqsumu(col);
}

void MbD::Part::fillpqsumudot(FColDsptr col)
{
	col->atputFullColumn(ipX, pXdot);
	col->atputFullColumn(ipE, pEdot);
	partFrame->fillpqsumudot(col);
}

void Part::fillqsudot(FColDsptr col)
{
	partFrame->fillqsudot(col);
}

void Part::fillqsudotWeights(DiagMatDsptr diagMat)
{
	//"wqXdot and wqEdot are set to their respective inertias."
	//"When the inertias are zero, they are set to a small number for positive definiteness."
	//"They are not set to zero because inertialess part may be underconstrained."
	//"wqEdot(4) = 0.0d is ok because there is always the euler parameter constraint."

		//| mMax aJiMax maxInertia minw maxw aJi wqXdot wqEdot |
	auto mMax = root()->maximumMass();
	auto aJiMax = root()->maximumMomentOfInertia();
	double maxInertia = std::max(mMax, aJiMax);
	if (maxInertia == 0) maxInertia = 1.0;
	double minw = 1.0e-12 * maxInertia;
	double maxw = maxInertia;
	auto wqXdot = DiagonalMatrix<double>::With(3);
	auto wqEdot = DiagonalMatrix<double>::With(4);
	for (size_t i = 0; i < 3; i++)
	{
		wqXdot->at(i) = (maxw * m / maxInertia) + minw;
		auto aJi = aJ->at(i);
		wqEdot->at(i) = (maxw * aJi / maxInertia) + minw;
	}
	wqEdot->at(3) = minw;
	diagMat->atputDiagonalMatrix(partFrame->iqX, wqXdot);
	diagMat->atputDiagonalMatrix(partFrame->iqE, wqEdot);
	partFrame->fillqsudotWeights(diagMat);
}

void Part::useEquationNumbers()
{
	partFrame->useEquationNumbers();
}

void Part::setqsu(FColDsptr col)
{
	partFrame->setqsu(col);
}

void Part::setqsulam(FColDsptr col)
{
	partFrame->setqsulam(col);
}

void Part::setqsudot(FColDsptr col)
{
	partFrame->setqsudot(col);
}

void Part::setqsudotlam(FColDsptr col)
{
	partFrame->setqsudotlam(col);
}

void Part::postPosICIteration()
{
	partFrame->postPosICIteration();
}

void Part::fillPosICError(FColDsptr col)
{
	partFrame->fillPosICError(col);
}

void Part::fillPosICJacob(SpMatDsptr mat)
{
	partFrame->fillPosICJacob(mat);
}

void Part::removeRedundantConstraints(std::shared_ptr<std::vector<size_t>> redundantEqnNos)
{
	partFrame->removeRedundantConstraints(redundantEqnNos);
}

void Part::reactivateRedundantConstraints()
{
	partFrame->reactivateRedundantConstraints();
}

void Part::constraintsReport()
{
	partFrame->constraintsReport();
}

void Part::postPosIC()
{
	partFrame->postPosIC();
	calcmE();
}

void Part::preDyn()
{
	partFrame->preDyn();
}

void Part::storeDynState()
{
	partFrame->storeDynState();
}

void Part::fillPosKineError(FColDsptr col)
{
	partFrame->fillPosKineError(col);
}

void Part::fillPosKineJacob(SpMatDsptr mat)
{
	partFrame->fillPosKineJacob(mat);
}

void Part::preVelIC()
{
	partFrame->preVelIC();
}

void Part::postVelIC()
{
	partFrame->postVelIC();
	calcp();
	calcmEdot();
	calcpTpE();
	calcppTpEpE();
	calcppTpEpEdot();
}

void Part::fillVelICError(FColDsptr col)
{
	partFrame->fillVelICError(col);
}

void Part::fillVelICJacob(SpMatDsptr mat)
{
	partFrame->fillVelICJacob(mat);
}

void Part::preAccIC()
{
	partFrame->preAccIC();
	Item::preAccIC();
}

void Part::calcp()
{
	pX = mX->timesFullColumn(partFrame->qXdot);
	pE = mE->timesFullColumn(partFrame->qEdot);
}

void Part::calcpdot()
{
	pXdot = mX->timesFullColumn(partFrame->qXddot);
	pEdot = mEdot->timesFullColumn(partFrame->qEdot)->plusFullColumn(mE->timesFullColumn(partFrame->qEddot));
}

void Part::calcmEdot()
{
	auto aC = partFrame->aC();
	auto aCdot = partFrame->aCdot();
	auto a4J = aJ->times(4.0);
	auto term1 = aC->transposeTimesFullMatrix(a4J->timesFullMatrix(aCdot));
	auto term2 = term1->transpose();
	mEdot = term1->plusFullMatrix(term2);
}

void Part::calcpTpE()
{
	//"pTpE is a column vector."
	auto& qEdot = partFrame->qEdot;
	auto aC = partFrame->aC();
	auto pCpEtimesqEdot = EulerParameters<double>::pCpEtimesColumn(qEdot);
	pTpE = (pCpEtimesqEdot->transposeTimesFullColumn(aJ->timesFullColumn(aC->timesFullColumn(qEdot))))->times(4.0);
}

void Part::calcppTpEpE()
{
	auto& qEdot = partFrame->qEdot;
	auto pCpEtimesqEdot = EulerParameters<double>::pCpEtimesColumn(qEdot);
	auto a4J = aJ->times(4.0);
	ppTpEpE = pCpEtimesqEdot->transposeTimesFullMatrix(a4J->timesFullMatrix(pCpEtimesqEdot));
}

void Part::calcppTpEpEdot()
{
	//| qEdot aC a4J term1 pCpEtimesqEdot term2 |
	auto& qEdot = partFrame->qEdot;
	auto aC = partFrame->aC();
	auto a4J = aJ->times(4.0);
	auto term1 = EulerParameters<double>::pCTpEtimesColumn(a4J->timesFullColumn(aC->timesFullColumn(qEdot)));
	auto pCpEtimesqEdot = EulerParameters<double>::pCpEtimesColumn(qEdot);
	auto term2 = aC->transposeTimesFullMatrix(a4J->timesFullMatrix(pCpEtimesqEdot));
	ppTpEpEdot = term1->plusFullMatrix(term2)->transpose();
}

void Part::calcmE()
{
	auto aC = partFrame->aC();
	mE = aC->transposeTimesFullMatrix(aJ->timesFullMatrix(aC))->times(4.0);
}

void Part::fillAccICIterError(FColDsptr col)
{
	//ToDo: Check for Units effect.
	auto iqX = partFrame->iqX;
	auto iqE = partFrame->iqE;
	col->atminusFullColumn(iqX, mX->timesFullColumn(partFrame->qXddot));
	col->atminusFullColumn(iqE, mEdot->timesFullColumn(partFrame->qEdot));
	col->atminusFullColumn(iqE, mE->timesFullColumn(partFrame->qEddot));
	col->atplusFullColumn(iqE, pTpE);
	partFrame->fillAccICIterError(col);
}

void Part::fillAccICIterJacob(SpMatDsptr mat)
{
	//ToDo: Check for Units effect.
	auto iqX = partFrame->iqX;
	auto iqE = partFrame->iqE;
	mat->atandminusDiagonalMatrix(iqX, iqX, mX);
	mat->atandminusFullMatrix(iqE, iqE, mE);
	partFrame->fillAccICIterJacob(mat);
}

std::shared_ptr<EulerParametersDot<double>> Part::qEdot()
{
	return partFrame->qEdot;
}

void Part::setqsuddotlam(FColDsptr col)
{
	partFrame->setqsuddotlam(col);
}

std::shared_ptr<StateData> Part::stateData()
{
	//"
	//P : = part frame.
	//p : = principal frame at cm.
	//rOcmO : = rOPO + aAOP * rPcmP.
	//aAOp : = aAOP * aAPp.
	//vOcmO : = vOPO + aAdotOP * rPcmP
	//: = vOPO + (omeOPO cross : aAOP * rPcmP).
	//omeOpO : = omeOPO.
	//aOcmO : = aOPO + aAddotOP * rPcmP
	//: = aOPO + (alpOPO cross : aAOP * rPcmP) + (omeOPO cross : (omeOPO cross : aAOP * rPcmP)).
	//alpOpO : = alpOPO.

	//Therefore
	//aAOP : = aAOp * aAPpT
	//rOPO : = rOcmO - aAOP * rPcmP.
	//omeOPO : = omeOpO.
	//vOPO : = vOcmO - (omeOPO cross : aAOP * rPcmP).
	//alpOPO : = alpOpO.
	//aOPO : = aOcmO - (alpOPO cross : aAOP * rPcmP) - (omeOPO cross : (omeOPO cross :
	//aAOP * rPcmP)).
	//"

	auto rOpO = qX();
	auto aAOp = this->aAOp();
	auto vOpO = qXdot();
	auto omeOpO = this->omeOpO();
	auto aOpO = qXddot();
	auto alpOpO = this->alpOpO();
	auto answer = std::make_shared<PosVelAccData>();
	answer->rFfF = rOpO;
	answer->aAFf = aAOp;
	answer->vFfF = vOpO;
	answer->omeFfF = omeOpO;
	answer->aFfF = aOpO;
	answer->alpFfF = alpOpO;
	return answer;
}

double Part::suggestSmallerOrAcceptDynStepSize(double hnew)
{
	auto hnew2 = hnew;
	hnew2 = partFrame->suggestSmallerOrAcceptDynStepSize(hnew2);
	return hnew2;
}

void Part::postDynStep()
{
	partFrame->postDynStep();
}

void MbD::Part::postAccIC()
{
	calcpdot();
}

void MbD::Part::setpqsumu(FColDsptr col)
{
	pX->equalFullColumnAt(col, ipX);
	pE->equalFullColumnAt(col, ipE);
	partFrame->setpqsumu(col);
}

void MbD::Part::setpqsumudot(FColDsptr col)
{
	pXdot->equalFullColumnAt(col, ipX);
	pEdot->equalFullColumnAt(col, ipE);
	partFrame->setpqsumudot(col);
}

void MbD::Part::setpqsumuddot(FColDsptr col)
{
	partFrame->setpqsumuddot(col);
}

void MbD::Part::postDynPredictor()
{
	partFrame->postDynPredictor();
	Item::postDynPredictor();
}

void MbD::Part::fillDynError(FColDsptr col)
{
	partFrame->fillDynError(col);
	//ToDo: Check for Units effect.
	col->atplusFullColumn(ipX, pX->minusFullColumn(mX->timesFullColumn(partFrame->qXdot)));
	col->atplusFullColumn(ipE, pE->minusFullColumn(mE->timesFullColumn(partFrame->qEdot)));
	col->atminusFullColumn(partFrame->iqX, pXdot);
	col->atminusFullColumn(partFrame->iqE, pEdot->minusFullColumn(pTpE));
}

void MbD::Part::fillpFpy(SpMatDsptr mat)
{
	mat->atandplusDiagonalMatrix(ipX, ipX, DiagonalMatrix<double>::Identity3by3);
	mat->atandplusDiagonalMatrix(ipE, ipE, DiagonalMatrix<double>::Identity4by4);
	auto iqE = partFrame->iqE;
	//ToDo: Check for Units effect.
	mat->atandminusTransposeFullMatrix(ipE, iqE, ppTpEpEdot);
	mat->atandplusFullMatrix(iqE, iqE, ppTpEpE);
	partFrame->fillpFpy(mat);
}

void MbD::Part::fillpFpydot(SpMatDsptr mat)
{
		auto iqX = partFrame->iqX;
		auto iqE = partFrame->iqE;
		//ToDo: Check for Units effect.
		mat->atandminusDiagonalMatrix(ipX, iqX, mX);
		mat->atandminusFullMatrix(ipE, iqE, mE);
		mat->atandminusDiagonalMatrix(iqX, ipX, DiagonalMatrix<double>::Identity3by3);
		mat->atandminusDiagonalMatrix(iqE, ipE, DiagonalMatrix<double>::Identity4by4);
		mat->atandplusFullMatrix(iqE, iqE, ppTpEpEdot);
		partFrame->fillpFpydot(mat);
}

void MbD::Part::postDynCorrectorIteration()
{
	partFrame->postDynCorrectorIteration();
	Item::postDynCorrectorIteration();
}

void MbD::Part::preDynOutput()
{
	partFrame->preDynOutput();
	Item::preDynOutput();
}

void MbD::Part::postDynOutput()
{
	partFrame->postDynOutput();
	Item::postDynOutput();
}
