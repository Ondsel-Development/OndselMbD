/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#include <cassert>
 
#include "Variable.h"

using namespace MbD;

Variable::Variable()
{
	value = 0.0;
}

Variable::Variable(const char* str) : name(str) 
{
	value = 0.0;
}

std::shared_ptr<Variable> MbD::Variable::With(const char* str)
{
	auto inst = std::make_shared<Variable>(str);
	inst->initialize();
	return inst;
}

void Variable::initialize()
{
	assert(false);
}

void Variable::setName(std::string str)
{
	name = str;
}

const std::string& Variable::getName() const
{
	return name;
}

double Variable::getValue()
{
	return value;
}

std::ostream& Variable::printOn(std::ostream& s) const
{
	return s << name;
}

void Variable::setValue(double val)
{
	value = val;
}

Symsptr MbD::Variable::expandUntil(Symsptr sptr, std::shared_ptr<std::unordered_set<Symsptr>>)
{
	return sptr;
}

Symsptr MbD::Variable::simplifyUntil(Symsptr sptr, std::shared_ptr<std::unordered_set<Symsptr>>)
{
	return sptr;
}

bool MbD::Variable::isVariable()
{
	return true;
}
