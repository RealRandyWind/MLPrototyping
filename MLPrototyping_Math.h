#pragma once

#include "MLPrototyping_Types.h"
#include "MLPrototyping_Definitions.h"
#include "Point.h"
#include <math.h>

namespace MLPrototyping
{
	template<typename Type>
	union TPoint1D
	{
		TPoint<1, Type> Point;
		struct { Type X };
	};

	template<typename Type>
	union TPoint2D
	{
		TPoint<2, Type> Point;
		struct { Type X, Y };
	};

	template<typename Type>
	union TPoint3D
	{
		TPoint<3, Type> Point;
		struct { Type X, Y, Z };
	};

	template<typename Type>
	union TPoint4D
	{
		TPoint<4, Type> Point;
		struct { Type X, Y, Z, W };
	};

	template<typename Type>
	union TPoint5D
	{
		TPoint<5, Type> Point;
		struct { Type X, Y, Z, W, T };
	};

	template<typename Type>
	union TColor
	{
		TPoint<4, Type> Point;
		struct { Type R, G, B, A };
	};

	template<size_t Size, typename Type>
	Type Norm2(const TPoint<Size, Type> &Rhs)
	{
		size_t Index, End;
		Type Result = Type();

		End = Size;
		for (Index = 0; Index < End; ++Index)
		{
			Result += Rhs.Data[Index] * Rhs.Data[Index];
		}
		return Result;
	}

	template<size_t Size, typename Type>
	Type Norm(const TPoint<Size, Type> &Rhs)
	{
		return sqrt(Norm2(Rhs));
	}

	template<size_t Size, typename Type>
	TPoint<Size, Type> Min(const TPoint<Size, Type> &Lhs, const TPoint<Size, Type> &Rhs)
	{
		size_t Index, End;
		TPoint<Size, Type> Result;

		End = Size;
		for (Index = 0; Index < End; ++Index)
		{
			Result[Index] = Min(Lhs[Index], Rhs[Index]);
		}
		return Result;
	}

	template<size_t Size, typename Type>
	TPoint<Size, Type> Max(const TPoint<Size, Type> &Lhs, const TPoint<Size, Type> &Rhs)
	{
		size_t Index, End;
		TPoint<Size, Type> Result;

		End = Size;
		for (Index = 0; Index < End; ++Index)
		{
			Result[Index] = Max(Lhs[Index], Rhs[Index]);
		}
		return Result;
	}


/*	Vector @ Vector */

	template<size_t Size, typename Type>
	TPoint<Size, Type> operator-(const TPoint<Size, Type> &Lhs, const TPoint<Size, Type> &Rhs)
	{
		size_t Index, End;
		TPoint<Size, Type> Result;

		End = Size;
		for (Index = 0; Index < End; ++Index)
		{
			Result[Index] = Lhs[Index] - Rhs[Index];
		}
		return Result;
	}


/*	Vector @= Vector */

	template<size_t Size, typename Type>
	TPoint<Size, Type> &operator+=(TPoint<Size, Type> &Lhs, const TPoint<Size, Type> &Rhs)
	{
		size_t Index, End;

		End = Size;
		for (Index = 0; Index < End; ++Index)
		{
			Lhs[Index] += Rhs[Index];
		}
		return Lhs;
	}


/*	Alpha @ Vector */

	template<size_t Size, typename Type>
	TPoint<Size, Type> operator*(const Type &Lhs, const TPoint<Size, Type> &Rhs)
	{
		size_t Index, End;
		TPoint<Size, Type> Result;

		End = Size;
		for (Index = 0; Index < End; ++Index)
		{
			Result[Index] = Lhs * Rhs[Index];
		}
		return Result;
	}

	template<size_t Size, typename Type>
	TPoint<Size, Type> operator-(const Type &Lhs, const TPoint<Size, Type> &Rhs)
	{
		size_t Index, End;
		TPoint<Size, Type> Result;

		End = Size;
		for (Index = 0; Index < End; ++Index)
		{
			Result[Index] = Lhs - Rhs[Index];
		}
		return Result;
	}


/*	Vector @ Alpha */

	template<size_t Size, typename Type>
	TPoint<Size, Type> operator*(const TPoint<Size, Type> &Lhs, const Type &Rhs)
	{
		size_t Index, End;
		TPoint<Size, Type> Result;

		End = Size;
		for (Index = 0; Index < End; ++Index)
		{
			Result[Index] = Rhs * Lhs[Index];
		}
		return Result;
	}

/*	Vector @= Alpha */

	template<size_t Size, typename Type>
	TPoint<Size, Type> &operator*=(TPoint<Size, Type> &Lhs, const Type &Rhs)
	{
		size_t Index, End;

		End = Size;
		for (Index = 0; Index < End; ++Index)
		{
			Lhs[Index] *= Rhs;
		}
		return Lhs;
	}



}