#include <string>
#include <cassert>
#include <fstream>	
#include <numeric>
#include <iomanip>

#include "MBDynSystem.h"
#include "FullColumn.h"
#include "MBDynInitialValue.h"
#include "MBDynData.h"
#include "MBDynControlData.h"
#include "ASMTAssembly.h"
#include "ASMTConstantGravity.h"
#include "ASMTTime.h"
#include "MBDynBody.h"
#include "MBDynJoint.h"
#include "MBDynStructural.h"
#include "SymbolicParser.h"
#include "BasicUserFunction.h"
#include "MBDynReference.h"
#include "MBDynDrive.h"
#include "MBDynGravity.h"

using namespace MbD;

std::shared_ptr<MBDynSystem> MbD::MBDynSystem::With()
{
	auto inst = std::make_shared<MBDynSystem>();
	inst->initialize();
	return inst;
}

std::shared_ptr<MBDynSystem> MbD::MBDynSystem::fromFile(const char* filename)
{
	std::ifstream stream(filename);
	std::string line;
	std::vector<std::string> lines;
	while (std::getline(stream, line)) {
		lines.push_back(line);
	}
	eraseComments(lines);
	auto statements = collectStatements(lines);

	auto system = MBDynSystem::With();
	system->setFilename(filename);
	system->parseMBDyn(statements);
	return system;
}

void MbD::MBDynSystem::runFile(const char* filename)
{
	auto system = MBDynSystem::fromFile(filename);
	system->runKINEMATIC();
}

void MbD::MBDynSystem::runDynFile(const char* filename)
{
	auto system = MBDynSystem::fromFile(filename);
	system->runDYNAMIC();
}

void MbD::MBDynSystem::parseMBDyn(std::vector<std::string>& lines)
{
	readDataBlock(lines);
	readInitialValueBlock(lines);
	readControlDataBlock(lines);
	readLabels(lines);
	readVariables(lines);
	readReferences(lines);
	readScalarFunctions(lines);
	readNodesBlock(lines);
	readElementsBlock(lines);
	assert(lines.empty());
}

std::shared_ptr<std::vector<std::shared_ptr<MBDynNode>>> MbD::MBDynSystem::mbdynNodes()
{
	return nodes;
}

std::shared_ptr<std::vector<std::shared_ptr<MBDynBody>>> MbD::MBDynSystem::mbdynBodies()
{
	return bodies;
}

std::shared_ptr<std::vector<std::shared_ptr<MBDynJoint>>> MbD::MBDynSystem::mbdynJoints()
{
	return joints;
}

std::shared_ptr<std::vector<std::shared_ptr<MBDynDrive>>> MbD::MBDynSystem::mbdynDrives()
{
	return drives;
}

std::shared_ptr<std::map<std::string, Symsptr>> MbD::MBDynSystem::mbdynVariables()
{
	return variables;
}

std::shared_ptr<std::map<std::string, std::shared_ptr<MBDynReference>>> MbD::MBDynSystem::mbdynReferences()
{
	return references;
}

void MbD::MBDynSystem::createASMT()
{
	auto asmtAsm = ASMTAssembly::With();
	asmtAsm->mbdynItem = this;
	asmtItem = asmtAsm;
	asmtItem->setName("Assembly");
	initialValue->createASMT();
	for (auto& node : *nodes) node->createASMT();
	for (auto& body : *bodies) body->createASMT();
	for (auto& joint : *joints) joint->createASMT();
	for (auto& plugin : *plugins) plugin->createASMT();
	if (gravity) gravity->createASMT();
}

std::shared_ptr<MBDynNode> MbD::MBDynSystem::nodeAt(std::string nodeName)
{
	for (auto& node : *nodes) {
		if (node->label == nodeName) return node;
	}
	return nullptr;
}

int MbD::MBDynSystem::labelIDat(std::string nodeName)
{
	return labels->at(nodeName);
}

std::shared_ptr<MBDynBody> MbD::MBDynSystem::bodyWithNode(std::string nodeName)
{
	for (auto& body : *bodies) {
		if (body->nodeName == nodeName) return body;
	}
	return nullptr;
}

std::shared_ptr<ASMTAssembly> MbD::MBDynSystem::asmtAssembly()
{
	return std::static_pointer_cast<ASMTAssembly>(asmtItem);
}

std::vector<std::string> MbD::MBDynSystem::nodeNames()
{
	auto nodeNames = std::vector<std::string>();
	for (auto& node : *nodes) {
		nodeNames.push_back(node->label);
	}
	return nodeNames;
}

