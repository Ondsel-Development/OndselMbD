#include "MBDynItem.h"
#include "MBDynSystem.h"
#include "SymbolicParser.h"
#include "BasicUserFunction.h"
#include "EulerAngles.h"
#include "Constant.h"
#include "MBDynReference.h"
#include "FullMatrix.h"
#include "ASMTItem.h"
#include "MBDynBody.h"
#include "MBDynDrive.h"
#include "MBDynGravity.h"
#include <cstdarg>


using namespace MbD;

std::shared_ptr<MBDynItem> MbD::MBDynItem::With()
{
	auto inst = std::make_shared<MBDynItem>();
	inst->initialize();
	return inst;
}

void MbD::MBDynItem::initialize()
{
	assert(false);
}

MBDynSystem* MbD::MBDynItem::root()
{
	return container->root();
}

void MbD::MBDynItem::noop()
{
	//No Operations
}

void MbD::MBDynItem::parseMBDyn(std::vector<std::string>&)
{
	assert(false);
}

void MbD::MBDynItem::parseMBDyn(std::string)
{
	assert(false);
}

void MbD::MBDynItem::readFunction(std::vector<std::string>& args)
{
	assert(false);
}

std::vector<std::string> MbD::MBDynItem::collectArgumentsFor(std::string title, std::string& statement)
{
	size_t previousPos = 0;
	auto pos = statement.find(":");
	auto front = statement.substr(previousPos, pos - previousPos);
	assert(front.find(title) != std::string::npos);
	auto arguments = std::vector<std::string>();
	std::string argument;
	while (true) {
		previousPos = pos;
		pos = statement.find(",", pos + 1);
		if (pos != std::string::npos) {
			argument = statement.substr(previousPos + 1, pos - previousPos - 1);
			arguments.push_back(argument);
		}
		else {
			argument = statement.substr(previousPos + 1);
			arguments.push_back(argument);
			break;
		}
	}
	auto arguments2 = std::vector<std::string>();
	while (!arguments.empty()) {
		argument = arguments[0];
		auto n = std::count(argument.begin(), argument.end(), '"');
		if ((n % 2) == 0) {
			arguments2.push_back(argument);
			arguments.erase(arguments.begin());
		}
		else {
			//Need to find matching '"'
			auto it = std::find_if(arguments.begin() + 1, arguments.end(), [](const std::string& s) {
				auto nn = std::count(s.begin(), s.end(), '"');
				return (nn % 2) == 1;
				});
			std::vector<std::string> needToCombineArgs(arguments.begin(), it + 1);
			arguments.erase(arguments.begin(), it + 1);
			std::stringstream ss;
			ss << needToCombineArgs[0];
			needToCombineArgs.erase(needToCombineArgs.begin());
			for (auto& arg : needToCombineArgs) {
				ss << ',' << arg;
			}
			arguments2.push_back(ss.str());
		}
	}
	return arguments2;
}

std::vector<std::string>::iterator MbD::MBDynItem::findLineWith(std::vector<std::string>& lines, std::vector<std::string>& tokens)
{
	auto it = std::find_if(lines.begin(), lines.end(), [&](const std::string& line) {
		return lineHasTokens(line, tokens);
		});
	return it;
}

bool MbD::MBDynItem::lineHasToken(const std::string& line, const std::string& token)
{
	return line.find(token) != std::string::npos;
}

bool MbD::MBDynItem::lineHasTokens(const std::string& line, std::vector<std::string>& tokens)
{
	size_t index = 0;
	for (auto& token : tokens) {
		index = line.find(token, index);
		if (index == std::string::npos) return false;
		index++;
	}
	return true;
}

bool MbD::MBDynItem::lineHasTokens(int narg, ...)
{
	va_list ap;
	va_start(ap, narg);
	std::string line = va_arg(ap, std::string);
	size_t index = 0;
	for (int i = 2; i <= narg; i++) {
		std::string token = va_arg(ap, char*);
		index = line.find(token, index);
		if (index == std::string::npos) {
			va_end(ap);
			return false;
		}
		index++;
	}
	va_end(ap);
	return true;
}

//bool MbD::MBDynItem::lineHasTokens(int narg, ...)
//{
//	va_list ap;
//	va_start(ap, narg);
//	std::string line = va_arg(ap, std::string);
//	std::vector<std::string> tokens;
//	for (int i = 2; i <= narg; i++) {
//		std::string str = va_arg(ap, char*);
//		tokens.push_back(str);
//	}
//	va_end(ap);
//	return lineHasTokens(line, tokens);
//}

std::shared_ptr<std::vector<std::shared_ptr<MBDynNode>>> MbD::MBDynItem::mbdynNodes()
{
	return container->mbdynNodes();
}

