#include "MBDynNode.h"
#include "ASMTPart.h"
#include "EulerAngles.h"

using namespace MbD;

std::shared_ptr<MBDynNode> MbD::MBDynNode::With()
{
	auto inst = std::make_shared<MBDynNode>();
	inst->initialize();
	return inst;
}

void MbD::MBDynNode::initialize()
{
	//Do nothing.
}

void MbD::MBDynNode::parseMBDyn(std::vector<std::string>&)
{
	assert(false);
}

void MbD::MBDynNode::outputLine(size_t i, std::ostream& os)
{
	auto id = labelIDat(label);
	auto asmtPart = std::static_pointer_cast<ASMTPart>(asmtItem);
	auto x = asmtPart->xs->at(i);
	auto y = asmtPart->ys->at(i);
	auto z = asmtPart->zs->at(i);
	auto aA = asmtPart->getRotationMatrix(i);
	auto vx = asmtPart->vxs->at(i);
	auto vy = asmtPart->vys->at(i);
	auto vz = asmtPart->vzs->at(i);
	auto omex = asmtPart->omexs->at(i);
	auto omey = asmtPart->omeys->at(i);
	auto omez = asmtPart->omezs->at(i);
	os << id << " ";
	os << x << " " << y << " " << z << " ";
	auto row = aA->at(0);
	os << row->at(0) << " " << row->at(1) << " " << row->at(2) << " ";
	row = aA->at(1);
	os << row->at(0) << " " << row->at(1) << " " << row->at(2) << " ";
	row = aA->at(2);
	os << row->at(0) << " " << row->at(1) << " " << row->at(2) << " ";
	os << vx << " " << vy << " " << vz << " ";
	os << omex << " " << omey << " " << omez << " ";
	os << std::endl;
}
