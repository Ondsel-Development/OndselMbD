/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

 //#include <string>
 //#include <cassert>
 //#include <fstream>	
 //#include <algorithm>
 //#include <numeric>
 //#include <iomanip>

#include "ASMTAssembly.h"
#include "ASMTRevoluteJoint.h"
#include "ASMTCylindricalJoint.h"
#include "ASMTRotationalMotion.h"
#include "ASMTTranslationalMotion.h"
#include "ASMTMarker.h"
#include "ASMTPart.h"
#include "ASMTTranslationalJoint.h"
#include "ASMTSphericalJoint.h"
#include "ASMTFixedJoint.h"
#include "ASMTGeneralMotion.h"
#include "ASMTAllowRotation.h"
#include "ASMTUniversalJoint.h"
#include "ASMTPointInPlaneJoint.h"
#include "ASMTPrincipalMassMarker.h"
#include "ASMTForceTorque.h"
#include "ASMTConstantGravity.h"
#include "ASMTSimulationParameters.h"
#include "ASMTAnimationParameters.h"
#include "Part.h"
#include "ASMTTime.h"
#include "ASMTItem.h"
#include "ASMTItemIJ.h"
#include "ASMTAngleJoint.h"
#include "ASMTConstantVelocityJoint.h"
#include "ASMTCylSphJoint.h"
#include "ASMTGearJoint.h"
#include "ASMTPointInLineJoint.h"
#include "ASMTRevCylJoint.h"
#include "ASMTSphSphJoint.h"
#include "ASMTLineInPlaneJoint.h"
#include "ASMTPlanarJoint.h"
#include "ASMTNoRotationJoint.h"
#include "ASMTParallelAxesJoint.h"
#include "ASMTPerpendicularJoint.h"
#include "ASMTRackPinionJoint.h"
#include "ASMTScrewJoint.h"
#include "SimulationStoppingError.h"
#include "ASMTKinematicIJ.h"
#include "ASMTRefPoint.h"
#include "ASMTRefCurve.h"
#include "ASMTRefSurface.h"
#include "ExternalSystem.h"
#include "SystemSolver.h"
#include "ASMTRevRevJoint.h"
#include "ASMTForceTorqueInLine.h"
#include "ASMTForceTorqueGeneral.h"
#include "Units.h"

using namespace MbD;

std::shared_ptr<ASMTAssembly> MbD::ASMTAssembly::With()
{
	auto inst = std::make_shared<ASMTAssembly>();
	inst->initialize();
	return inst;
}

void MbD::ASMTAssembly::initialize()
{
	ASMTSpatialContainer::initialize();
	setConstantGravity(ASMTConstantGravity::With());
	addTime(ASMTTime::With());
	times = FullRow<double>::With();
}

void MbD::ASMTAssembly::runSinglePendulumSuperSimplified()
{
	//In this version we skip declaration of variables that don't need as they use default values.
	auto assembly = ASMTAssembly::With();

	assembly->setName("Assembly1");

	auto mkrI = ASMTMarker::With();
	mkrI->setName("Marker1");
	assembly->addMarker(mkrI);

	auto part1 = ASMTPart::With();
	part1->setName("Part1");
	part1->setPosition3D(-0.1, -0.1, -0.1);
	assembly->addPart(part1);

	auto mkrJ = ASMTMarker::With();
	mkrJ->setName("Marker1");
	mkrJ->setPosition3D(0.1, 0.1, 0.1);
	part1->addMarker(mkrJ);

	auto joint = ASMTFixedJoint::With();
	joint->setName("Joint1");
	joint->setMarkerI(mkrI);
	joint->setMarkerJ(mkrJ);
	assembly->addJoint(joint);

	auto simulationParameters = ASMTSimulationParameters::With();
	simulationParameters->settstart(0.0);
	simulationParameters->settend(0.0);	//tstart == tend Initial Conditions only.
	simulationParameters->sethmin(1.0e-9);
	simulationParameters->sethmax(1.0);
	simulationParameters->sethout(0.04);
	simulationParameters->seterrorTol(1.0e-6);
	assembly->setSimulationParameters(simulationParameters);

	assembly->runKINEMATIC();
}

void MbD::ASMTAssembly::runSinglePendulumSuperSimplified2()
{
	//In this version we skip declaration of variables that don't need as they use default values.
	auto assembly = ASMTAssembly::With();
	assembly->setName("OndselAssembly");

	auto mkrAM1 = ASMTMarker::With();
	mkrAM1->setName("marker1");
	assembly->addMarker(mkrAM1);

	auto part1 = ASMTPart::With();
	part1->setName("part1");
	assembly->addPart(part1);

	auto mkrP1Fix = ASMTMarker::With();
	mkrP1Fix->setName("FixingMarker");
	part1->addMarker(mkrP1Fix);

	auto mkrP1M2 = ASMTMarker::With();
	mkrP1M2->setName("marker2");
	mkrP1M2->setPosition3D(20.0, 10.0, 0.0);
	part1->addMarker(mkrP1M2);

	auto part2 = ASMTPart::With();
	part2->setName("part2");
	part2->setPosition3D(20.0, 10.0, 0.0);
	assembly->addPart(part2);

	auto mkrP2M2 = ASMTMarker::With();
	mkrP2M2->setName("marker2");
	mkrP2M2->setPosition3D(50.0, 10.0, 0.0);
	part2->addMarker(mkrP2M2);

	/*Ground joint*/
	auto joint = ASMTFixedJoint::With();
	joint->setName("Joint1");
	joint->setMarkerI(mkrAM1);
	joint->setMarkerJ(mkrP1Fix);
	assembly->addJoint(joint);

	auto joint2 = ASMTRevoluteJoint::With();
	joint2->setName("Joint2");
	joint2->setMarkerI(mkrP1M2);
	joint2->setMarkerJ(mkrP2M2);
	assembly->addJoint(joint2);

	auto simulationParameters = ASMTSimulationParameters::With();
	simulationParameters->settstart(0.0);
	simulationParameters->settend(0.0);	//tstart == tend Initial Conditions only.
	simulationParameters->sethmin(1.0e-9);
	simulationParameters->sethmax(1.0);
	simulationParameters->sethout(0.04);
	simulationParameters->seterrorTol(1.0e-6);
	assembly->setSimulationParameters(simulationParameters);

	assembly->runKINEMATIC();
}