std::shared_ptr<std::vector<std::shared_ptr<MBDynBody>>> MbD::MBDynItem::mbdynBodies()
{
	return container->mbdynBodies();
}

std::shared_ptr<std::vector<std::shared_ptr<MBDynJoint>>> MbD::MBDynItem::mbdynJoints()
{
	return container->mbdynJoints();
}

std::shared_ptr<std::vector<std::shared_ptr<MBDynDrive>>> MbD::MBDynItem::mbdynDrives()
{
	return container->mbdynDrives();
}

std::vector<std::string> MbD::MBDynItem::nodeNames()
{
	return container->nodeNames();
}

std::shared_ptr<std::map<std::string, Symsptr>> MbD::MBDynItem::mbdynVariables()
{
	return container->mbdynVariables();
}

std::shared_ptr<std::map<std::string, std::shared_ptr<MBDynReference>>> MbD::MBDynItem::mbdynReferences()
{
	return container->mbdynReferences();
}

void MbD::MBDynItem::createASMT()
{
	assert(false);
}

std::shared_ptr<MBDynNode> MbD::MBDynItem::nodeAt(std::string nodeName)
{
	return container->nodeAt(nodeName);
}

int MbD::MBDynItem::labelIDat(std::string nodeName)
{
	return container->labelIDat(nodeName);
}

std::shared_ptr<MBDynBody> MbD::MBDynItem::bodyWithNode(std::string nodeName)
{
	return container->bodyWithNode(nodeName);
}

std::shared_ptr<ASMTAssembly> MbD::MBDynItem::asmtAssembly()
{
	return container->asmtAssembly();
}

std::string MbD::MBDynItem::formulaFromDrive(std::string driveName, std::string varName)
{
	std::vector<std::string> tokens{ "drive:", driveName };
	auto drives = mbdynDrives();
	auto it = std::find_if(drives->begin(), drives->end(), [&](auto& drive) {
		return lineHasTokens(drive->driveName, tokens);
		});
	auto& formula = (*it)->formula;
	assert(varName == "Time");
	return formula;
}

void MbD::MBDynItem::logString(std::string& str)
{
	std::cout << str << std::endl;
}

FColDsptr MbD::MBDynItem::readVector3(std::vector<std::string>& args)
{
	auto parser = std::make_shared<SymbolicParser>();
	parser->variables = mbdynVariables();
	auto col3D = std::make_shared<FullColumn<double>>(3);
	auto str = args.at(0); //Must copy string
	if (str.find("null") != std::string::npos) {
		args.erase(args.begin());
	}
	else {
		for (size_t i = 0; i < 3; i++)
		{
			auto userFunc = std::make_shared<BasicUserFunction>(popOffTop(args), 1.0);
			parser->parseUserFunction(userFunc);
			auto& sym = parser->stack->top();
			col3D->at(i) = sym->getValue();
		}

	}
	return col3D;
}

FColDsptr MbD::MBDynItem::readPosition(std::vector<std::string>& args)
{
	auto rOfO = std::make_shared<FullColumn<double>>(3);
	if (args.empty()) return rOfO;
	auto str = args.at(0); //Must copy string
	if (str.find("position") != std::string::npos) {
		args.erase(args.begin());
		rOfO = readPosition(args);
	}
	else if (str.find("orientation") != std::string::npos) {
		//Do nothing
	}
	else if (str.find("reference") != std::string::npos) {
		args.erase(args.begin());
		auto refName = readStringNoSpacesOffTop(args);
		auto& ref = mbdynReferences()->at(refName);
		auto rFfF = readBasicPosition(args);
		auto& rOFO = ref->rFfF;
		auto& aAOF = ref->aAFf;
		rOfO = rOFO->plusFullColumn(aAOF->timesFullColumn(rFfF));
	}
	else if (str.find("offset") != std::string::npos) {
		args.erase(args.begin());
		rOfO = readBasicPosition(args);
	}
	else if (str.find("null") != std::string::npos) {
		args.erase(args.begin());
	}
	else {
		rOfO = readBasicPosition(args);
	}
	return rOfO;
}

FColDsptr MbD::MBDynItem::readBasicPosition(std::vector<std::string>& args)
{
	return readVector3(args);
}

FMatDsptr MbD::MBDynItem::readOrientation(std::vector<std::string>& args)
{
	auto aAOf = FullMatrix<double>::identitysptr(3);
	if (args.empty()) return aAOf;
	auto str = args.at(0); //Must copy string
	if (str.find("reference") != std::string::npos) {
		args.erase(args.begin());
		auto refName = readStringNoSpacesOffTop(args);
		auto& ref = mbdynReferences()->at(refName);
		auto aAFf = readBasicOrientation(args);
		auto& aAOF = ref->aAFf;
		aAOf = aAOF->timesFullMatrix(aAFf);
	}
	else if (str.find("hinge") != std::string::npos) {
		args.erase(args.begin());
		aAOf = readOrientation(args);
	}
	else if (str.find("position") != std::string::npos) {
		if (str.find("orientation") != std::string::npos) {
			args.erase(args.begin());
			aAOf = readOrientation(args);
		}
	}
	else if (str.find("orientation") != std::string::npos) {
		args.erase(args.begin());
		aAOf = readOrientation(args);
	}
	else {
		aAOf = readBasicOrientation(args);
	}
	return aAOf;
}