void MbD::MBDynSystem::runKINEMATIC()
{
	createASMT();
	//auto debugFile1 = filename.substr(0, filename.find_last_of('.')) + "debug1.asmt";
	//asmtAssembly()->outputFile(debugFile1);
	std::static_pointer_cast<ASMTAssembly>(asmtItem)->runKINEMATIC();
	outputFiles();
	//auto debugFile2 = filename.substr(0, filename.find_last_of('.')) + "debug2.asmt";
	//asmtAssembly()->outputFile(debugFile2);
}

void MbD::MBDynSystem::runDYNAMIC()
{
	createASMT();
	auto debugFile1 = filename.substr(0, filename.find_last_of('.')) + "debug1.asmt";
	asmtAssembly()->outputFile(debugFile1);
	std::static_pointer_cast<ASMTAssembly>(asmtItem)->runDYNAMIC();
	outputFiles();
	auto debugFile2 = filename.substr(0, filename.find_last_of('.')) + "debug2.asmt";
	asmtAssembly()->outputFile(debugFile2);
}

void MbD::MBDynSystem::outputFiles()
{
	outputNodesFile();
	outputJointsFile();
}

void MbD::MBDynSystem::outputNodesFile()
{
	auto movFile = filename.substr(0, filename.find_last_of('.')) + ".mov";
	auto asmtAsm = asmtAssembly();
	auto& asmtTimes = asmtAsm->times;
	//auto& asmtParts = asmtAsm->parts;
	//auto& asmtJoints = asmtAsm->joints;
	//auto& asmtMotions = asmtAsm->motions;
	std::ofstream os(movFile);
	os << std::setprecision(std::numeric_limits<double>::max_digits10);
	for (size_t i = 1; i < asmtTimes->size(); i++)
	{
		for (auto& node : *nodes) {
			node->outputLine(i, os);
		}
	}
}

void MbD::MBDynSystem::outputJointsFile()
{
	auto jntFile = filename.substr(0, filename.find_last_of('.')) + ".jnt";
	auto asmtAsm = asmtAssembly();
	auto& asmtTimes = asmtAsm->times;
	std::ofstream os(jntFile);
	os << std::setprecision(std::numeric_limits<double>::max_digits10);
	for (size_t i = 1; i < asmtTimes->size(); i++)
	{
		for (auto& joint : *joints) {
			joint->outputLine(i, os);
		}
	}
}

void MbD::MBDynSystem::setFilename(std::string str)
{
	std::stringstream ss;
	ss << "FileName = " << str << std::endl;
	auto str2 = ss.str();
	logString(str2);
	filename = str;
}

void MbD::MBDynSystem::readDataBlock(std::vector<std::string>& lines)
{
	std::vector<std::string> tokens{ "begin:", "data" };
	auto beginit = findLineWith(lines, tokens);
	std::vector<std::string> tokens1{ "end:", "data" };
	auto endit = findLineWith(lines, tokens1);
	std::vector<std::string> blocklines = { beginit, endit + 1 };
	parseMBDynData(blocklines);
	lines.erase(beginit, endit + 1);
}

void MbD::MBDynSystem::readInitialValueBlock(std::vector<std::string>& lines)
{
	std::vector<std::string> tokens{ "begin:", "initial", "value" };
	auto beginit = findLineWith(lines, tokens);
	std::vector<std::string> tokens1{ "end:", "initial", "value" };
	auto endit = findLineWith(lines, tokens1);
	std::vector<std::string> blocklines = { beginit, endit + 1 };
	initialValue = MBDynInitialValue::With();
	initialValue->container = this;
	initialValue->parseMBDyn(blocklines);
	lines.erase(beginit, endit + 1);
}

void MbD::MBDynSystem::readControlDataBlock(std::vector<std::string>& lines)
{
	std::vector<std::string> tokens{ "begin:", "control", "data" };
	auto beginit = findLineWith(lines, tokens);
	std::vector<std::string> tokens1{ "end:", "control", "data" };
	auto endit = findLineWith(lines, tokens1);
	std::vector<std::string> blocklines = { beginit, endit + 1 };
	controlData = MBDynControlData::With();
	controlData->container = this;
	controlData->parseMBDyn(blocklines);
	lines.erase(beginit, endit + 1);
}

void MbD::MBDynSystem::readLabels(std::vector<std::string>& lines)
{
	parseMBDynLabels(lines);
}

void MbD::MBDynSystem::readVariables(std::vector<std::string>& lines)
{
	parseMBDynVariables(lines);
}

void MbD::MBDynSystem::readReferences(std::vector<std::string>& lines)
{
	parseMBDynReferences(lines);
}

void MbD::MBDynSystem::readScalarFunctions(std::vector<std::string>& lines)
{
	parseMBDynScalarFunctions(lines);
}

