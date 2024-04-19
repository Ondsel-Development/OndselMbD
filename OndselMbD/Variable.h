/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include <string>

#include "Symbolic.h"

namespace MbD {
	class Variable : public Symbolic
	{
		//name value 
	public:
		Variable();
		Variable(const char* str);
		Variable(double val) : value(val) {}
		static std::shared_ptr<Variable> With(const char* str);
		void initialize() override;

		void setName(std::string str);
		const std::string& getName() const override;
		double getValue() override;
		void setValue(double val) override;
		Symsptr expandUntil(Symsptr sptr, std::shared_ptr<std::unordered_set<Symsptr>> set) override;
		Symsptr simplifyUntil(Symsptr sptr, std::shared_ptr<std::unordered_set<Symsptr>> set) override;
		bool isVariable() override;

		std::ostream& printOn(std::ostream& s) const override;

		std::string name;
		double value;
	};
}