FMatDsptr MbD::MBDynItem::readBasicOrientation(std::vector<std::string>& args)
{
	auto parser = std::make_shared<SymbolicParser>();
	parser->variables = mbdynVariables();
	auto str = args.at(0);	//Must copy string
	if (str.find("euler") != std::string::npos) {
		str = readStringNoSpacesOffTop(args);
		std::string substr = "euler";
		auto pos = str.find(substr);
		assert(pos != std::string::npos);
		str.erase(0, pos + substr.length());
		auto euler = EulerAngles<Symsptr>::With();
		if (str.length() == 0) {
			euler->rotOrder = std::make_shared<std::vector<size_t>>(std::initializer_list<size_t>{ 1, 2, 3 });
		}
		else {
			auto rotOrder = std::make_shared<std::vector<size_t>>(3);
			rotOrder->at(0) = str[0] - '0';
			rotOrder->at(1) = str[1] - '0';
			rotOrder->at(2) = str[2] - '0';
			euler->rotOrder = rotOrder;
		}
		for (size_t i = 0; i < 3; i++)
		{
			auto userFunc = std::make_shared<BasicUserFunction>(popOffTop(args), 1.0);
			parser->parseUserFunction(userFunc);
			auto& sym = parser->stack->top();
			euler->at(i) = sym->simplified();
		}
		euler->calc();
		auto& aAFf = euler->aA;
		return aAFf;
	}
	if (str.find("eye") != std::string::npos) {
		args.erase(args.begin());
		auto aAFf = FullMatrix<double>::identitysptr(3);
		return aAFf;
	}
	auto iss = std::istringstream(str);
	int integer;
	iss >> integer;
	if (integer == 1) {
		args.erase(args.begin());
		FColDsptr vecX, vecY, vecZ, vec;
		vecX = readPosition(args);
		vecX->normalizeSelf();
		auto axis = stoi(popOffTop(args));
		str = args.at(0);
		if (str.find("guess") != std::string::npos) {
			args.erase(args.begin());
			double min = std::numeric_limits<double>::max();
			double max = -1.0;
			size_t imin, imax;
			for (size_t i = 0; i < 3; i++)
			{
				auto mag = std::abs(vecX->at(i));
				if (mag > max) {
					imax = i;
					max = mag;
				}
				if (mag < min) {
					imin = i;
					min = mag;
				}
			}
			vec = std::make_shared<FullColumn<double>>(3);
			vec->at(imin) = 1.0;
			vec->at(imax) = -vecX->at(imin) / vecX->at(imax);
		}
		else {
			vec = readPosition(args);
		}
		vec->normalizeSelf();
		if (axis == 2) {
			vecZ = vecX->cross(vec);
			vecY = vecZ->cross(vecX);
		}
		else if (axis == 3) {
			vecY = vec->cross(vecX);
			vecZ = vecX->cross(vecY);
		}
		else {
			assert(false);
		}
		auto aAFf = FullMatrix<double>::identitysptr(3);
		aAFf->atandputFullColumn(0, 0, vecX);
		aAFf->atandputFullColumn(0, 1, vecY);
		aAFf->atandputFullColumn(0, 2, vecZ);
		return aAFf;
	}
	if (integer == 3) {
		args.erase(args.begin());
		FColDsptr vecX, vecY, vecZ, vec;
		vecZ = readPosition(args);
		vecZ->normalizeSelf();
		auto axis = stoi(popOffTop(args));
		str = args.at(0);
		if (str.find("guess") != std::string::npos) {
			args.erase(args.begin());
			double min = std::numeric_limits<double>::max();
			double max = -1.0;
			size_t imin, imax;
			for (size_t i = 0; i < 3; i++)
			{
				auto mag = std::abs(vecZ->at(i));
				if (mag > max) {
					imax = i;
					max = mag;
				}
				if (mag < min) {
					imin = i;
					min = mag;
				}
			}
			vec = std::make_shared<FullColumn<double>>(3);
			vec->at(imin) = 1.0;
			vec->at(imax) = -vecZ->at(imin) / vecZ->at(imax);
		}
		else {
			vec = readPosition(args);
		}
		vec->normalizeSelf();
		if (axis == 2) {
			vecX = vec->cross(vecZ);
			vecY = vecZ->cross(vecX);
		}
		else if (axis == 1) {
			vecY = vecZ->cross(vec);
			vecX = vecY->cross(vecZ);
		}
		else {
			assert(false);
		}
		auto aAFf = FullMatrix<double>::identitysptr(3);
		aAFf->atandputFullColumn(0, 0, vecX);
		aAFf->atandputFullColumn(0, 1, vecY);
		aAFf->atandputFullColumn(0, 2, vecZ);
		return aAFf;
	}
	auto aAFf = FullMatrix<double>::identitysptr(3);
	for (size_t i = 0; i < 3; i++)
	{
		auto& rowi = aAFf->at(i);
		for (size_t j = 0; j < 3; j++)
		{
			auto userFunc = std::make_shared<BasicUserFunction>(popOffTop(args), 1.0);
			parser->parseUserFunction(userFunc);
			auto& sym = parser->stack->top();
			rowi->at(j) = sym->getValue();
		}
	}
	return aAFf;
}

