#pragma once

#include "MLPrototyping_Types.h"
#include "MLPrototyping_Definitions.h"
#include "Point.h"
#include <math.h>
#include <limits.h>
#include <random>

namespace MLPrototyping
{
	template<size_t Size, typename Type>
	using TQuinsor = TPoint<Size, Type>;

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
		struct { Type C, M, Y, K; };
	};

	template<typename Type>
	struct TDistribution
	{
		Type &operator()(Type &Value) { Value = Next();  return Value; }

		template<size_t SizeLhs>
		TPoint<SizeLhs, Type> &operator()(TPoint<SizeLhs, Type> &Point)
		{
			for (auto &Value : Point) { Value = Next(); }
			return Point;
		}

		Type operator()() { return Next(); }

		template<size_t SizeLhs>
		TPoint<SizeLhs, Type> operator()()
		{
			TPoint<SizeLhs, Type> Point;

			for (auto &Value : Point) { Value = Next(); }
			return Point;
		}

		virtual void Seed(size_t SeedIn) = 0;

		virtual Type Next() = 0;

		virtual void Reset() = 0;
	};

	template<typename Type>
	struct TNormal : TDistribution<Type>
	{
		std::default_random_engine Generator;

		std::normal_distribution<Type> Distribution;

		TNormal()
		{
			Generator = std::default_random_engine();
			Distribution = std::normal_distribution<Type>();
		}

		~TNormal() { }

		void Parameters(Type Mean, Type SD)
		{
			Distribution.param(std::normal_distribution<Type>::param_type(Mean, SD));
		}

		virtual void Seed(size_t SeedIn) override
		{
			return Generator.seed(static_cast<unsigned int>(SeedIn));
		}

		virtual Type Next() override
		{
			return Distribution(Generator);
		}

		virtual void Reset() override
		{
			Distribution.reset();
		}
	};

	template<typename Type>
	struct TGamma : TDistribution<Type>
	{
		std::default_random_engine Generator;

		std::gamma_distribution<Type> Distribution;

		TGamma()
		{
			Generator = std::default_random_engine();
			Distribution = std::gamma_distribution<Type>();
		}

		~TGamma() { }

		void Parameters(Type Alpha, Type Beta)
		{
			Distribution.param(std::gamma_distribution<Type>::param_type(Alpha, Beta));
		}

		virtual void Seed(size_t SeedIn) override
		{
			return Generator.seed(static_cast<unsigned int>(SeedIn));
		}

		virtual Type Next() override
		{
			return Distribution(Generator);
		}

		virtual void Reset() override
		{
			Distribution.reset();
		}
	};

	template<typename Type>
	struct TUniform : TDistribution<Type>
	{
		std::default_random_engine Generator;

		std::uniform_real_distribution<Type> Distribution;

		TUniform()
		{
			Generator = std::default_random_engine();
			Distribution = std::uniform_real_distribution<Type>();
		}

		~TUniform() { }

		void Parameters(Type Lower, Type Upper)
		{
			Distribution.param(std::uniform_real_distribution<Type>::param_type(Lower, Upper));
		}

		virtual void Seed(size_t SeedIn) override
		{
			return Generator.seed(static_cast<unsigned int>(SeedIn));
		}

		virtual Type Next() override
		{
			return Distribution(Generator);
		}

		virtual void Reset() override
		{
			Distribution.reset();
		}
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
	void MinInto(TPoint<Size, Type> &Lhs, const TPoint<Size, Type> &Rhs)
	{
		size_t Index, End;

		End = Size;
		for (Index = 0; Index < End; ++Index)
		{
			Lhs[Index] = Min(Lhs[Index], Rhs[Index]);
		}
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

	template<size_t Size, typename Type>
	void MaxInto(TPoint<Size, Type> &Lhs, const TPoint<Size, Type> &Rhs)
	{
		size_t Index, End;

		End = Size;
		for (Index = 0; Index < End; ++Index)
		{
			Lhs[Index] = Max(Lhs[Index], Rhs[Index]);
		}
	}
	
	/*
	template<size_t Size, typename Type>
	TPoint<Size, Type> &IntoPoint(TPoint<Size, Type> &Lhs, const TQuinsor<Size, Type> &Rhs)
	{
		size_t Index, End;
		Type Scale, Theta;

	}

	template<size_t Size, typename Type>
	TQuinsor<Size, Type> &IntoQuinsor(TQuinsor<Size, Type> &Lhs, const TPoint<Size, Type> &Rhs)
	{
		size_t Index, End;
		Type Scale, Theta;
	}
	*/

}