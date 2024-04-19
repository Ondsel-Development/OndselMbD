/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "FullColumn.h"
#include "FullRow.h"
#include "FullMatrix.h"
#include "DiagonalMatrix.h"
#include "SparseMatrix.h"
#include "enum.h"

namespace MbD {
	class ASMTAssembly;
	class Units;
	class ASMTSpatialContainer;
	class ASMTPart;
	class System;
	class Constant;
	class Item;

	class ASMTItem : public std::enable_shared_from_this<ASMTItem>
	{
		//
	public:
		ASMTItem() {}
		//virtual ~ASMTItem() {}
		static std::shared_ptr<ASMTItem> With();
		virtual void initialize();
		virtual void initializeGlobally();
		virtual void initializeLocally();

		virtual ASMTAssembly* root();
		virtual ASMTSpatialContainer* partOrAssembly();
		virtual ASMTPart* part();

		void noop();
		virtual std::string classname();
		void setName(std::string str);
		virtual void parseASMT(std::vector<std::string>& lines);
		std::string popOffTop(std::vector<std::string>& args);
		std::string readStringOffTop(std::vector<std::string>& args);
		FRowDsptr readRowOfDoubles(std::string& line);
		FColDsptr readColumnOfDoubles(std::string& line);
		double readDouble(std::string& line);
		int readInt(std::string& line);
		size_t readSize_t(std::string& line);
		bool readBool(std::string& line);
		std::string readString(std::string& line);
		void readName(std::vector<std::string>& lines);
		virtual std::string fullName(std::string partialName);
		void readDoublesInto(std::string& str, std::string label, FRowDsptr& row);
		virtual void deleteMbD();
		virtual void createMbD(std::shared_ptr<System> mbdSys, std::shared_ptr<Units> mbdUnits);
		virtual void updateFromMbD();
		virtual void compareResults(AnalysisType type);
		virtual void outputResults(AnalysisType type);
		std::shared_ptr<Units> mbdUnits();
		std::shared_ptr<Constant> sptrConstant(double value);
		virtual void storeOnLevel(std::ofstream& os, size_t level);
		virtual void storeOnLevelTabs(std::ofstream& os, size_t level);
		virtual void storeOnLevelString(std::ofstream& os, size_t level, std::string str);
		virtual void storeOnLevelDouble(std::ofstream& os, size_t level, double value);
		virtual void storeOnLevelInt(std::ofstream& os, size_t level, int i);
		virtual void storeOnLevelSize_t(std::ofstream& os, size_t level, size_t i);
		virtual void storeOnLevelBool(std::ofstream& os, size_t level, bool value);
		//template<typename T>
		//void storeOnLevelArray(std::ofstream& os, size_t level, std::vector<T> array);
		void storeOnLevelArray(std::ofstream& os, size_t level, std::vector<double> array);
		void storeOnLevelName(std::ofstream& os, size_t level);
		virtual void storeOnTimeSeries(std::ofstream& os);
		void logString(std::string& str);
		void logString(const char* chars);

		std::string name;
		ASMTItem* owner = nullptr;
		std::shared_ptr<Item> mbdObject;
	};
}

