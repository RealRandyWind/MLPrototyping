#pragma once

#include "NDevTypes.h"
#include "NDevPoint.h"
#include <random>

namespace NDev
{
    using namespace Types;

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
}