void MbD::ASMTAssembly::runSinglePendulumSimplified()
{
	auto assembly = ASMTAssembly::With();

	assembly->setNotes("");
	assembly->setName("Assembly1");
	assembly->setPosition3D(0, 0, 0);
	assembly->setRotationMatrix(
		1, 0, 0,
		0, 1, 0,
		0, 0, 1);
	assembly->setVelocity3D(0, 0, 0);
	assembly->setOmega3D(0, 0, 0);

	auto massMarker = ASMTPrincipalMassMarker::With();
	massMarker->setMass(0.0);
	massMarker->setDensity(0.0);
	massMarker->setMomentOfInertias(0, 0, 0);
	massMarker->setPosition3D(0, 0, 0);
	massMarker->setRotationMatrix(
		1, 0, 0,
		0, 1, 0,
		0, 0, 1);
	assembly->setPrincipalMassMarker(massMarker);

	auto mkrAM1 = ASMTMarker::With();
	mkrAM1->setName("Marker1");
	mkrAM1->setPosition3D(0, 0, 0);
	mkrAM1->setRotationMatrix(
		1, 0, 0,
		0, 1, 0,
		0, 0, 1);
	assembly->addMarker(mkrAM1);

	auto part1 = ASMTPart::With();
	part1->setName("Part1");
	part1->setPosition3D(-0.1, -0.1, -0.1);
	part1->setRotationMatrix(
		1, 0, 0,
		0, 1, 0,
		0, 0, 1);
	part1->setVelocity3D(0, 0, 0);
	part1->setOmega3D(0, 0, 0);
	assembly->addPart(part1);

	massMarker = ASMTPrincipalMassMarker::With();
	massMarker->setMass(0.2);
	massMarker->setDensity(10.0);
	massMarker->setMomentOfInertias(8.3333333333333e-4, 0.016833333333333, 0.017333333333333);
	massMarker->setPosition3D(0.5, 0.1, 0.05);
	massMarker->setRotationMatrix(
		1, 0, 0,
		0, 1, 0,
		0, 0, 1);
	part1->setPrincipalMassMarker(massMarker);

	auto mkrP1M1 = ASMTMarker::With();
	mkrP1M1->setName("Marker1");
	mkrP1M1->setPosition3D(0.1, 0.1, 0.1);
	mkrP1M1->setRotationMatrix(
		1, 0, 0,
		0, 1, 0,
		0, 0, 1);
	part1->addMarker(mkrP1M1);

	auto joint = ASMTRevoluteJoint::With();
	joint->setName("Joint1");
	joint->setMarkerI(mkrAM1);
	joint->setMarkerJ(mkrP1M1);
	assembly->addJoint(joint);

	auto motion = ASMTRotationalMotion::With();
	motion->setName("Motion1");
	motion->setMotionJoint("/Assembly1/Joint1");
	motion->setRotationZ("0.0");
	assembly->addMotion(motion);

	auto constantGravity = ASMTConstantGravity::With();
	constantGravity->setg(0.0, 0.0, 0.0);
	assembly->setConstantGravity(constantGravity);

	auto simulationParameters = ASMTSimulationParameters::With();
	simulationParameters->settstart(0.0);
	simulationParameters->settend(0.0);	//tstart == tend Initial Conditions only.
	simulationParameters->sethmin(1.0e-9);
	simulationParameters->sethmax(1.0);
	simulationParameters->sethout(0.04);
	simulationParameters->seterrorTol(1.0e-6);
	assembly->setSimulationParameters(simulationParameters);

	assembly->runKINEMATIC();
}

void MbD::ASMTAssembly::runSinglePendulum()
{
	auto assembly = ASMTAssembly::With();
	std::string str = "";
	assembly->setNotes(str);
	str = "Assembly1";
	assembly->setName(str);
	auto pos3D = std::make_shared<FullColumn<double>>(ListD{ 0, 0, 0 });
	assembly->setPosition3D(pos3D);
	auto rotMat = FullMatrix<double>::With(ListListD{
		{ 1, 0, 0 },
		{ 0, 1, 0 },
		{ 0, 0, 1 }
		});
	assembly->setRotationMatrix(rotMat);
	auto vel3D = std::make_shared<FullColumn<double>>(ListD{ 0, 0, 0 });
	assembly->setVelocity3D(vel3D);
	auto ome3D = std::make_shared<FullColumn<double>>(ListD{ 0, 0, 0 });
	assembly->setOmega3D(ome3D);
	//
	auto massMarker = ASMTPrincipalMassMarker::With();
	massMarker->setMass(0.0);
	massMarker->setDensity(0.0);
	auto aJ = DiagonalMatrix<double>::With(ListD{ 0, 0, 0 });
	massMarker->setMomentOfInertias(aJ);
	pos3D = std::make_shared<FullColumn<double>>(ListD{ 0, 0, 0 });
	massMarker->setPosition3D(pos3D);
	rotMat = FullMatrix<double>::With(ListListD{
		{ 1, 0, 0 },
		{ 0, 1, 0 },
		{ 0, 0, 1 }
		});
	massMarker->setRotationMatrix(rotMat);
	assembly->setPrincipalMassMarker(massMarker);
	//
	auto mkrAM1 = ASMTMarker::With();
	str = "Marker1";
	mkrAM1->setName(str);
	pos3D = std::make_shared<FullColumn<double>>(ListD{ 0, 0, 0 });
	mkrAM1->setPosition3D(pos3D);
	rotMat = FullMatrix<double>::With(ListListD{
		{ 1, 0, 0 },
		{ 0, 1, 0 },
		{ 0, 0, 1 }
		});
	mkrAM1->setRotationMatrix(rotMat);
	assembly->addMarker(mkrAM1);
	//
	auto part1 = ASMTPart::With();
	str = "Part1";
	part1->setName(str);
	pos3D = std::make_shared<FullColumn<double>>(ListD{ -0.1, -0.1, -0.1 });
	part1->setPosition3D(pos3D);
	rotMat = FullMatrix<double>::With(ListListD{
		{ 1, 0, 0 },
		{ 0, 1, 0 },
		{ 0, 0, 1 }
		});
	part1->setRotationMatrix(rotMat);
	vel3D = std::make_shared<FullColumn<double>>(ListD{ 0, 0, 0 });
	part1->setVelocity3D(vel3D);
	ome3D = std::make_shared<FullColumn<double>>(ListD{ 0, 0, 0 });
	part1->setOmega3D(ome3D);
	assembly->addPart(part1);
	//
	massMarker = ASMTPrincipalMassMarker::With();
	massMarker->setMass(0.2);
	massMarker->setDensity(10.0);
	aJ = DiagonalMatrix<double>::With(ListD{ 8.3333333333333e-4, 0.016833333333333, 0.017333333333333 });
	massMarker->setMomentOfInertias(aJ);
	pos3D = std::make_shared<FullColumn<double>>(ListD{ 0.5, 0.1, 0.05 });
	massMarker->setPosition3D(pos3D);
	rotMat = FullMatrix<double>::With(ListListD{
		{ 1, 0, 0 },
		{ 0, 1, 0 },
		{ 0, 0, 1 }
		});
	massMarker->setRotationMatrix(rotMat);
	part1->setPrincipalMassMarker(massMarker);
	//
	auto mkrP1M1 = ASMTMarker::With();
	str = "Marker1";
	mkrP1M1->setName(str);
	pos3D = std::make_shared<FullColumn<double>>(ListD{ 0.1, 0.1, 0.1 });
	mkrP1M1->setPosition3D(pos3D);
	rotMat = FullMatrix<double>::With(ListListD{
		{ 1, 0, 0 },
		{ 0, 1, 0 },
		{ 0, 0, 1 }
		});
	mkrP1M1->setRotationMatrix(rotMat);
	part1->addMarker(mkrP1M1);
	//
	auto joint = ASMTRevoluteJoint::With();
	str = "Joint1";
	joint->setName(str);
	joint->setMarkerI(mkrAM1);
	joint->setMarkerJ(mkrP1M1);
	assembly->addJoint(joint);
	//
	auto motion = ASMTRotationalMotion::With();
	str = "Motion1";
	motion->setName(str);
	str = "/Assembly1/Joint1";
	motion->setMotionJoint(str);
	str = "0.0";
	motion->setRotationZ(str);
	assembly->addMotion(motion);
	//
	auto constantGravity = ASMTConstantGravity::With();
	auto gAcceleration = std::make_shared<FullColumn<double>>(ListD{ 0.0, 0.0, 0.0 });
	constantGravity->setg(gAcceleration);
	assembly->setConstantGravity(constantGravity);
	//
	auto simulationParameters = ASMTSimulationParameters::With();
	simulationParameters->settstart(0.0);
	simulationParameters->settend(0.0);	//tstart == tend Initial Conditions only.
	simulationParameters->sethmin(1.0e-9);
	simulationParameters->sethmax(1.0);
	simulationParameters->sethout(0.04);
	simulationParameters->seterrorTol(1.0e-6);
	assembly->setSimulationParameters(simulationParameters);
	//
	assembly->runKINEMATIC();
}

