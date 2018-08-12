#pragma once

#include "MLPrototyping_Types.h"
#include "MLPrototyping_Definitions.h"
#include "Point.h"
#include <math.h>
#include <limits.h>

namespace MLPrototyping
{
	template<typename Type>
	union TPoint1D
	{
		TPoint<1, Type> Point;
		struct { Type X; };
	};

	template<typename Type>
	union TPoint2D
	{
		TPoint<2, Type> Point;
		struct { Type X, Y; };
	};

	template<typename Type>
	union TPoint3D
	{
		TPoint<3, Type> Point;
		struct { Type X, Y, Z; };
	};

	template<typename Type>
	union TPoint4D
	{
		TPoint<4, Type> Point;
		struct { Type X, Y, Z, W; };
	};

	template<typename Type>
	union TPoint5D
	{
		TPoint<5, Type> Point;
		struct { Type X, Y, Z, W, T; };
	};

	template<typename Type>
	union TColor
	{
		TPoint<4, Type> Point;
		struct { Type R, G, B, A; };
	};

	template<typename Type>
	struct TLimit
	{
		static Type Upper()
		{
			return std::numeric_limits<Type>::max();
		}

		static Type Lower()
		{
			if (std::numeric_limits<Type>::is_bounded)
			{
				return std::numeric_limits<Type>::lowest();
			}
			return std::numeric_limits<Type>::min();
		}

		static Type Epsilon()
		{
			return std::numeric_limits<Type>::epsilon();
		}

		static Type Infinity()
		{
			if (!std::numeric_limits<Type>::has_infinity) { return Type(); }
			return std::numeric_limits<Type>::infinity();
		}

		static Type NaN()
		{
			if (!std::numeric_limits<Type>::has_quiet_NaN) { return Type(); }
			return std::numeric_limits<Type>::quiet_NaN();
		}
	};

	/* Vector @ Vector */

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

	template<size_t Size, typename Type>
	TPoint<Size, Type> operator+(const TPoint<Size, Type> &Lhs, const TPoint<Size, Type> &Rhs)
	{
		size_t Index, End;
		TPoint<Size, Type> Result;

		End = Size;
		for (Index = 0; Index < End; ++Index)
		{
			Result[Index] = Lhs[Index] + Rhs[Index];
		}
		return Result;
	}

	template<size_t Size, typename Type>
	TPoint<Size, Type> operator*(const TPoint<Size, Type> &Lhs, const TPoint<Size, Type> &Rhs)
	{
		size_t Index, End;
		TPoint<Size, Type> Result;

		End = Size;
		for (Index = 0; Index < End; ++Index)
		{
			Result[Index] = Lhs[Index] * Rhs[Index];
		}
		return Result;
	}

	template<size_t Size, typename Type>
	TPoint<Size, Type> operator/(const TPoint<Size, Type> &Lhs, const TPoint<Size, Type> &Rhs)
	{
		size_t Index, End;
		TPoint<Size, Type> Result;

		End = Size;
		for (Index = 0; Index < End; ++Index)
		{
			Result[Index] = Lhs[Index] / Rhs[Index];
		}
		return Result;
	}


	/* Vector @= Vector */

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

	template<size_t Size, typename Type>
	TPoint<Size, Type> &operator-=(TPoint<Size, Type> &Lhs, const TPoint<Size, Type> &Rhs)
	{
		size_t Index, End;

		End = Size;
		for (Index = 0; Index < End; ++Index)
		{
			Lhs[Index] -= Rhs[Index];
		}
		return Lhs;
	}

	template<size_t Size, typename Type>
	TPoint<Size, Type> &operator*=(TPoint<Size, Type> &Lhs, const TPoint<Size, Type> &Rhs)
	{
		size_t Index, End;

		End = Size;
		for (Index = 0; Index < End; ++Index)
		{
			Lhs[Index] *= Rhs[Index];
		}
		return Lhs;
	}

	template<size_t Size, typename Type>
	TPoint<Size, Type> &operator/=(TPoint<Size, Type> &Lhs, const TPoint<Size, Type> &Rhs)
	{
		size_t Index, End;

		End = Size;
		for (Index = 0; Index < End; ++Index)
		{
			Lhs[Index] /= Rhs[Index];
		}
		return Lhs;
	}


	/* Alpha @ Vector */

