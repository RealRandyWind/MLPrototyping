#pragma once

#include "MLPrototyping_Types.h"

namespace MLPrototyping
{
	struct FDescriptor
	{
		size_t Type, SizeOf, Size;
		bool_t bHeap;
		pointer_t Pointer;
	};

	template<typename Type>
	Type Min(const Type &Lhs, const Type &Rhs)
	{
		return Lhs < Rhs ? Lhs : Rhs;
	}

	template<typename Type>
	Type Max(const Type &Lhs, const Type &Rhs)
	{
		return Lhs > Rhs ? Lhs : Rhs;
	}

	template<typename Type>
	Type & Swap(Type &Lhs, Type &Rhs)
	{
		Type Temp;

		Temp = Lhs;
		Lhs = Rhs;
		Rhs = Temp;
		return Rhs;
	}



}