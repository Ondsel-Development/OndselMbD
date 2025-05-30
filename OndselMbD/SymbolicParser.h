/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include <stack>
#include <memory>
#include <sstream>
#include <set>

#include "Symbolic.h"
#include "ASMTItem.h"
#include "ASMTItemIJ.h"

namespace MbD {
	class SymbolicParser : public std::enable_shared_from_this<SymbolicParser>
	{
		//
	public:
		SymbolicParser();
		static std::shared_ptr<SymbolicParser> With();
		void initialize();

		void parseUserFunction(Symsptr userFunc);
		void parseString(std::string expr);
		bool commaExpression();
		bool plusTerm();
		bool minusTerm();
		bool plainTerm();
		bool term();
		bool plainFunction();
		bool timesFunction();
		bool divideByFunction();
		bool peekForTypeNoPush(std::string c);
		std::string scanToken();
		void xLetter();
		void xDigit();
		void xDoubleQuote();
		bool symfunction();
		bool expression();
		bool expressionInParentheses();
		bool constant();
		virtual bool namedFunction();
		bool intrinsic();
		bool variable();
		bool raisedTo();
		bool expected(std::string msg);
		bool signedNumber();
		bool peekForTypevalue(std::string type, std::string symbol);
		void notify(std::string msg) const;
		void notifyat(std::string msg, int mrk) const;
		void combineStackTo(size_t pos) const;
		bool isNextLineTag(char c) const;
		void initVariables();
		std::shared_ptr<std::set<Symbolic*>> variablesSet();

		ASMTItem* container = nullptr;
		std::shared_ptr<std::map<std::string, Symsptr>> variables;
		std::shared_ptr<Units> units;
		int mark = -1, prevEnd = -1;
		char hereChar = '\0';
		std::string token, tokenType;
		double tokenNum = -1.0e100;
		std::shared_ptr<std::istringstream> source;
		std::shared_ptr<std::stringstream> buffer;
		std::shared_ptr<std::stack<Symsptr>> stack;

	};
}