std::shared_ptr<ASMTAssembly> MbD::ASMTAssembly::assemblyFromFile(const char* fileName)
{
	std::ifstream stream(fileName);
	if (stream.fail()) {
		throw std::invalid_argument("File not found.");
	}
	std::string line;
	std::vector<std::string> lines;
	while (std::getline(stream, line)) {
		lines.push_back(line);
	}
	auto assembly = ASMTAssembly::With();
	auto str = assembly->popOffTop(lines);
	bool bool1 = str == "freeCAD: 3D CAD with Motion Simulation  by  askoh.com";
	bool bool2 = str == "OndselSolver";
	assert(bool1 || bool2);
	assert(assembly->readStringNoSpacesOffTop(lines) == "Assembly");
	assembly->setFilename(fileName);
	assembly->parseASMT(lines);
	return assembly;
}

void MbD::ASMTAssembly::runDynFile(const char* fileName)
{
	auto lines = linesFromFile(fileName);
	auto assembly = ASMTAssembly::With();
	std::string str("\n\n\nStarting DYNAMIC simulation");
	assembly->logString(str);
	assembly->setFilename(fileName);
	assert(assembly->readStringNoSpacesOffTop(lines) == "Assembly");
	assembly->parseASMT(lines);
	assembly->runDYNAMIC();
}

void MbD::ASMTAssembly::runKineFile(const char* fileName)
{
	auto lines = linesFromFile(fileName);
	auto assembly = ASMTAssembly::With();
	std::string str("\n\n\nStarting KINEMATIC simulation");
	assembly->logString(str);
	assembly->setFilename(fileName);
	assert(assembly->readStringNoSpacesOffTop(lines) == "Assembly");
	assembly->parseASMT(lines);
	assembly->runKINEMATIC();
}

std::vector<std::string> MbD::ASMTAssembly::linesFromFile(const char* fileName)
{
	std::ifstream stream(fileName);
	if (stream.fail()) {
		throw std::invalid_argument("File not found.");
	}
	std::string line;
	std::vector<std::string> lines;
	while (std::getline(stream, line)) {
		lines.push_back(line);
	}
	bool bool1 = lines[0] == "freeCAD: 3D CAD with Motion Simulation  by  askoh.com";
	bool bool2 = lines[0] == "OndselSolver";
	assert(bool1 || bool2);
	lines.erase(lines.begin());
	return lines;
}

void MbD::ASMTAssembly::readWriteKineFile(const char* fileName)
{
	std::ifstream stream(fileName);
	if (stream.fail()) {
		throw std::invalid_argument("File not found.");
	}
	std::string line;
	std::vector<std::string> lines;
	while (std::getline(stream, line)) {
		lines.push_back(line);
	}
	bool bool1 = lines[0] == "freeCAD: 3D CAD with Motion Simulation  by  askoh.com";
	bool bool2 = lines[0] == "OndselSolver";
	assert(bool1 || bool2);
	lines.erase(lines.begin());

	if (lines[0] == "Assembly") {
		lines.erase(lines.begin());
		auto assembly = ASMTAssembly::With();
		assembly->parseASMT(lines);
		assembly->runKINEMATIC();
		assembly->outputFile("assemblyKine.asmt");
		ASMTAssembly::runKineFile("assemblyKine.asmt");
	}
}

void MbD::ASMTAssembly::readWriteDynFile(const char* fileName)
{
	std::ifstream stream(fileName);
	if (stream.fail()) {
		throw std::invalid_argument("File not found.");
	}
	std::string line;
	std::vector<std::string> lines;
	while (std::getline(stream, line)) {
		lines.push_back(line);
	}
	bool bool1 = lines[0] == "freeCAD: 3D CAD with Motion Simulation  by  askoh.com";
	bool bool2 = lines[0] == "OndselSolver";
	assert(bool1 || bool2);
	lines.erase(lines.begin());

	if (lines[0] == "Assembly") {
		lines.erase(lines.begin());
		auto assembly = ASMTAssembly::With();
		assembly->parseASMT(lines);
		assembly->runDYNAMIC();
		assembly->outputFile("../testapp/tempAssembly.asmt");
		ASMTAssembly::runDynFile("../testapp/tempAssembly.asmt");
	}
}

void MbD::ASMTAssembly::runDraggingTest()
{
	auto assembly = ASMTAssembly::assemblyFromFile("../testapp/dragCrankSlider.asmt");
	auto& dragPart = assembly->parts->at(0);
	auto dragParts = std::make_shared<std::vector<std::shared_ptr<ASMTPart>>>();
	dragParts->push_back(dragPart);
	assembly->runPreDrag();	//Do this before first drag
	FColDsptr pos3D, delta;
	pos3D = dragPart->position3D;
	delta = std::make_shared<FullColumn<double>>(ListD{ 0.1, 0.2, 0.3 });
	dragPart->updateMbDFromPosition3D(pos3D->plusFullColumn(delta));
	assembly->runDragStep(dragParts);
	pos3D = dragPart->position3D;
	delta = std::make_shared<FullColumn<double>>(ListD{ 0.3, 0.2, 0.1 });
	dragPart->updateMbDFromPosition3D(pos3D->plusFullColumn(delta));
	assembly->runDragStep(dragParts);
	assembly->runPostDrag();	//Do this after last drag
}