void MbD::MBDynSystem::readNodesBlock(std::vector<std::string>& lines)
{
	std::vector<std::string> tokens{ "begin:", "nodes" };
	auto beginit = findLineWith(lines, tokens);
	std::vector<std::string> tokens1{ "end:", "nodes" };
	auto endit = findLineWith(lines, tokens1);
	std::vector<std::string> blocklines = { beginit, endit + 1 };
	parseMBDynNodes(blocklines);
	lines.erase(beginit, endit + 1);
}

void MbD::MBDynSystem::readElementsBlock(std::vector<std::string>& lines)
{
	std::vector<std::string> tokens{ "begin:", "elements" };
	auto beginit = findLineWith(lines, tokens);
	std::vector<std::string> tokens1{ "end:", "elements" };
	auto endit = findLineWith(lines, tokens1);
	std::vector<std::string> blocklines = { beginit, endit + 1 };
	parseMBDynElements(blocklines);
	lines.erase(beginit, endit + 1);
}

void MbD::MBDynSystem::eraseComments(std::vector<std::string>& lines)
{
	for (size_t i = 0; i < lines.size(); i++)
	{
		auto& line = lines[i];
		auto it = line.find('#');
		if (it != std::string::npos) {
			lines[i] = line.substr(0, it);
		}
	}
	for (int i = (int)lines.size() - 1; i >= 0; i--)	//Use int because of decrement
	{
		auto& line = lines[i];
		auto it = std::find_if(line.begin(), line.end(), [](unsigned char ch) { return !std::isspace(ch); });
		if (it == line.end()) lines.erase(lines.begin() + i);
	}
}

std::vector<std::string> MbD::MBDynSystem::collectStatements(std::vector<std::string>& lines)
{
	auto statements = std::vector<std::string>();
	while (!lines.empty()) {
		std::stringstream ss;
		while (!lines.empty()) {
			std::string line = lines[0];	//Must copy string
			lines.erase(lines.begin());
			auto i = line.find(';');
			if (i != std::string::npos) {
				ss << line.substr(0, i);
				if (line.size() > i + 1) {
					auto remainder = line.substr(i + 1);
					auto it = std::find_if(remainder.begin(), remainder.end(), [](unsigned char ch) { return !std::isspace(ch); });
					if (it != remainder.end()) lines.insert(lines.begin(), remainder);
				}
				break;
			}
			else {
				ss << line;
			}
		}
		statements.push_back(ss.str());
	}
	return statements;
}

MBDynSystem* MbD::MBDynSystem::root()
{
	return this;
}

void MbD::MBDynSystem::initialize()
{
	//Do nothing.
}

void MbD::MBDynSystem::parseMBDynData(std::vector<std::string>& lines)
{
	assert(lines.size() == 3);
	std::vector<std::string> tokens{ "problem:", "initial", "value" };
	auto problemit = findLineWith(lines, tokens);
	assert(problemit != lines.end());
	data = *problemit;
}

void MbD::MBDynSystem::parseMBDynNodes(std::vector<std::string>& lines)
{
	nodes = std::make_shared<std::vector<std::shared_ptr<MBDynNode>>>();
	std::vector<std::string> tokens{ "structural:" };
	while (true) {
		auto it = findLineWith(lines, tokens);
		if (it != lines.end()) {
			auto structural = MBDynStructural::newStructural(*it);
			structural->container = this;
			structural->parseMBDyn(*it);
			nodes->push_back(structural);
			lines.erase(it);
		}
		else {
			break;
		}
	}
}

