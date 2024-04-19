#include "MBDynStructuralDummy.h"
#include "MBDynReference.h"

using namespace MbD;

std::shared_ptr<MBDynStructuralDummy> MbD::MBDynStructuralDummy::With()
{
	auto inst = std::make_shared<MBDynStructuralDummy>();
	inst->initialize();
	return inst;
}

void MbD::MBDynStructuralDummy::parseMBDyn(std::string line)
{
	strucString = line;
	arguments = collectArgumentsFor("structural", line);
	readLabel(arguments);
	auto nodeType = readStringOffTop(arguments);
	assert(nodeType == "dummy");
	baseNodeName = readStringOffTop(arguments);
	auto offsetStr = readStringOffTop(arguments);
	assert(offsetStr == "offset");
	readPosition(arguments);
	readOrientation(arguments);
}

void MbD::MBDynStructuralDummy::readPosition(std::vector<std::string>& args)
{
	rOfO = std::make_shared<FullColumn<double>>(3);
	if (args.empty()) return;
	if (args[0].find("reference") != std::string::npos) {
		args.erase(args.begin());
		baseRefName = readStringOffTop(args);
		auto& ref = mbdynReferences()->at(baseRefName);
		auto rFfF = readBasicPosition(args);
		auto& rOFO = ref->rFfF;
		auto& aAOF = ref->aAFf;
		rOfO = rOFO->plusFullColumn(aAOF->timesFullColumn(rFfF));
	}
	else if (args[0].find("null") != std::string::npos) {
		args.erase(args.begin());
	}
	else {
		rOfO = readBasicPosition(args);
	}
}

void MbD::MBDynStructuralDummy::readOrientation(std::vector<std::string>& args)
{
	aAOf = FullMatrix<double>::identitysptr(3);
	if (args.empty()) return;
	if (args[0].find("reference") != std::string::npos) {
		args.erase(args.begin());
		assert(baseRefName == readStringOffTop(args));
		auto& ref = mbdynReferences()->at(baseRefName);
		auto aAFf = readBasicOrientation(args);
		auto& aAOF = ref->aAFf;
		aAOf = aAOF->timesFullMatrix(aAFf);
	}
	else if (args[0].find("position") != std::string::npos) {
		if (args[0].find("orientation") != std::string::npos) {
			args.erase(args.begin());
			aAOf = readBasicOrientation(args);
		}
	}
	else if (args[0].find("orientation") != std::string::npos) {
		args.erase(args.begin());
		if (args[0].find("reference") != std::string::npos) {
			args.erase(args.begin());
			assert(baseRefName == readStringOffTop(args));
			aAOf = readBasicOrientation(args);
		}
	}
	else {
		aAOf = readBasicOrientation(args);
	}
}