ASMTAssembly* MbD::ASMTAssembly::root()
{
	return this;
}

void MbD::ASMTAssembly::setNotes(std::string str)
{
	notes = str;
}

void MbD::ASMTAssembly::parseASMT(std::vector<std::string>& lines)
{
	readNotes(lines);
	readName(lines);
	readPosition3D(lines);
	readRotationMatrix(lines);
	readVelocity3D(lines);
	readOmega3D(lines);
	initprincipalMassMarker();
	readRefPoints(lines);
	readRefCurves(lines);
	readRefSurfaces(lines);
	readParts(lines);
	readKinematicIJs(lines);
	readConstraintSets(lines);
	readForcesTorques(lines);
	readConstantGravity(lines);
	readSimulationParameters(lines);
	readAnimationParameters(lines);
	readSeries(lines);
}

void MbD::ASMTAssembly::readNotes(std::vector<std::string>& lines)
{
	assert(lines[0] == "\tNotes");
	lines.erase(lines.begin());
	notes = readStringNoSpacesOffTop(lines);
}

void MbD::ASMTAssembly::readParts(std::vector<std::string>& lines)
{
	assert(lines[0] == "\tParts");
	lines.erase(lines.begin());
	parts->clear();
	auto it = std::find(lines.begin(), lines.end(), "\tKinematicIJs");
	std::vector<std::string> partsLines(lines.begin(), it);
	while (!partsLines.empty()) {
		readPart(partsLines);
	}
	lines.erase(lines.begin(), it);

}

void MbD::ASMTAssembly::readPart(std::vector<std::string>& lines)
{
	assert(lines[0] == "\t\tPart");
	lines.erase(lines.begin());
	auto part = ASMTPart::With();
	part->container = this;
	part->parseASMT(lines);
	parts->push_back(part);
}

void MbD::ASMTAssembly::readKinematicIJs(std::vector<std::string>& lines)
{
	assert(lines[0] == "\tKinematicIJs");
	lines.erase(lines.begin());
	kinematicIJs->clear();
	auto it = std::find(lines.begin(), lines.end(), "\tConstraintSets");
	std::vector<std::string> kinematicIJsLines(lines.begin(), it);
	while (!kinematicIJsLines.empty()) {
		readKinematicIJ(kinematicIJsLines);
	}
	lines.erase(lines.begin(), it);

}

void MbD::ASMTAssembly::readKinematicIJ(std::vector<std::string>&)
{
	assert(false);
}

void MbD::ASMTAssembly::readConstraintSets(std::vector<std::string>& lines)
{
	assert(lines[0] == "\tConstraintSets");
	lines.erase(lines.begin());
	readJoints(lines);
	readMotions(lines);
	readGeneralConstraintSets(lines);
}

void MbD::ASMTAssembly::readJoints(std::vector<std::string>& lines)
{
	assert(lines[0] == "\t\tJoints");
	lines.erase(lines.begin());
	joints->clear();
	auto it = std::find(lines.begin(), lines.end(), "\t\tMotions");
	std::vector<std::string> jointsLines(lines.begin(), it);
	std::shared_ptr<ASMTJoint> joint;
	while (!jointsLines.empty()) {
		if (jointsLines[0] == "\t\t\tAngleJoint") {
			joint = ASMTAngleJoint::With();
		}
		else if (jointsLines[0] == "\t\t\tGearJoint") {
			joint = ASMTGearJoint::With();
		}
		else if (jointsLines[0] == "\t\t\tNoRotationJoint") {
			joint = ASMTNoRotationJoint::With();
		}
		else if (jointsLines[0] == "\t\t\tParallelAxesJoint") {
			joint = ASMTParallelAxesJoint::With();
		}
		else if (jointsLines[0] == "\t\t\tPerpendicularJoint") {
			joint = ASMTPerpendicularJoint::With();
		}
		else if (jointsLines[0] == "\t\t\tRackPinionJoint") {
			joint = ASMTRackPinionJoint::With();
		}
		else if (jointsLines[0] == "\t\t\tScrewJoint") {
			joint = ASMTScrewJoint::With();
		}
		//AtPointJoints
		else if (jointsLines[0] == "\t\t\tConstantVelocityJoint") {
			joint = ASMTConstantVelocityJoint::With();
		}
		else if (jointsLines[0] == "\t\t\tFixedJoint") {
			joint = ASMTFixedJoint::With();
		}
		else if (jointsLines[0] == "\t\t\tRevoluteJoint") {
			joint = ASMTRevoluteJoint::With();
		}
		else if (jointsLines[0] == "\t\t\tSphericalJoint") {
			joint = ASMTSphericalJoint::With();
		}
		else if (jointsLines[0] == "\t\t\tUniversalJoint") {
			joint = ASMTUniversalJoint::With();
		}
		//CompoundJoints
		else if (jointsLines[0] == "\t\t\tSphSphJoint") {
			joint = ASMTSphSphJoint::With();
		}
		else if (jointsLines[0] == "\t\t\tCylSphJoint") {
			joint = ASMTCylSphJoint::With();
		}
		else if (jointsLines[0] == "\t\t\tRevCylJoint") {
			joint = ASMTRevCylJoint::With();
		}
		else if (jointsLines[0] == "\t\t\tRevRevJoint") {
			joint = ASMTRevRevJoint::With();
		}
		//InLineJoints
		else if (jointsLines[0] == "\t\t\tCylindricalJoint") {
			joint = ASMTCylindricalJoint::With();
		}
		else if (jointsLines[0] == "\t\t\tPointInLineJoint") {
			joint = ASMTPointInLineJoint::With();
		}
		else if (jointsLines[0] == "\t\t\tTranslationalJoint") {
			joint = ASMTTranslationalJoint::With();
		}
		//InPlaneJoints
		else if (jointsLines[0] == "\t\t\tLineInPlaneJoint") {
			joint = ASMTLineInPlaneJoint::With();
		}
		else if (jointsLines[0] == "\t\t\tPlanarJoint") {
			joint = ASMTPlanarJoint::With();
		}
		else if (jointsLines[0] == "\t\t\tPointInPlaneJoint") {
			joint = ASMTPointInPlaneJoint::With();
		}
		else {
			assert(false);
		}
		jointsLines.erase(jointsLines.begin());
		joint->container = this;
		joint->parseASMT(jointsLines);
		joints->push_back(joint);
	}
	lines.erase(lines.begin(), it);

}

