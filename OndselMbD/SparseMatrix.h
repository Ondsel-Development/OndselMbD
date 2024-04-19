/***************************************************************************
 *   Copyright (c) 2023 Ondsel, Inc.                                       *
 *                                                                         *
 *   This file is part of OndselSolver.                                    *
 *                                                                         *
 *   See LICENSE file for details about copyright.                         *
 ***************************************************************************/

#pragma once

#include <fstream>	
#include <sstream> 
#include <iomanip>

#include "RowTypeMatrix.h"
#include "SparseRow.h"
#include "DiagonalMatrix.h"
#include "FullMatrix.h"

namespace MbD {
	template<typename T>
	class SparseMatrix;
	template<typename T>
	using SpMatsptr = std::shared_ptr<SparseMatrix<T>>;
	using SpMatDsptr = std::shared_ptr<SparseMatrix<double>>;

	template<typename T>
	class SparseMatrix : public RowTypeMatrix<SpRowsptr<T>>
	{
	public:
		SparseMatrix(size_t m) : RowTypeMatrix<SpRowsptr<T>>(m)
		{
		}
		SparseMatrix(size_t m, size_t n) {
			for (size_t i = 0; i < m; i++)
			{
				auto row = std::make_shared<SparseRow<T>>(n);
				this->push_back(row);
			}
		}
		SparseMatrix(std::initializer_list<std::initializer_list<std::initializer_list<double>>> list2D) {
			for (auto& rowList : list2D)
			{
				auto row = std::make_shared<SparseRow<T>>(rowList);
				this->push_back(row);
			}
		}
		static SpMatDsptr colTimesRowTimesScalar(FColDsptr col, SpRowDsptr row, double a);
		void atput(size_t i, SpRowsptr<T> spRow);
		void atandplusDiagonalMatrix(size_t i, size_t j, DiagMatDsptr diagMat);
		void atandminusDiagonalMatrix(size_t i, size_t j, DiagMatDsptr diagMat);
		double sumOfSquares() override;
		void zeroSelf() override;
		void atandplusFullRow(size_t i, size_t j, FRowsptr<T> fullRow);
		void atandplusFullColumn(size_t i, size_t j, FColsptr<T> fullCol);
		void atandplusFullMatrix(size_t i, size_t j, FMatDsptr fullMat);
		void atandminusFullMatrix(size_t i, size_t j, FMatDsptr fullMat);
		void atandplusTransposeFullMatrix(size_t i, size_t j, FMatDsptr fullMat);
		void atandplusFullMatrixtimes(size_t i, size_t j, FMatDsptr fullMat, T factor);
		void atandminusFullColumn(size_t i, size_t j, FColDsptr fullCol);
		void atandminusTransposeFullMatrix(size_t i, size_t j, FMatDsptr fullMat);
		void atandplusNumber(size_t i, size_t j, double value);
		void atandminusNumber(size_t i, size_t j, double value);
		void atandput(size_t i, size_t j, T value);
		double maxMagnitude() override;
		FColsptr<T> timesFullColumn(FColsptr<T> fullCol);
		SpMatsptr<T> plusSparseMatrix(SpMatsptr<T> spMat);
		std::shared_ptr<SparseMatrix<T>> clonesptr();
		void magnifySelf(T factor);

		std::ostream& printOn(std::ostream& s) const override;

	};

	template<typename T>
	inline SpMatDsptr SparseMatrix<T>::colTimesRowTimesScalar(FColDsptr col, SpRowDsptr row, double a)
	{
		//"a*b*scalar = a(i)b(j)*scalar"

		auto nrow = col->size();
		auto answer = std::make_shared<SparseMatrix<double>>(nrow);
		for (size_t i = 0; i < nrow; i++) {
			answer->atput(i, row->times(a * col->at(i)));
		}
		return answer;
	}

	template<typename T>
	inline void SparseMatrix<T>::atput(size_t i, SpRowsptr<T> spRow)
	{
		this->at(i) = spRow;
	}

	template<typename T>
	inline void SparseMatrix<T>::atandplusDiagonalMatrix(size_t i, size_t j, DiagMatDsptr diagMat)
	{
		auto n = diagMat->nrow();
		for (size_t ii = 0; ii < n; ii++)
		{
			this->atandplusNumber(i + ii, j + ii, diagMat->at(ii));
		}
	}

	template<>
	inline void SparseMatrix<double>::atandminusDiagonalMatrix(size_t i1, size_t j1, DiagMatDsptr diagMat)
	{
		auto n = diagMat->nrow();
		for (size_t ii = 0; ii < n; ii++)
		{
			this->atandminusNumber(i1 + ii, j1 + ii, diagMat->at(ii));
		}
	}

	template<typename T>
	inline double SparseMatrix<T>::sumOfSquares()
	{
		double sum = 0.0;
		for (size_t i = 0; i < this->size(); i++)
		{
			sum += this->at(i)->sumOfSquares();
		}
		return sum;
	}

	template<>
	inline void SparseMatrix<double>::zeroSelf()
	{
		for (size_t i = 0; i < this->size(); i++) {
			this->at(i)->zeroSelf();
		}
	}

