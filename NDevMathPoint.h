#pragma once

#include <math.h>

#include "NDevTypes.h"
#include "NDevDefinitions.h"
#include "NDevPoint.h"

namespace NDev
{
	using namespace Types;

	/* Vector @ Vector */

	template<FSize Size, typename Type>
	TPoint<Size, Type> operator-(const TPoint<Size, Type> &Lhs, const TPoint<Size, Type> &Rhs)
	{
		FSize Index, End;
		TPoint<Size, Type> Result;

		End = Size;
		for (Index = 0; Index < End; ++Index)
		{
			Result[Index] = Lhs[Index] - Rhs[Index];
		}
		return Result;
	}

	template<FSize Size, typename Type>
	TPoint<Size, Type> operator+(const TPoint<Size, Type> &Lhs, const TPoint<Size, Type> &Rhs)
	{
		FSize Index, End;
		TPoint<Size, Type> Result;

		End = Size;
		for (Index = 0; Index < End; ++Index)
		{
			Result[Index] = Lhs[Index] + Rhs[Index];
		}
		return Result;
	}

	template<FSize Size, typename Type>
	TPoint<Size, Type> operator*(const TPoint<Size, Type> &Lhs, const TPoint<Size, Type> &Rhs)
	{
		FSize Index, End;
		TPoint<Size, Type> Result;

		End = Size;
		for (Index = 0; Index < End; ++Index)
		{
			Result[Index] = Lhs[Index] * Rhs[Index];
		}
		return Result;
	}

	template<FSize Size, typename Type>
	TPoint<Size, Type> operator/(const TPoint<Size, Type> &Lhs, const TPoint<Size, Type> &Rhs)
	{
		FSize Index, End;
		TPoint<Size, Type> Result;

		End = Size;
		for (Index = 0; Index < End; ++Index)
		{
			Result[Index] = Lhs[Index] / Rhs[Index];
		}
		return Result;
	}

	template<FSize Size, typename Type>
	TPoint<Size, Type> operator^(const TPoint<Size, Type> &Lhs, const TPoint<Size, Type> &Rhs)
	{
		FSize Index, End;
		TPoint<Size, Type> Result;

		End = Size;
		for (Index = 0; Index < End; ++Index)
		{
			Result[Index] = pow(Lhs[Index], Rhs[Index]);
		}
		return Result;
	}


	/* Vector @= Vector */

	template<FSize Size, typename Type>
	TPoint<Size, Type> &operator+=(TPoint<Size, Type> &Lhs, const TPoint<Size, Type> &Rhs)
	{
		FSize Index, End;

		End = Size;
		for (Index = 0; Index < End; ++Index)
		{
			Lhs[Index] += Rhs[Index];
		}
		return Lhs;
	}

	template<FSize Size, typename Type>
	TPoint<Size, Type> &operator-=(TPoint<Size, Type> &Lhs, const TPoint<Size, Type> &Rhs)
	{
		FSize Index, End;

		End = Size;
		for (Index = 0; Index < End; ++Index)
		{
			Lhs[Index] -= Rhs[Index];
		}
		return Lhs;
	}

	template<FSize Size, typename Type>
	TPoint<Size, Type> &operator*=(TPoint<Size, Type> &Lhs, const TPoint<Size, Type> &Rhs)
	{
		FSize Index, End;

		End = Size;
		for (Index = 0; Index < End; ++Index)
		{
			Lhs[Index] *= Rhs[Index];
		}
		return Lhs;
	}

	template<FSize Size, typename Type>
	TPoint<Size, Type> &operator/=(TPoint<Size, Type> &Lhs, const TPoint<Size, Type> &Rhs)
	{
		FSize Index, End;

		End = Size;
		for (Index = 0; Index < End; ++Index)
		{
			Lhs[Index] /= Rhs[Index];
		}
		return Lhs;
	}

	template<FSize Size, typename Type>
	TPoint<Size, Type> &operator^=(TPoint<Size, Type> &Lhs, const TPoint<Size, Type> &Rhs)
	{
		FSize Index, End;

		End = Size;
		for (Index = 0; Index < End; ++Index)
		{
			Lhs[Index] = pow(Lhs[Index], Rhs[Index]);
		}
		return Lhs;
	}


	/* Alpha @ Vector */

	template<FSize Size, typename Type>
	TPoint<Size, Type> operator+(const Type &Lhs, const TPoint<Size, Type> &Rhs)
	{
		FSize Index, End;
		TPoint<Size, Type> Result;

		End = Size;
		for (Index = 0; Index < End; ++Index)
		{
			Result[Index] = Lhs + Rhs[Index];
		}
		return Result;
	}

	template<FSize Size, typename Type>
	TPoint<Size, Type> operator-(const Type &Lhs, const TPoint<Size, Type> &Rhs)
	{
		FSize Index, End;
		TPoint<Size, Type> Result;

		End = Size;
		for (Index = 0; Index < End; ++Index)
		{
			Result[Index] = Lhs - Rhs[Index];
		}
		return Result;
	}

