/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselMbD.                                       *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#include "ASMTPart.h"
#include "CREATE.h"

using namespace MbD;

void MbD::ASMTPart::parseASMT(std::vector<std::string>& lines)
{
	readName(lines);
	readPosition3D(lines);
	readRotationMatrix(lines);
	readVelocity3D(lines);
	readOmega3D(lines);
	readFeatureOrder(lines);
	readPrincipalMassMarker(lines);
	readRefPoints(lines);
	readRefCurves(lines);
	readRefSurfaces(lines);
}

void MbD::ASMTPart::readFeatureOrder(std::vector<std::string>& lines)
{
	assert(lines[0].find("FeatureOrder") != std::string::npos);
	lines.erase(lines.begin());
	//featureOrder = std::make_shared<std::vector<std::shared_ptr<ASMTRefPoint>>>();
	auto it = std::find_if(lines.begin(), lines.end(), [](const std::string& s) {
		return s.find("PrincipalMassMarker") != std::string::npos;
		});
	//std::vector<std::string> featureOrderLines(lines.begin(), it);
	//while (!featureOrderLines.empty()) {
	//	if (featureOrderLines[0] == (leadingTabs + "\tExtrusion")) {
	//		featureOrderLines.erase(featureOrderLines.begin());
	//		auto extrusion = CREATE<ASMTExtrusion>::With();
	//		extrusion->parseASMT(featureOrderLines);
	//		featureOrder->push_back(extrusion);
	//		extrusion->owner = this;
	//	}
	//	else {
	//		assert(false);
	//	}
	//}
	lines.erase(lines.begin(), it);
}

void MbD::ASMTPart::readPrincipalMassMarker(std::vector<std::string>& lines)
{
	assert(lines[0].find("PrincipalMassMarker") != std::string::npos);
	lines.erase(lines.begin());
	principalMassMarker = CREATE<ASMTPrincipalMassMarker>::With();
	principalMassMarker->parseASMT(lines);
	principalMassMarker->owner = this;
}

void MbD::ASMTPart::readPartSeries(std::vector<std::string>& lines)
{
	std::string str = lines[0];
	std::string substr = "PartSeries";
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

FColDsptr MbD::ASMTPart::vOcmO()
{
	auto& rOPO = position3D;
	auto& vOPO = velocity3D;
	auto& omeOPO = omega3D;
	auto rPcmO = rOcmO()->minusFullColumn(rOPO);
	return vOPO->plusFullColumn(omeOPO->cross(rPcmO));
}

FColDsptr MbD::ASMTPart::omeOpO()
{
	return omega3D;
}
