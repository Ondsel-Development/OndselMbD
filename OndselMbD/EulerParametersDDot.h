/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/
 
#pragma once

#include "EulerArray.h"
#include "EulerParametersDot.h"

namespace MbD {

	template<typename T>
	class EulerParametersDDot : public EulerArray<T>
	{
		//qEdot aAddot aBddot aCddot 
	public:
		EulerParametersDDot(size_t count) : EulerArray<T>(count) {}
		EulerParametersDDot(size_t count, const T& value) : EulerArray<T>(count, value) {}
		EulerParametersDDot(std::initializer_list<T> list) : EulerArray<T>{ list } {}
		static std::shared_ptr<EulerParametersDDot> With();

		//std::shared_ptr<EulerParametersDot<T>> qEdot;
		FMatDsptr aAddot, aBddot, aCddot;
	};

	template<typename T>
	inline std::shared_ptr<EulerParametersDDot<T>> EulerParametersDDot<T>::With()
	{
		assert(false);
		auto inst = std::make_shared<EulerParametersDDot<T>>();
		inst->initialize();
		return inst;
	}
}