void MbD::ASMTAssembly::readMotions(std::vector<std::string>& lines)
{
	assert(lines[0] == "\t\tMotions");
	lines.erase(lines.begin());
	motions->clear();
	auto it = std::find(lines.begin(), lines.end(), "\t\tGeneralConstraintSets");
	std::vector<std::string> motionsLines(lines.begin(), it);
	std::shared_ptr<ASMTMotion> motion;
	while (!motionsLines.empty()) {
		if (motionsLines[0] == "\t\t\tRotationalMotion") {
			motion = ASMTRotationalMotion::With();
		}
		else if (motionsLines[0] == "\t\t\tTranslationalMotion") {
			motion = ASMTTranslationalMotion::With();
		}
		else if (motionsLines[0] == "\t\t\tGeneralMotion") {
			motion = ASMTGeneralMotion::With();
		}
		else if (motionsLines[0] == "\t\t\tAllowRotation") {
			motion = ASMTAllowRotation::With();
		}
		else {
			assert(false);
		}
		motionsLines.erase(motionsLines.begin());
		motion->container = this;
		motion->parseASMT(motionsLines);
		motions->push_back(motion);
		motion->initMarkers();
	}
	lines.erase(lines.begin(), it);

}

void MbD::ASMTAssembly::readGeneralConstraintSets(std::vector<std::string>& lines) const
{
	assert(lines[0] == "\t\tGeneralConstraintSets");
	lines.erase(lines.begin());
	constraintSets->clear();
	auto it = std::find(lines.begin(), lines.end(), "\tForceTorques");
	std::vector<std::string> generalConstraintSetsLines(lines.begin(), it);
	while (!generalConstraintSetsLines.empty()) {
		assert(false);
	}
	lines.erase(lines.begin(), it);
}

void MbD::ASMTAssembly::readForcesTorques(std::vector<std::string>& lines)
{
	assert(lines[0] == "\tForceTorques");	//Spelling is not consistent in asmt file.
	lines.erase(lines.begin());
	forcesTorques->clear();
	auto it = std::find(lines.begin(), lines.end(), "\tConstantGravity");
	std::vector<std::string> forcesTorquesLines(lines.begin(), it);
	std::shared_ptr<ASMTForceTorque> forceTorque;
	while (!forcesTorquesLines.empty()) {
		if (forcesTorquesLines[0] == "\t\tInLineForceTorque") {
			forceTorque = ASMTForceTorqueInLine::With();
		}
		else if (forcesTorquesLines[0] == "\t\tGeneralForceTorque") {
			forceTorque = ASMTForceTorqueGeneral::With();
		}
		else {
			assert(false);
		}

		forcesTorquesLines.erase(forcesTorquesLines.begin());
		forceTorque->container = this;
		forceTorque->parseASMT(forcesTorquesLines);
		forcesTorques->push_back(forceTorque);
	}
	lines.erase(lines.begin(), it);
}

void MbD::ASMTAssembly::readConstantGravity(std::vector<std::string>& lines)
{
	assert(lines[0] == "\tConstantGravity");
	lines.erase(lines.begin());
	constantGravity = ASMTConstantGravity::With();
	constantGravity->container = this;
	constantGravity->parseASMT(lines);
}

void MbD::ASMTAssembly::readSimulationParameters(std::vector<std::string>& lines)
{
	assert(lines[0] == "\tSimulationParameters");
	lines.erase(lines.begin());
	simulationParameters = ASMTSimulationParameters::With();
	simulationParameters->container = this;
	simulationParameters->parseASMT(lines);
}

void MbD::ASMTAssembly::readAnimationParameters(std::vector<std::string>& lines)
{
	assert(lines[0] == "\tAnimationParameters");
	lines.erase(lines.begin());
	animationParameters = ASMTAnimationParameters::With();
	animationParameters->container = this;
	animationParameters->parseASMT(lines);
}

void MbD::ASMTAssembly::readSeries(std::vector<std::string>& lines)
{
	while (!lines.empty() && (lines[0].find("Series") != std::string::npos)) {
		if (lines[0].find("TimeSeries") != std::string::npos) {
			readTimeSeries(lines);
		}
		else if (lines[0].find("AssemblySeries") != std::string::npos) {
			readAssemblySeries(lines);
		}
		else if (lines[0].find("PartSeries") != std::string::npos) {
			readPartSeries(lines);
		}
		else if (lines[0].find("JointSeries") != std::string::npos) {
			readJointSeries(lines);
		}
		else if (lines[0].find("MotionSeries") != std::string::npos) {
			readMotionSeries(lines);
		}
		else if (lines[0].find("ForceTorqueSeries") != std::string::npos) {
			readForceTorqueSeries(lines);
		}
		else {
			assert(false);
		}
	}
}

void MbD::ASMTAssembly::readTimeSeries(std::vector<std::string>& lines)
{
	if (lines.empty()) return;
	assert(readStringNoSpacesOffTop(lines) == "TimeSeries");
	assert(lines[0].find("Number\tInput") != std::string::npos);
	lines.erase(lines.begin());
	readTimes(lines);
}

void MbD::ASMTAssembly::readTimes(std::vector<std::string>& lines)
{
	if (lines.empty()) return;
	std::string str = lines[0];
	std::string substr = "Time\tInput";
	auto pos = str.find(substr);
	assert(pos != std::string::npos);
	str.erase(0, pos + substr.length());
	itimes = readRowOfDoubles(str);
	itimes->insert(itimes->begin(), itimes->at(0));	//The first element is the input state.
	lines.erase(lines.begin());
}

void MbD::ASMTAssembly::readPartSeriesMany(std::vector<std::string>& lines)
{
	if (lines.empty()) return;
	assert(lines[0].find("PartSeries") != std::string::npos);
	auto it = std::find_if(lines.begin(), lines.end(), [](const std::string& s) {
		return s.find("JointSeries") != std::string::npos;
		});
	std::vector<std::string> partSeriesLines(lines.begin(), it);
	while (!partSeriesLines.empty()) {
		readPartSeries(partSeriesLines);
	}
	lines.erase(lines.begin(), it);
}

void MbD::ASMTAssembly::readJointSeriesMany(std::vector<std::string>& lines)
{
	if (lines.empty()) return;
	assert(lines[0].find("JointSeries") != std::string::npos);
	auto it = std::find_if(lines.begin(), lines.end(), [](const std::string& s) {
		return s.find("tionSeries") != std::string::npos;
		});
	std::vector<std::string> jointSeriesLines(lines.begin(), it);
	while (!jointSeriesLines.empty()) {
		readJointSeries(jointSeriesLines);
	}
	lines.erase(lines.begin(), it);
}

