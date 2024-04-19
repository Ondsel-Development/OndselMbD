#include "EigenDecomposition.h"

using namespace MbD;

std::shared_ptr<EigenDecomposition> MbD::EigenDecomposition::With()
{
	auto inst = std::make_shared<EigenDecomposition>();
	inst->initialize();
	return inst;
}

FColDsptr MbD::EigenDecomposition::basicSolvewithsaveOriginal(FMatDsptr fullMat, FColDsptr fullCol, bool saveOriginal)
{
	assert(false);
	return FColDsptr();
}

FColDsptr MbD::EigenDecomposition::basicSolvewithsaveOriginal(SpMatDsptr spMat, FColDsptr fullCol, bool saveOriginal)
{
	assert(false);
	return FColDsptr();
}

void MbD::EigenDecomposition::preSolvewithsaveOriginal(FMatDsptr fullMat, FColDsptr fullCol, bool saveOriginal)
{
	assert(false);
}

void MbD::EigenDecomposition::preSolvewithsaveOriginal(SpMatDsptr spMat, FColDsptr fullCol, bool saveOriginal)
{
	assert(false);
}

void MbD::EigenDecomposition::doPivoting(size_t p)
{
	assert(false);
}

void MbD::EigenDecomposition::forwardEliminateWithPivot(size_t p)
{
	assert(false);
}

void MbD::EigenDecomposition::backSubstituteIntoDU()
{
	assert(false);
}

void MbD::EigenDecomposition::postSolve()
{
	assert(false);
}

double MbD::EigenDecomposition::getmatrixArowimaxMagnitude(size_t i)
{
	assert(false);
	return 0.0;
}
