/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "ASMTPrincipalMassMarker.h"
#include <cassert>
#include "FullMatrix.h"

using namespace MbD;

std::shared_ptr<ASMTPrincipalMassMarker> MbD::ASMTPrincipalMassMarker::With()
{
	auto inst = std::make_shared<ASMTPrincipalMassMarker>();
	inst->initialize();
	return inst;
}

void MbD::ASMTPrincipalMassMarker::initialize()
{
	name = "MassMarker";
}

void MbD::ASMTPrincipalMassMarker::parseASMT(std::vector<std::string>& lines)
{
	size_t pos = lines[0].find_first_not_of("\t");
	auto leadingTabs = lines[0].substr(0, pos);
	assert(lines[0] == (leadingTabs + "Name"));
	lines.erase(lines.begin());
	name = readStringNoSpacesOffTop(lines);
	assert(lines[0] == (leadingTabs + "Position3D"));
	lines.erase(lines.begin());
	position3D = readColumnOfDoubles(lines[0]);
	lines.erase(lines.begin());
	assert(lines[0] == (leadingTabs + "RotationMatrix"));
	lines.erase(lines.begin());
	rotationMatrix = FullMatrix<double>::With(3);
	for (size_t i = 0; i < 3; i++)
	{
		auto row = readRowOfDoubles(lines[0]);
		rotationMatrix->atput(i, row);
		lines.erase(lines.begin());
	}
	assert(lines[0] == (leadingTabs + "Mass"));
	lines.erase(lines.begin());
	mass = readDouble(lines[0]);
	lines.erase(lines.begin());
	assert(lines[0] == (leadingTabs + "MomentOfInertias"));
	lines.erase(lines.begin());
	momentOfInertias = DiagonalMatrix<double>::With(3);
	auto row = readRowOfDoubles(lines[0]);
	lines.erase(lines.begin());
	for (size_t i = 0; i < 3; i++)
	{
		momentOfInertias->atput(i, row->at(i));
	}
	assert(lines[0] == (leadingTabs + "Density"));
	lines.erase(lines.begin());
	density = readDouble(lines[0]);
	lines.erase(lines.begin());
}

void MbD::ASMTPrincipalMassMarker::setMass(double m)
{
	mass = m;
}

void MbD::ASMTPrincipalMassMarker::setDensity(double rho)
{
	density = rho;
}

void MbD::ASMTPrincipalMassMarker::setMomentOfInertias(DiagMatDsptr mat)
{
	momentOfInertias = mat;
}

// Overloads to simplify syntax.
void MbD::ASMTPrincipalMassMarker::setMomentOfInertias(double a, double b, double c)
{
	momentOfInertias = DiagonalMatrix<double>::With(ListD{ a, b, c });
}

void MbD::ASMTPrincipalMassMarker::storeOnLevel(std::ofstream& os, size_t level)
{
	storeOnLevelString(os, level, "PrincipalMassMarker");
	storeOnLevelString(os, level + 1, "Name");
	storeOnLevelString(os, level + 2, name);
	ASMTSpatialItem::storeOnLevel(os, level);
	storeOnLevelString(os, level + 1, "Mass");
	storeOnLevelDouble(os, level + 2, mass);
	storeOnLevelString(os, level + 1, "MomentOfInertias");
	storeOnLevelArray(os, level + 2, *momentOfInertias);
	storeOnLevelString(os, level + 1, "Density");
	storeOnLevelDouble(os, level + 2, density);
}

void MbD::ASMTPrincipalMassMarker::zeroMass()
{
	mass = 0.0;
	density = 0.0;
	momentOfInertias = DiagonalMatrix<double>::With(ListD{ 0.0, 0.0, 0.0 });
}