std::string MbD::MBDynItem::popOffTop(std::vector<std::string>& args)
{
	auto str = args.at(0);	//Must copy string
	args.erase(args.begin());
	return str;
}

std::string MbD::MBDynItem::readStringNoSpacesOffTop(std::vector<std::string>& args)
{
	//Return top string without whitespaces.
	std::string str = popOffTop(args);
	str.erase(std::remove_if(str.begin(), str.end(), isspace), str.end());
	return str;
}

std::string MbD::MBDynItem::stringOffTopHas(std::vector<std::string>& args, std::string token)
{
	return std::string();
}

FRowDsptr MbD::MBDynItem::readRowOfDoubles(std::string& line)
{
	return FRowDsptr();
}

FColDsptr MbD::MBDynItem::readColumnOfDoubles(std::string& line)
{
	return FColDsptr();
}

int MbD::MBDynItem::readIntOffTop(std::vector<std::string>& args)
{
	auto str = readStringNoSpacesOffTop(args);
	return readInt(str);
}

double MbD::MBDynItem::readDoubleOffTop(std::vector<std::string>& args)
{
	auto str = readStringNoSpacesOffTop(args);
	return readDouble(str);
}

double MbD::MBDynItem::readDouble(std::string& line)
{
	auto parser = std::make_shared<SymbolicParser>();
	parser->variables = mbdynVariables();
	auto userFunc = std::make_shared<BasicUserFunction>(line, 1.0);
	parser->parseUserFunction(userFunc);
	auto& sym = parser->stack->top();
	return sym->getValue();
}

size_t MbD::MBDynItem::readInt(std::string& line)
{
	std::istringstream iss(line);
	size_t i;
	iss >> i;
	return i;
}

bool MbD::MBDynItem::readBool(std::string& line)
{
	assert(false);
	return false;
}

std::string MbD::MBDynItem::asmtFormula(std::string mbdynFormula)
{
	auto ss = std::stringstream();
	std::string drivestr = "model::drive";
	size_t previousPos = 0;
	auto pos = mbdynFormula.find(drivestr);
	ss << mbdynFormula.substr(previousPos, pos - previousPos);
	while (pos != std::string::npos) {
		previousPos = pos;
		pos = mbdynFormula.find('(', pos + 1);
		previousPos = pos;
		pos = mbdynFormula.find(',', pos + 1);
		auto driveName = mbdynFormula.substr(previousPos + 1, pos - previousPos - 1);
		driveName = readToken(driveName);
		previousPos = pos;
		pos = mbdynFormula.find(')', pos + 1);
		auto varName = mbdynFormula.substr(previousPos + 1, pos - previousPos - 1);
		varName = readToken(varName);
		//Insert drive mbdynFormula
		ss << formulaFromDrive(driveName, varName);
		previousPos = pos;
		pos = mbdynFormula.find(drivestr, pos + 1);
		ss << mbdynFormula.substr(previousPos + 1, pos - previousPos);
	}
	return ss.str();
}

std::string MbD::MBDynItem::asmtFormulaIntegral(std::string mbdynFormula)
{
	auto ss = std::stringstream();
	ss << "integral(time, " << asmtFormula(mbdynFormula) << ")";
	return ss.str();
}

void MbD::MBDynItem::readLabel(std::vector<std::string>& args)
{
	label = readStringNoSpacesOffTop(args);
}

std::string MbD::MBDynItem::readJointTypeOffTop(std::vector<std::string>& args)
{
	auto ss = std::stringstream();
	auto iss = std::istringstream(popOffTop(args));
	std::string str;
	iss >> str;
	ss << str;
	while (!iss.eof()) {
		ss << ' ';
		iss >> str;
		ss << str;
	}
	return ss.str();
}

std::string MbD::MBDynItem::readToken(std::string& line)
{
	auto iss = std::istringstream(line);
	std::string str;
	iss >> str;
	return str;
}
