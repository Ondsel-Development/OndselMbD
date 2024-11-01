#include <regex>

#include "MBDynGravity.h"
#include "ASMTConstantGravity.h"
#include "ASMTAssembly.h"

using namespace MbD;

std::shared_ptr<MBDynGravity> MbD::MBDynGravity::With()
{
	auto inst = std::make_shared<MBDynGravity>();
	inst->initialize();
	return inst;
}

void MbD::MBDynGravity::parseMBDyn(std::string line)
{
	gravityString = line;
	arguments = collectArgumentsFor("gravity", line);
	assert(arguments.at(0).find("uniform") != std::string::npos);
	arguments.erase(arguments.begin());
	gvec = readPosition(arguments);
	assert(arguments.at(0).find("string") != std::string::npos);
	arguments.erase(arguments.begin());
	auto iss = std::istringstream(arguments.at(0));
	iss >> formula;
	formula = std::regex_replace(formula, std::regex("\""), "");
	double mag;
	iss = std::istringstream(formula);
	iss >> mag;

	arguments.erase(arguments.begin());
	gvec->normalizeSelf();
	gvec->magnifySelf(mag);
}

void MbD::MBDynGravity::readFunction(std::vector<std::string>&)
{
	assert(false);
	noop();
}

void MbD::MBDynGravity::createASMT()
{
	auto asmtGravity = ASMTConstantGravity::With();
	asmtGravity->setg(gvec);
	asmtAssembly()->setConstantGravity(asmtGravity);
}
