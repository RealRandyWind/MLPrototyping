#include "pch.h"

#include "MLPrototyping.h"
#include "NN.h"

using namespace MLPrototyping;

FReturn main()
{
	using FNNF2L3 = LVQ::TNN<2, 3>;
	TData<FNNF2L3::FError> ErrorsNN;
	auto NN = FNNF2L3();

	return Success;
}