void MbD::ASMTAssembly::readAssemblySeries(std::vector<std::string>& lines)
{
	if (lines.empty()) return;
	std::string str = lines[0];
	std::string substr = "AssemblySeries";
	auto pos = str.find(substr);
	assert(pos != std::string::npos);
	str.erase(0, pos + substr.length());
	auto seriesName = readString(str);
	assert(fullName("") == seriesName);
	lines.erase(lines.begin());
	//xs, ys, zs, bryxs, bryys, bryzs
	readXs(lines);
	readYs(lines);
	readZs(lines);
	readBryantxs(lines);
	readBryantys(lines);
	readBryantzs(lines);
	readVXs(lines);
	readVYs(lines);
	readVZs(lines);
	readOmegaXs(lines);
	readOmegaYs(lines);
	readOmegaZs(lines);
	readAXs(lines);
	readAYs(lines);
	readAZs(lines);
	readAlphaXs(lines);
	readAlphaYs(lines);
	readAlphaZs(lines);
}

void MbD::ASMTAssembly::readPartSeries(std::vector<std::string>& lines)
{
	if (lines.empty()) return;
	std::string str = lines[0];
	std::string substr = "PartSeries";
	auto pos = str.find(substr);
	assert(pos != std::string::npos);
	str.erase(0, pos + substr.length());
	auto seriesName = readString(str);
	auto it = std::find_if(parts->begin(), parts->end(), [&](const std::shared_ptr<ASMTPart>& prt) {
		return prt->fullName("") == seriesName;
		});
	auto& part = *it;
	part->readPartSeries(lines);
}

void MbD::ASMTAssembly::readJointSeries(std::vector<std::string>& lines)
{
	if (lines.empty()) return;
	std::string str = lines[0];
	std::string substr = "JointSeries";
	auto pos = str.find(substr);
	assert(pos != std::string::npos);
	str.erase(0, pos + substr.length());
	auto seriesName = readString(str);
	auto it = std::find_if(joints->begin(), joints->end(), [&](const std::shared_ptr<ASMTJoint>& jt) {
		return jt->fullName("") == seriesName;
		});
	auto& joint = *it;
	joint->readJointSeries(lines);
}

void MbD::ASMTAssembly::readMotionSeriesMany(std::vector<std::string>& lines)
{
	while (!lines.empty()) {
		assert(lines[0].find("tionSeries") != std::string::npos);
		readMotionSeries(lines);
	}
}

void MbD::ASMTAssembly::readMotionSeries(std::vector<std::string>& lines)
{
	if (lines.empty()) return;
	std::string str = lines[0];
	std::string substr = "tionSeries";
	auto pos = str.find(substr);
	assert(pos != std::string::npos);
	str.erase(0, pos + substr.length());
	auto seriesName = readString(str);
	auto it = std::find_if(motions->begin(), motions->end(), [&](const std::shared_ptr<ASMTMotion>& jt) {
		return jt->fullName("") == seriesName;
		});
	auto& motion = *it;
	motion->readMotionSeries(lines);
}

void MbD::ASMTAssembly::readForceTorqueSeries(std::vector<std::string>& lines)
{
	if (lines.empty()) return;
	std::string str = lines[0];
	std::string substr = "ForceTorqueSeries";
	auto pos = str.find(substr);
	assert(pos != std::string::npos);
	str.erase(0, pos + substr.length());
	auto seriesName = readString(str);
	auto it = std::find_if(forcesTorques->begin(), forcesTorques->end(), [&](const std::shared_ptr<ASMTForceTorque>& jt) {
		return jt->fullName("") == seriesName;
		});
	auto& forcesTorque = *it;
	forcesTorque->readForceTorqueSeries(lines);
}

void MbD::ASMTAssembly::outputFor(AnalysisType type)
{
	assert(false);
}

void MbD::ASMTAssembly::preMbDrun(std::shared_ptr<System> mbdSys)
{
	deleteMbD();
	createMbD();
	std::static_pointer_cast<Part>(mbdObject)->asFixed();
}

void MbD::ASMTAssembly::postMbDrun()
{
	assert(false);
}

std::shared_ptr<std::vector<std::shared_ptr<ASMTItemIJ>>> MbD::ASMTAssembly::connectorList() const
{
	auto list = std::make_shared<std::vector<std::shared_ptr<ASMTItemIJ>>>();
	list->insert(list->end(), joints->begin(), joints->end());
	list->insert(list->end(), motions->begin(), motions->end());
	list->insert(list->end(), kinematicIJs->begin(), kinematicIJs->end());
	list->insert(list->end(), forcesTorques->begin(), forcesTorques->end());
	return list;
}

void MbD::ASMTAssembly::deleteMbD()
{
	ASMTSpatialContainer::deleteMbD();
	constantGravity->deleteMbD();
	asmtTime->deleteMbD();
	for (auto& part : *parts) { part->deleteMbD(); }
	for (auto& joint : *joints) { joint->deleteMbD(); }
	for (auto& motion : *motions) { motion->deleteMbD(); }
	for (auto& forceTorque : *forcesTorques) { forceTorque->deleteMbD(); }


}

void MbD::ASMTAssembly::createMbD()
{
	ASMTSpatialContainer::createMbD();
	constantGravity->createMbD();
	asmtTime->createMbD();
	std::sort(parts->begin(), parts->end(), [](std::shared_ptr<ASMTPart> a, std::shared_ptr<ASMTPart> b) { return a->name < b->name; });
	auto jointsMotions = std::make_shared<std::vector<std::shared_ptr<ASMTConstraintSet>>>();
	jointsMotions->insert(jointsMotions->end(), joints->begin(), joints->end());
	jointsMotions->insert(jointsMotions->end(), motions->begin(), motions->end());
	std::sort(jointsMotions->begin(), jointsMotions->end(), [](std::shared_ptr<ASMTConstraintSet> a, std::shared_ptr<ASMTConstraintSet> b) { return a->name < b->name; });
	std::sort(forcesTorques->begin(), forcesTorques->end(), [](std::shared_ptr<ASMTForceTorque> a, std::shared_ptr<ASMTForceTorque> b) { return a->name < b->name; });
	for (auto& part : *parts) { part->createMbD(); }
	for (auto& joint : *jointsMotions) { joint->createMbD(); }
	for (auto& forceTorque : *forcesTorques) { forceTorque->createMbD(); }

	//Create MbD in SI units
	auto asmtUnts = asmtUnits;
	auto& mbdSysSolver = mbdSys()->systemSolver;
	mbdSysSolver->errorTolPosKine = simulationParameters->errorTolPosKine;
	mbdSysSolver->errorTolAccKine = simulationParameters->errorTolAccKine;
	mbdSysSolver->iterMaxPosKine = simulationParameters->iterMaxPosKine;
	mbdSysSolver->iterMaxAccKine = simulationParameters->iterMaxAccKine;
	mbdSysSolver->tstart = simulationParameters->tstart * asmtUnts->time;
	mbdSysSolver->tend = simulationParameters->tend * asmtUnts->time;
	mbdSysSolver->hmin = simulationParameters->hmin * asmtUnts->time;
	mbdSysSolver->hmax = simulationParameters->hmax * asmtUnts->time;
	mbdSysSolver->hout = simulationParameters->hout * asmtUnts->time;
	mbdSysSolver->corAbsTol = simulationParameters->corAbsTol;
	mbdSysSolver->corRelTol = simulationParameters->corRelTol;
	mbdSysSolver->intAbsTol = simulationParameters->intAbsTol;
	mbdSysSolver->intRelTol = simulationParameters->intRelTol;
	mbdSysSolver->iterMaxDyn = simulationParameters->iterMaxDyn;
	mbdSysSolver->orderMax = simulationParameters->orderMax;
	mbdSysSolver->translationLimit = simulationParameters->translationLimit * asmtUnts->length;
	mbdSysSolver->rotationLimit = simulationParameters->rotationLimit;
	//animationParameters = nullptr;
}