	template<typename T>
	inline void SparseMatrix<T>::atandplusFullRow(size_t i, size_t j, FRowsptr<T> fullRow)
	{
		this->at(i)->atplusFullRow(j, fullRow);
	}

	template<typename T>
	inline void SparseMatrix<T>::atandplusFullColumn(size_t i, size_t j, FColsptr<T> fullCol)
	{
		for (size_t ii = 0; ii < fullCol->size(); ii++)
		{
			this->atandplusNumber(i + ii, j, fullCol->at(ii));
		}
	}

	template<typename T>
	inline void SparseMatrix<T>::atandminusFullColumn(size_t i, size_t j, FColDsptr fullCol)
	{
		for (size_t ii = 0; ii < fullCol->size(); ii++)
		{
			this->atandminusNumber(i + ii, j, fullCol->at(ii));
		}
	}

	template<typename T>
	inline void SparseMatrix<T>::atandplusFullMatrix(size_t i, size_t j, FMatDsptr fullMat)
	{
		for (size_t ii = 0; ii < fullMat->nrow(); ii++)
		{
			this->at(i + ii)->atplusFullRow(j, fullMat->at(ii));
		}
	}

	template<typename T>
	inline void SparseMatrix<T>::atandminusFullMatrix(size_t i, size_t j, FMatDsptr fullMat)
	{
		for (size_t ii = 0; ii < fullMat->nrow(); ii++)
		{
			this->at(i + ii)->atminusFullRow(j, fullMat->at(ii));
		}
	}

	template<typename T>
	inline void SparseMatrix<T>::atandplusTransposeFullMatrix(size_t i, size_t j, FMatDsptr fullMat)
	{
		for (size_t ii = 0; ii < fullMat->nrow(); ii++)
		{
			this->atandplusFullColumn(i, j + ii, fullMat->at(ii)->transpose());
		}
	}

	template<typename T>
	inline void SparseMatrix<T>::atandminusTransposeFullMatrix(size_t i, size_t j, FMatDsptr fullMat)
	{
		for (size_t ii = 0; ii < fullMat->nrow(); ii++)
		{
			this->atandminusFullColumn(i, j + ii, fullMat->at(ii)->transpose());
		}
	}

	template<typename T>
	inline void SparseMatrix<T>::atandplusFullMatrixtimes(size_t i, size_t j, FMatDsptr fullMat, T factor)
	{
		for (size_t ii = 0; ii < fullMat->nrow(); ii++)
		{
			this->at(i + ii)->atplusFullRowtimes(j, fullMat->at(ii), factor);
		}
	}

	template<typename T>
	inline void SparseMatrix<T>::atandplusNumber(size_t i, size_t j, double value)
	{
		this->at(i)->atplusNumber(j, value);
	}

	template<typename T>
	inline void SparseMatrix<T>::atandminusNumber(size_t i, size_t j, double value)
	{
		this->at(i)->atminusNumber(j, value);
	}

	template<typename T>
	inline void SparseMatrix<T>::atandput(size_t i, size_t j, T value)
	{
		this->at(i)->atput(j, value);
	}

	template<typename T>
	inline double SparseMatrix<T>::maxMagnitude()
	{
		double max = 0.0;
		for (size_t i = 0; i < this->size(); i++)
		{
			double element = this->at(i)->maxMagnitude();
			if (max < element) max = element;
		}
		return max;
	}

	template<typename T>
	inline std::ostream& SparseMatrix<T>::printOn(std::ostream& s) const
	{
		s << "SpMat[" << std::endl;
		for (size_t i = 0; i < this->size(); i++)
		{
			s << *(this->at(i)) << std::endl;
		}
		s << "]" << std::endl;
		return s;
	}

	template<typename T>
	inline FColsptr<T> SparseMatrix<T>::timesFullColumn(FColsptr<T> fullCol)
	{
		//"a*b = a(i,j)b(j) sum j."
		auto nrow = this->nrow();
		auto answer = std::make_shared<FullColumn<T>>(nrow);
		for (size_t i = 0; i < nrow; i++)
		{
			answer->at(i) = this->at(i)->timesFullColumn(fullCol);
		}
		return answer;
	}

	template<typename T>
	inline SpMatsptr<T> SparseMatrix<T>::plusSparseMatrix(SpMatsptr<T> spMat)
	{
		//"a + b."
		//"Assume all checking of validity of this operation has been done."
		//"Just evaluate quickly."

		auto answer = clonesptr();
		for (size_t i = 0; i < answer->size(); i++)
		{
			answer->atput(i, answer->at(i)->plusSparseRow(spMat->at(i)));
		}
		return answer;
	}

	template<typename T>
	inline std::shared_ptr<SparseMatrix<T>> SparseMatrix<T>::clonesptr()
	{
		return std::make_shared<SparseMatrix<T>>(*this);
	}

	template<typename T>
	inline void SparseMatrix<T>::magnifySelf(T factor)
	{
		for (size_t i = 0; i < this->size(); i++) {
			this->at(i)->magnifySelf(factor);
		}
	}
}