	template<FSize Size, typename Type>
	TPoint<Size, Type> operator*(const Type &Lhs, const TPoint<Size, Type> &Rhs)
	{
		FSize Index, End;
		TPoint<Size, Type> Result;

		End = Size;
		for (Index = 0; Index < End; ++Index)
		{
			Result[Index] = Lhs * Rhs[Index];
		}
		return Result;
	}

	template<FSize Size, typename Type>
	TPoint<Size, Type> operator/(const Type &Lhs, const TPoint<Size, Type> &Rhs)
	{
		FSize Index, End;
		TPoint<Size, Type> Result;

		End = Size;
		for (Index = 0; Index < End; ++Index)
		{
			Result[Index] = Lhs / Rhs[Index];
		}
		return Result;
	}

	template<FSize Size, typename Type>
	TPoint<Size, Type> operator^(const Type &Lhs, const TPoint<Size, Type> &Rhs)
	{
		FSize Index, End;
		TPoint<Size, Type> Result;

		End = Size;
		for (Index = 0; Index < End; ++Index)
		{
			Result[Index] = pow(Lhs, Rhs[Index]);
		}
		return Result;
	}


	/* Vector @ Alpha */

	template<FSize Size, typename Type>
	TPoint<Size, Type> operator+(const TPoint<Size, Type> &Lhs, const Type &Rhs)
	{
		FSize Index, End;
		TPoint<Size, Type> Result;

		End = Size;
		for (Index = 0; Index < End; ++Index)
		{
			Result[Index] = Lhs[Index] + Rhs;
		}
		return Result;
	}

	template<FSize Size, typename Type>
	TPoint<Size, Type> operator-(const TPoint<Size, Type> &Lhs, const Type &Rhs)
	{
		FSize Index, End;
		TPoint<Size, Type> Result;

		End = Size;
		for (Index = 0; Index < End; ++Index)
		{
			Result[Index] = Lhs[Index] - Rhs;
		}
		return Result;
	}

	template<FSize Size, typename Type>
	TPoint<Size, Type> operator*(const TPoint<Size, Type> &Lhs, const Type &Rhs)
	{
		FSize Index, End;
		TPoint<Size, Type> Result;

		End = Size;
		for (Index = 0; Index < End; ++Index)
		{
			Result[Index] = Lhs[Index] * Rhs;
		}
		return Result;
	}

	template<FSize Size, typename Type>
	TPoint<Size, Type> operator/(const TPoint<Size, Type> &Lhs, const Type &Rhs)
	{
		FSize Index, End;
		TPoint<Size, Type> Result;

		End = Size;
		for (Index = 0; Index < End; ++Index)
		{
			Result[Index] = Lhs[Index] / Rhs;
		}
		return Result;
	}

	template<FSize Size, typename Type>
	TPoint<Size, Type> operator^(const TPoint<Size, Type> &Lhs, const Type &Rhs)
	{
		FSize Index, End;
		TPoint<Size, Type> Result;

		End = Size;
		for (Index = 0; Index < End; ++Index)
		{
			Result[Index] = pow(Lhs[Index], Rhs);
		}
		return Result;
	}

	/* Vector @= Alpha */

	template<FSize Size, typename Type>
	TPoint<Size, Type> &operator+=(TPoint<Size, Type> &Lhs, const Type &Rhs)
	{
		FSize Index, End;

		End = Size;
		for (Index = 0; Index < End; ++Index)
		{
			Lhs[Index] += Rhs;
		}
		return Lhs;
	}

	template<FSize Size, typename Type>
	TPoint<Size, Type> &operator-=(TPoint<Size, Type> &Lhs, const Type &Rhs)
	{
		FSize Index, End;

		End = Size;
		for (Index = 0; Index < End; ++Index)
		{
			Lhs[Index] -= Rhs;
		}
		return Lhs;
	}

	template<FSize Size, typename Type>
	TPoint<Size, Type> &operator*=(TPoint<Size, Type> &Lhs, const Type &Rhs)
	{
		FSize Index, End;

		End = Size;
		for (Index = 0; Index < End; ++Index)
		{
			Lhs[Index] *= Rhs;
		}
		return Lhs;
	}

	template<FSize Size, typename Type>
	TPoint<Size, Type> &operator/=(TPoint<Size, Type> &Lhs, const Type &Rhs)
	{
		FSize Index, End;

		End = Size;
		for (Index = 0; Index < End; ++Index)
		{
			Lhs[Index] /= Rhs;
		}
		return Lhs;
	}

