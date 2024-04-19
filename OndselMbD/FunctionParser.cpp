#include "FunctionParser.h"
#include "ASMTAssembly.h"
#include "ASMTrIJ.h"
#include "ASMTAngleIJz.h"
#include "ASMTdAngleIJx.h"
#include "ASMTdAngleIJy.h"
#include "ASMTvIJ.h"
#include "ASMTvrIJ.h"
#include "ASMTOmegaIJ.h"

using namespace MbD;

std::shared_ptr<FunctionParser> MbD::FunctionParser::With()
{
	auto inst = std::make_shared<FunctionParser>();
	inst->initialize();
	return inst;
}

void MbD::FunctionParser::initgeoIJs()
{
	geoIJs = std::make_shared<std::map<std::string, std::shared_ptr<ASMTSymbolicFunctionIJ>>>();
	auto connectorList = container->root()->connectorList();
	std::shared_ptr<ASMTSymbolicFunctionIJ> funcIJ;
	for (auto& geoIJ : *connectorList) {
		funcIJ = ASMTSymbolicFunctionIJ::With();
		funcIJ->geoIJ = geoIJ;
		geoIJs->insert(std::make_pair(geoIJ->name, funcIJ));
		if (geoIJ.get() == container) {
			funcIJ = ASMTSymbolicFunctionIJ::With();
			funcIJ->geoIJ = geoIJ;
			geoIJs->insert(std::make_pair("self", funcIJ));
		}
	}
}

bool MbD::FunctionParser::geoIJ()
{
	if ((tokenType == "word") && (geoIJs->count(token) == 1)) {
		auto& var = geoIJs->at(token);
		stack->push(var);
		scanToken();
		return true;
	}
	return false;
}

bool MbD::FunctionParser::displacement()
{
	Symsptr symfunc = nullptr;
	if (peekForTypevalue("word", "rIJ")) {
		symfunc = std::make_shared<ASMTrIJ>();
	}
	else if (peekForTypevalue("word", "angleIJz")) {
		symfunc = std::make_shared<ASMTAngleIJz>();
	}
	else if (peekForTypevalue("word", "dAngleIJx")) {
		symfunc = std::make_shared<ASMTdAngleIJx>();
	}
	else if (peekForTypevalue("word", "dAngleIJy")) {
		symfunc = std::make_shared<ASMTdAngleIJy>();
	}
	if (symfunc != nullptr) {
		stack->push(symfunc);
		if (peekForTypeNoPush("(")) {
			auto startsize = stack->size();
			if (geoIJ()) {
				if (peekForTypeNoPush(")")) {
					auto itemIJ = std::static_pointer_cast<ASMTSymbolicFunctionIJ>(stack->top());
					stack->pop();
					auto funcIJ = std::static_pointer_cast<ASMTSymbolicFunctionIJ>(stack->top());
					funcIJ->geoIJ = itemIJ->geoIJ;
					return true;
				}
				expected(")");
			}
			expected("displacement");
		}
		expected("(");
	}
	return false;
}

bool MbD::FunctionParser::velocity()
{
	Symsptr symfunc = nullptr;
	if (peekForTypevalue("word", "vIJ")) {
		symfunc = std::make_shared<ASMTvIJ>();
	}
	else if (peekForTypevalue("word", "vrIJ")) {
		symfunc = std::make_shared<ASMTvrIJ>();
	}
	else if (peekForTypevalue("word", "omeIJ")) {
		symfunc = std::make_shared<ASMTOmegaIJ>();
	}
	if (symfunc != nullptr) {
		stack->push(symfunc);
		if (peekForTypeNoPush("(")) {
			auto startsize = stack->size();
			if (geoIJ()) {
				if (peekForTypeNoPush(")")) {
					auto itemIJ = std::static_pointer_cast<ASMTSymbolicFunctionIJ>(stack->top());
					stack->pop();
					auto funcIJ = std::static_pointer_cast<ASMTSymbolicFunctionIJ>(stack->top());
					funcIJ->geoIJ = itemIJ->geoIJ;
					return true;
				}
				expected(")");
			}
			expected("displacement");
		}
		expected("(");
	}
	return false;
}

bool MbD::FunctionParser::force()
{
	return false;
}

bool MbD::FunctionParser::namedFunction()
{
	return intrinsic() || displacement() || velocity() || force();
}
