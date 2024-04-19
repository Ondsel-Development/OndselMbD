#include "MBDynRodJoint.h"

using namespace MbD;

std::shared_ptr<MBDynRodJoint> MbD::MBDynRodJoint::With()
{
	auto inst = std::make_shared<MBDynRodJoint>();
	inst->initialize();
	return inst;
}

void MbD::MBDynRodJoint::parseMBDyn(std::string line)
{
	jointString = line;
	arguments = collectArgumentsFor("joint", line);
	readLabel(arguments);
	readJointType(arguments);
	readMarkerI(arguments);
	readMarkerJ(arguments);
	readRodLength(arguments);
	readConstitutiveLaw(arguments);
}

void MbD::MBDynRodJoint::readMarkerI(std::vector<std::string>& args)
{
	mkr1 = std::make_shared<MBDynMarker>();
	mkr1->owner = this;
	mkr1->nodeStr = readStringOffTop(args);
	auto _nodeNames = nodeNames();
	mkr1->rPmP = readPosition(args);
	mkr1->aAPm = FullMatrix<double>::identitysptr(3);
}

void MbD::MBDynRodJoint::readMarkerJ(std::vector<std::string>& args)
{
	mkr2 = std::make_shared<MBDynMarker>();
	mkr2->owner = this;
	mkr2->nodeStr = readStringOffTop(args);
	auto _nodeNames = nodeNames();
	mkr2->rPmP = readPosition(args);
	mkr2->aAPm = FullMatrix<double>::identitysptr(3);
}

void MbD::MBDynRodJoint::readRodLength(std::vector<std::string>& args)
{
	if (lineHasTokens(3, args[0], "from", "nodes")) {
		popOffTop(args);
		auto rIJO = mkr2->rOmO()->minusFullColumn(mkr1->rOmO());
		rodLength = rIJO->length();
	}
	else {
		rodLength = readDoubleOffTop(args);
	}
}

void MbD::MBDynRodJoint::readConstitutiveLaw(std::vector<std::string>& args)
{
	if (lineHasTokens(3, args[0], "linear", "elastic")) {
		popOffTop(args);
		stiffness = readDoubleOffTop(args);
	}
	else {
		assert(false);
	}
}