	template<FSize Size, typename Type>
	TPoint<Size, Type> &operator^=(TPoint<Size, Type> &Lhs, const Type &Rhs)
	{
		FSize Index, End;

		End = Size;
		for (Index = 0; Index < End; ++Index)
		{
			Lhs[Index] = pow(Lhs[Index], Rhs);
		}
		return Lhs;
	}

	/* Function(Vector...) */

	template<FSize Size, typename Type>
	Type Sum(const TPoint<Size, Type> &Rhs)
	{
		FSize Index, End;
		Type Result = Type();

		End = Size;
		for (Index = 0; Index < End; ++Index)
		{
			Result += Rhs[Index];
		}
		return Result;
	}

	template<FSize Size, typename Type>
	Type Norm2(const TPoint<Size, Type> &Rhs, const Type &N)
	{
		FSize Index, End;
		Type Result = Type();

		End = Size;
		for (Index = 0; Index < End; ++Index)
		{
			Result += pow(Rhs[Index], N);
		}
		return Result;
	}

	template<FSize Size, typename Type>
	Type Norm2(const TPoint<Size, Type> &Rhs)
	{
		FSize Index, End;
		Type Result = Type();

		End = Size;
		for (Index = 0; Index < End; ++Index)
		{
			Result += Rhs[Index] * Rhs[Index];
		}
		return Result;
	}

	template<FSize Size, typename Type>
	Type Norm(const TPoint<Size, Type> &Rhs, const Type &N)
	{
		const Type ByN = 1 / N;

		return pow(Norm2(Rhs, N), ByN);
	}

	template<FSize Size, typename Type>
	Type Norm(const TPoint<Size, Type> &Rhs)
	{
		return sqrt(Norm2(Rhs));
	}

	template<FSize Size, typename Type>
	TPoint<Size, Type> &Normalize2(TPoint<Size, Type> &Rhs, const Type &N)
	{
		const FReal One = 1;
		FReal Alpha = One / Norm2(Rhs, N);
		Rhs *= Alpha;
		return Rhs;
	}

	template<FSize Size, typename Type>
	TPoint<Size, Type> &Normalize2(TPoint<Size, Type> &Rhs)
	{
		const FReal One = 1;
		FReal Alpha = One / Norm2(Rhs);
		Rhs *= Alpha;
		return Rhs;
	}

	template<FSize Size, typename Type>
	TPoint<Size, Type> &Normalize(TPoint<Size, Type> &Rhs, const Type &N)
	{
		const FReal One = 1;
		FReal Alpha = One / Norm(Rhs, N);
		Rhs *= Alpha;
		return  Rhs;
	}

	template<FSize Size, typename Type>
	TPoint<Size, Type> &Normalize(TPoint<Size, Type> &Rhs)
	{
		const FReal One = 1;
		FReal Alpha = One / Norm(Rhs);
		Rhs *= Alpha;
		return  Rhs;
	}

	template<FSize Size, typename Type>
	TPoint<Size, Type> Min(const TPoint<Size, Type> &Lhs, const TPoint<Size, Type> &Rhs)
	{
		FSize Index, End;
		TPoint<Size, Type> Result;

		End = Size;
		for (Index = 0; Index < End; ++Index)
		{
			Result[Index] = Min(Lhs[Index], Rhs[Index]);
		}
		return Result;
	}

	template<FSize Size, typename Type>
	FVoid MinInto(TPoint<Size, Type> &Lhs, const TPoint<Size, Type> &Rhs)
	{
		FSize Index, End;

		End = Size;
		for (Index = 0; Index < End; ++Index)
		{
			Lhs[Index] = Min(Lhs[Index], Rhs[Index]);
		}
	}

	template<FSize Size, typename Type>
	TPoint<Size, Type> Max(const TPoint<Size, Type> &Lhs, const TPoint<Size, Type> &Rhs)
	{
		FSize Index, End;
		TPoint<Size, Type> Result;

		End = Size;
		for (Index = 0; Index < End; ++Index)
		{
			Result[Index] = Max(Lhs[Index], Rhs[Index]);
		}
		return Result;
	}

	template<FSize Size, typename Type>
	FVoid MaxInto(TPoint<Size, Type> &Lhs, const TPoint<Size, Type> &Rhs)
	{
		FSize Index, End;

		End = Size;
		for (Index = 0; Index < End; ++Index)
		{
			Lhs[Index] = Max(Lhs[Index], Rhs[Index]);
		}
	}
	
	/*
	template<FSize Size, typename Type>
	TPoint<Size, Type> &IntoPoint(TPoint<Size, Type> &Lhs, const TQuinsor<Size, Type> &Rhs)
	{
		FSize Index, End;
		Type Scale, Theta;

	}

	template<FSize Size, typename Type>
	TQuinsor<Size, Type> &IntoQuinsor(TQuinsor<Size, Type> &Lhs, const TPoint<Size, Type> &Rhs)
	{
		FSize Index, End;
		Type Scale, Theta;
	}
	*/

}