void MbD::MBDynSystem::parseMBDynElements(std::vector<std::string>& lines)
{

	assert(lineHasTokens(3, popOffTop(lines), "begin:", "elements"));
	bodies = std::make_shared<std::vector<std::shared_ptr<MBDynBody>>>();
	joints = std::make_shared<std::vector<std::shared_ptr<MBDynJoint>>>();
	plugins = std::make_shared<std::vector<std::shared_ptr<MBDynPlugin>>>();
	drives = std::make_shared<std::vector<std::shared_ptr<MBDynDrive>>>();
	forces = std::make_shared<std::vector<std::shared_ptr<MBDynForce>>>();
	genels = std::make_shared<std::vector<std::shared_ptr<MBDynGenel>>>();
	std::vector<std::string> bodyTokens{ "body:" };
	std::vector<std::string> jointTokens{ "joint:" };
	std::vector<std::string> setTokens{ "set:" };
	std::vector<std::string> driveTokens{ "drive", "caller:" };
	std::vector<std::string> gravityTokens{ "gravity" };
	std::vector<std::string> forceTokens{ "force:" };
	std::vector<std::string> genelTokens{ "genel:" };
	std::vector<std::string>::iterator it;
	while (true) {
		it = findLineWith(lines, bodyTokens);
		if (it != lines.end()) {
			auto body = MBDynBody::With();
			body->container = this;
			body->parseMBDyn(*it);
			bodies->push_back(body);
			lines.erase(it);
			continue;
		}
		it = findLineWith(lines, jointTokens);
		if (it != lines.end()) {
			auto joint = MBDynJoint::newJoint(*it);
			joint->container = this;
			joint->parseMBDyn(*it);
			joints->push_back(joint);
			lines.erase(it);
			continue;
		}
		it = findLineWith(lines, setTokens);
		if (it != lines.end()) {
			auto plugin = MBDynPlugin::newPlugin(*it);
			plugin->container = this;
			plugin->parseMBDyn(*it);
			plugins->push_back(plugin);
			lines.erase(it);
			continue;
		}
		it = findLineWith(lines, driveTokens);
		if (it != lines.end()) {
			auto drive = MBDynDrive::newDrive(*it);
			drive->container = this;
			drive->parseMBDyn(*it);
			drives->push_back(drive);
			lines.erase(it);
			continue;
		}
		it = findLineWith(lines, gravityTokens);
		if (it != lines.end()) {
			auto grav = MBDynGravity::With();
			grav->container = this;
			grav->parseMBDyn(*it);
			gravity = grav;
			lines.erase(it);
			continue;
		}
		it = findLineWith(lines, forceTokens);
		if (it != lines.end()) {
			auto force = MBDynForce::newForce(*it);
			force->container = this;
			force->parseMBDyn(*it);
			forces->push_back(force);
			lines.erase(it);
			continue;
		}
		it = findLineWith(lines, genelTokens);
		if (it != lines.end()) {
			auto genel = MBDynGenel::newGenel(*it);
			genel->container = this;
			genel->parseMBDyn(*it);
			genels->push_back(genel);
			lines.erase(it);
			continue;
		}
		break;
	}
	assert(lineHasTokens(3, popOffTop(lines), "end:", "elements"));
}

void MbD::MBDynSystem::parseMBDynVariables(std::vector<std::string>& lines)
{
	variables = std::make_shared<std::map<std::string, Symsptr>>();
	std::string str, variable;
	std::vector<std::string> tokens{ "set:", "real" };
	while (true) {
		auto it = findLineWith(lines, tokens);
		if (it != lines.end()) {
			std::istringstream iss(*it);
			iss >> str;
			iss >> str;
			iss >> variable;
			iss >> str;
			str = iss.str();
			auto previousPos = str.find("=");
			str = str.substr(previousPos + 1);
			auto parser = std::make_shared<SymbolicParser>();
			parser->variables = variables;
			auto userFunc = std::make_shared<BasicUserFunction>(str, 1.0);
			parser->parseUserFunction(userFunc);
			auto sym = parser->stack->top()->simplified();
			//auto val = sym->getValue();
			variables->insert(std::make_pair(variable, sym));
			lines.erase(it);
		}
		else {
			break;
		}
	}
}

void MbD::MBDynSystem::parseMBDynLabels(std::vector<std::string>& lines)
{
	labels = std::make_shared<std::map<std::string, int>>();
	std::string str;
	int intValue;
	std::vector<std::string> tokens{ "set:", "integer" };
	while (true) {
		auto it = findLineWith(lines, tokens);
		if (it != lines.end()) {
			std::istringstream iss(*it);
			iss >> str;
			iss >> str;
			iss >> label;
			iss >> str;
			iss >> intValue;
			labels->insert(std::make_pair(label, intValue));
			lines.erase(it);
		}
		else {
			break;
		}
	}
}

void MbD::MBDynSystem::parseMBDynReferences(std::vector<std::string>& lines)
{
	references = std::make_shared<std::map<std::string, std::shared_ptr<MBDynReference>>>();
	std::string str, refName;
	std::vector<std::string> tokens{ "reference:" };
	while (true) {
		auto it = findLineWith(lines, tokens);
		if (it != lines.end()) {
			auto reference = MBDynReference::With();
			reference->container = this;
			reference->parseMBDyn(*it);
			references->insert(std::make_pair(reference->label, reference));
			lines.erase(it);
		}
		else {
			break;
		}
	}
}

void MbD::MBDynSystem::parseMBDynScalarFunctions(std::vector<std::string>& lines)
{
	scalarFunctions = std::make_shared<std::map<std::string, std::shared_ptr<MBDynScalarFunction>>>();
	std::string str, refName;
	std::vector<std::string> tokens{ "scalar", "function:" };
	while (true) {
		auto it = findLineWith(lines, tokens);
		if (it != lines.end()) {
			auto reference = MBDynScalarFunction::With();
			reference->container = this;
			reference->parseMBDyn(*it);
			scalarFunctions->insert(std::make_pair(reference->label, reference));
			lines.erase(it);
		}
		else {
			break;
		}
	}
}
