
#include "ASMTInPlaneJoint.h"
#include "InPlaneJoint.h"
#include "Units.h"

using namespace MbD;

std::shared_ptr<ASMTInPlaneJoint> MbD::ASMTInPlaneJoint::With()
{
	auto inst = std::make_shared<ASMTInPlaneJoint>();
	inst->initialize();
	return inst;
}

void MbD::ASMTInPlaneJoint::parseASMT(std::vector<std::string>& lines)
{
	ASMTJoint::parseASMT(lines);
	readOffset(lines);
}

void MbD::ASMTInPlaneJoint::readOffset(std::vector<std::string>& lines)
{
	if (lines[0].find("offset") == std::string::npos) {
		offset = 0.0;
	}
	else {
		lines.erase(lines.begin());
		offset = readDouble(lines[0]);
		lines.erase(lines.begin());
	}
}

void MbD::ASMTInPlaneJoint::createMbD()
{
	ASMTJoint::createMbD();
	auto inPlaneJoint = std::static_pointer_cast<InPlaneJoint>(mbdObject);
	inPlaneJoint->offset = offset * asmtUnits()->length;
}

void MbD::ASMTInPlaneJoint::storeOnLevel(std::ofstream& os, size_t level)
{
	ASMTJoint::storeOnLevel(os, level);
	storeOnLevelString(os, level + 1, "offset");
	storeOnLevelDouble(os, level + 2, offset);
}