void MbD::ASMTAssembly::outputFile(std::string filename)
{
	std::ofstream os(filename);
	os << std::setprecision(std::numeric_limits<double>::max_digits10);
	//	try {
	os << "OndselSolver" << std::endl;
	storeOnLevel(os, 0);
}

void MbD::ASMTAssembly::storeOnLevel(std::ofstream& os, size_t level)
{
	storeOnLevelString(os, level, "Assembly");
	storeOnLevelNotes(os, level + 1);
	storeOnLevelName(os, level + 1);
	ASMTSpatialContainer::storeOnLevel(os, level);

	storeOnLevelParts(os, level + 1);
	storeOnLevelKinematicIJs(os, level + 1);
	storeOnLevelConstraintSets(os, level + 1);
	storeOnLevelForceTorques(os, level + 1);
	constantGravity->storeOnLevel(os, level + 1);
	simulationParameters->storeOnLevel(os, level + 1);
	animationParameters->storeOnLevel(os, level + 1);
	storeOnTimeSeries(os);
}

void MbD::ASMTAssembly::solve()
{
	auto simulationParameters = ASMTSimulationParameters::With();
	simulationParameters->settstart(0.0);
	simulationParameters->settend(0.0);	//tstart == tend Initial Conditions only.
	simulationParameters->sethmin(1.0e-9);
	simulationParameters->sethmax(1.0);
	simulationParameters->sethout(0.04);
	simulationParameters->seterrorTol(1.0e-6);
	setSimulationParameters(simulationParameters);

	runKINEMATIC();
}

void MbD::ASMTAssembly::runPreDrag()
{
	mbdSystem = System::With();
	mbdSystem->externalSystem->asmtAssembly = this;
	try {
		mbdSystem->runPreDrag(mbdSystem);
	}
	catch (SimulationStoppingError ex) {

	}
}

void MbD::ASMTAssembly::runDragStep(std::shared_ptr<std::vector<std::shared_ptr<ASMTPart>>> dragParts) const
{
	auto dragMbDParts = std::make_shared<std::vector<std::shared_ptr<Part>>>();
	for (auto& dragPart : *dragParts) {
		auto dragMbDPart = std::static_pointer_cast<Part>(dragPart->mbdObject);
		dragMbDParts->push_back(dragMbDPart);
	}
	mbdSystem->runDragStep(dragMbDParts);
}

void MbD::ASMTAssembly::runPostDrag()
{
	runPreDrag();
}

void MbD::ASMTAssembly::runKINEMATIC()
{
	mbdSystem = System::With();
	mbdSystem->externalSystem->asmtAssembly = this;
	try {
		mbdSystem->runKINEMATIC(mbdSystem);
	}
	catch (SimulationStoppingError ex) {

	}
}

void MbD::ASMTAssembly::runDYNAMIC()
{
	auto mbdSys = System::With();
	mbdSystem = mbdSys;
	mbdSystem->externalSystem->asmtAssembly = this;
	try {
		mbdSystem->runDYNAMIC(mbdSystem);
	}
	catch (SimulationStoppingError ex) {

	}
}

void MbD::ASMTAssembly::initprincipalMassMarker()
{
	principalMassMarker = ASMTPrincipalMassMarker::With();
	principalMassMarker->mass = 0.0;
	principalMassMarker->density = 0.0;
	principalMassMarker->momentOfInertias = DiagonalMatrix<double>::With(3, 0);
	//principalMassMarker->position3D = std::make_shared<FullColumn<double>>(3, 0);
	//principalMassMarker->rotationMatrix = FullMatrix<double>>::identitysptr(3);
}

std::shared_ptr<ASMTSpatialContainer> MbD::ASMTAssembly::spatialContainerAt(std::shared_ptr<ASMTAssembly> self, std::string& longname) const
{
	if ((self->fullName("")) == longname) return self;
	auto it = std::find_if(parts->begin(), parts->end(), [&](const std::shared_ptr<ASMTPart>& prt) {
		return prt->fullName("") == longname;
		});
	auto& part = *it;
	return part;
}

std::shared_ptr<ASMTMarker> MbD::ASMTAssembly::markerAt(std::string& longname) const
{
	for (auto& refPoint : *refPoints) {
		for (auto& marker : *refPoint->markers) {
			if (marker->fullName("") == longname) return marker;
		}
	}
	for (auto& part : *parts) {
		for (auto& refPoint : *part->refPoints) {
			for (auto& marker : *refPoint->markers) {
				if (marker->fullName("") == longname) return marker;
			}
		}
	}
	return nullptr;
}

std::shared_ptr<ASMTJoint> MbD::ASMTAssembly::jointAt(std::string& longname) const
{
	auto it = std::find_if(joints->begin(), joints->end(), [&](const std::shared_ptr<ASMTJoint>& jt) {
		return jt->fullName("") == longname;
		});
	auto& joint = *it;
	return joint;
}

std::shared_ptr<ASMTMotion> MbD::ASMTAssembly::motionAt(std::string& longname) const
{
	auto it = std::find_if(motions->begin(), motions->end(), [&](const std::shared_ptr<ASMTMotion>& mt) {
		return mt->fullName("") == longname;
		});
	auto& motion = *it;
	return motion;
}

std::shared_ptr<ASMTForceTorque> MbD::ASMTAssembly::forceTorqueAt(std::string& longname) const
{
	auto it = std::find_if(forcesTorques->begin(), forcesTorques->end(), [&](const std::shared_ptr<ASMTForceTorque>& mt) {
		return mt->fullName("") == longname;
		});
	auto& forceTorque = *it;
	return forceTorque;
}

FColDsptr MbD::ASMTAssembly::vOcmO()
{
	return FullColumn<double>::With(3, 0.0);
}

FColDsptr MbD::ASMTAssembly::omeOpO()
{
	return FullColumn<double>::With(3, 0.0);
}

std::shared_ptr<ASMTTime> MbD::ASMTAssembly::geoTime() const
{
	return asmtTime;
}