	template<size_t Size, typename Type>
	TPoint<Size, Type> operator+(const Type &Lhs, const TPoint<Size, Type> &Rhs)
	{
		size_t Index, End;
		TPoint<Size, Type> Result;

		End = Size;
		for (Index = 0; Index < End; ++Index)
		{
			Result[Index] = Lhs + Rhs[Index];
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
	TPoint<Size, Type> operator/(const Type &Lhs, const TPoint<Size, Type> &Rhs)
	{
		size_t Index, End;
		TPoint<Size, Type> Result;

		End = Size;
		for (Index = 0; Index < End; ++Index)
		{
			Result[Index] = Lhs / Rhs[Index];
		}
		return Result;
	}


	/* Vector @ Alpha */

	template<size_t Size, typename Type>
	TPoint<Size, Type> operator+(const TPoint<Size, Type> &Lhs, const Type &Rhs)
	{
		size_t Index, End;
		TPoint<Size, Type> Result;

		End = Size;
		for (Index = 0; Index < End; ++Index)
		{
			Result[Index] = Lhs[Index] + Rhs;
		}
		return Result;
	}

	template<size_t Size, typename Type>
	TPoint<Size, Type> operator-(const TPoint<Size, Type> &Lhs, const Type &Rhs)
	{
		size_t Index, End;
		TPoint<Size, Type> Result;

		End = Size;
		for (Index = 0; Index < End; ++Index)
		{
			Result[Index] = Lhs[Index] - Rhs;
		}
		return Result;
	}

	template<size_t Size, typename Type>
	TPoint<Size, Type> operator*(const TPoint<Size, Type> &Lhs, const Type &Rhs)
	{
		size_t Index, End;
		TPoint<Size, Type> Result;

		End = Size;
		for (Index = 0; Index < End; ++Index)
		{
			Result[Index] = Lhs[Index] * Rhs;
		}
		return Result;
	}

	template<size_t Size, typename Type>
	TPoint<Size, Type> operator/(const TPoint<Size, Type> &Lhs, const Type &Rhs)
	{
		size_t Index, End;
		TPoint<Size, Type> Result;

		End = Size;
		for (Index = 0; Index < End; ++Index)
		{
			Result[Index] = Lhs[Index] / Rhs;
		}
		return Result;
	}

	/* Vector @= Alpha */

	template<size_t Size, typename Type>
	TPoint<Size, Type> &operator+=(TPoint<Size, Type> &Lhs, const Type &Rhs)
	{
		size_t Index, End;

		End = Size;
		for (Index = 0; Index < End; ++Index)
		{
			Lhs[Index] += Rhs;
		}
		return Lhs;
	}

	template<size_t Size, typename Type>
	TPoint<Size, Type> &operator-=(TPoint<Size, Type> &Lhs, const Type &Rhs)
	{
		size_t Index, End;

		End = Size;
		for (Index = 0; Index < End; ++Index)
		{
			Lhs[Index] -= Rhs;
		}
		return Lhs;
	}

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

	template<size_t Size, typename Type>
	TPoint<Size, Type> &operator/=(TPoint<Size, Type> &Lhs, const Type &Rhs)
	{
		size_t Index, End;

		End = Size;
		for (Index = 0; Index < End; ++Index)
		{
			Lhs[Index] /= Rhs;
		}
		return Lhs;
	}

	/* Function(Vector...) */

	template<size_t Size, typename Type>
	Type Sum(const TPoint<Size, Type> &Rhs)
	{
		size_t Index, End;
		Type Result = Type();

		End = Size;
		for (Index = 0; Index < End; ++Index)
		{
			Result += Rhs[Index];
		}
		return Result;
	}

	template<size_t Size, typename Type>
	Type Norm2(const TPoint<Size, Type> &Rhs)
	{
		size_t Index, End;
		Type Result = Type();

		End = Size;
		for (Index = 0; Index < End; ++Index)
		{
			Result += Rhs[Index] * Rhs[Index];
		}
		return Result;
	}

	template<size_t Size, typename Type>
	Type Norm(const TPoint<Size, Type> &Rhs)
	{
		return sqrt(Norm2(Rhs));
	}

	template<size_t Size, typename Type>
	TPoint<Size, Type> &Normalize2(TPoint<Size, Type> &Rhs)
	{
		const real_t One = 1;
		real_t Alpha = One / Norm2(Rhs);
		Rhs *= Alpha;
		return Rhs;
	}

	template<size_t Size, typename Type>
	TPoint<Size, Type> & Normalize(TPoint<Size, Type> &Rhs)
	{
		const real_t One = 1;
		real_t Alpha = One / Norm(Rhs);
		Rhs *= Alpha;
		return  Rhs;
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



}