void MbD::ASMTAssembly::updateFromMbD()
{
	ASMTSpatialContainer::updateFromMbD();
	auto time = asmtTime->getValue();
	times->push_back(time);
	//std::cout << "Time = " << time << std::endl;
	for (auto& part : *parts) part->updateFromMbD();
	for (auto& joint : *joints) joint->updateFromMbD();
	for (auto& motion : *motions) motion->updateFromMbD();
	for (auto& forceTorque : *forcesTorques) forceTorque->updateFromMbD();
}

void MbD::ASMTAssembly::compareResults(AnalysisType type)
{
	ASMTSpatialContainer::compareResults(type);
	for (auto& part : *parts) part->compareResults(type);
	for (auto& joint : *joints) joint->compareResults(type);
	for (auto& motion : *motions) motion->compareResults(type);
	for (auto& forceTorque : *forcesTorques) forceTorque->compareResults(type);
}

void MbD::ASMTAssembly::outputResults(AnalysisType type)
{
	//ASMTSpatialContainer::outputResults(type);
	//for (auto& part : *parts) part->outputResults(type);
	//for (auto& joint : *joints) joint->outputResults(type);
	//for (auto& motion : *motions) motion->outputResults(type);
	//for (auto& forceTorque : *forcesTorques) forceTorque->outputResults(type);
}

void MbD::ASMTAssembly::addTime(std::shared_ptr<ASMTTime> time)
{
	asmtTime = time;
	time->container = this;
}

void MbD::ASMTAssembly::addPart(std::shared_ptr<ASMTPart> part)
{
	parts->push_back(part);
	part->container = this;
}

void MbD::ASMTAssembly::addJoint(std::shared_ptr<ASMTJoint> joint)
{
	joints->push_back(joint);
	joint->container = this;
}

void MbD::ASMTAssembly::addMotion(std::shared_ptr<ASMTMotion> motion)
{
	motions->push_back(motion);
	motion->container = this;
	motion->initMarkers();
}

void MbD::ASMTAssembly::addForceTorque(std::shared_ptr<ASMTForceTorque> forTor)
{
	forcesTorques->push_back(forTor);
	forTor->container = this;
}

void MbD::ASMTAssembly::setConstantGravity(std::shared_ptr<ASMTConstantGravity> gravity)
{
	constantGravity = gravity;
	gravity->container = this;
}

void MbD::ASMTAssembly::setSimulationParameters(std::shared_ptr<ASMTSimulationParameters> parameters)
{
	simulationParameters = parameters;
	parameters->container = this;
}

std::shared_ptr<ASMTPart> MbD::ASMTAssembly::partNamed(std::string partName) const
{
	auto it = std::find_if(parts->begin(), parts->end(), [&](const std::shared_ptr<ASMTPart>& prt) {
		return prt->fullName("") == partName;
		});
	auto& part = *it;
	return part;
}

std::shared_ptr<ASMTPart> MbD::ASMTAssembly::partPartialNamed(std::string partialName) const
{
	auto it = std::find_if(parts->begin(), parts->end(), [&](const std::shared_ptr<ASMTPart>& prt) {
		auto fullName = prt->fullName("");
		return fullName.find(partialName) != std::string::npos;
		});
	auto& part = *it;
	return part;
}

void MbD::ASMTAssembly::storeOnLevelNotes(std::ofstream& os, size_t level)
{
	storeOnLevelString(os, level, "Notes");
	storeOnLevelString(os, level + 1, notes);
}

void MbD::ASMTAssembly::storeOnLevelParts(std::ofstream& os, size_t level)
{
	storeOnLevelString(os, level, "Parts");
	for (auto& part : *parts) {
		part->storeOnLevel(os, level + 1);
	}
}

void MbD::ASMTAssembly::storeOnLevelKinematicIJs(std::ofstream& os, size_t level)
{
	storeOnLevelString(os, level, "KinematicIJs");
	for (auto& kinematicIJ : *kinematicIJs) {
		kinematicIJ->storeOnLevel(os, level);
	}
}

void MbD::ASMTAssembly::storeOnLevelConstraintSets(std::ofstream& os, size_t level)
{
	storeOnLevelString(os, level, "ConstraintSets");
	storeOnLevelJoints(os, level + 1);
	storeOnLevelMotions(os, level + 1);
	storeOnLevelGeneralConstraintSets(os, level + 1);
}

void MbD::ASMTAssembly::storeOnLevelForceTorques(std::ofstream& os, size_t level)
{
	storeOnLevelString(os, level, "ForceTorques");
	for (auto& forceTorque : *forcesTorques) {
		forceTorque->storeOnLevel(os, level + 1);
	}
}

void MbD::ASMTAssembly::storeOnLevelJoints(std::ofstream& os, size_t level)
{
	storeOnLevelString(os, level, "Joints");
	for (auto& joint : *joints) {
		joint->storeOnLevel(os, level + 1);
	}
}

void MbD::ASMTAssembly::storeOnLevelMotions(std::ofstream& os, size_t level)
{
	storeOnLevelString(os, level, "Motions");
	for (auto& motion : *motions) {
		motion->storeOnLevel(os, level + 1);
	}
}

void MbD::ASMTAssembly::storeOnLevelGeneralConstraintSets(std::ofstream& os, size_t level)
{
	storeOnLevelString(os, level, "GeneralConstraintSets");
	//for (auto& generalConstraintSet : *generalConstraintSets) {
	//	generalConstraintSet->storeOnLevel(os, level);
	//}
}

void MbD::ASMTAssembly::storeOnTimeSeries(std::ofstream& os)
{
	if (times->empty()) return;
	os << "TimeSeries" << std::endl;
	os << "Number\tInput\t";
	for (size_t i = 1; i < times->size(); i++)
	{
		os << i << '\t';
	}
	os << std::endl;
	os << "Time\tInput\t";
	for (size_t i = 1; i < times->size(); i++)
	{
		os << times->at(i) << '\t';
	}
	os << std::endl;
	os << "AssemblySeries\t" << fullName("") << std::endl;
	ASMTSpatialContainer::storeOnTimeSeries(os);
	for (auto& part : *parts) part->storeOnTimeSeries(os);
	for (auto& joint : *joints) joint->storeOnTimeSeries(os);
	for (auto& motion : *motions) motion->storeOnTimeSeries(os);
	for (auto& forTor : *forcesTorques) forTor->storeOnTimeSeries(os);
}

void MbD::ASMTAssembly::setFilename(std::string str)
{
	std::stringstream ss;
	ss << "FileName = " << str;
	auto str2 = ss.str();
	logString(str2);
	filename = str;
}

void MbD::ASMTAssembly::updateFromInputState()
{
	ASMTSpatialContainer::updateFromInputState();
	for (auto& part : *parts) part->updateFromInputState();
	for (auto& joint : *joints) joint->updateFromInputState();
	for (auto& motion : *motions) motion->updateFromInputState();
}


