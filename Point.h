#pragma once

#include "MLPrototyping_Types.h"
#include "MLPrototyping_Definitions.h"

namespace MLPrototyping
{
	template<size_t SizeData, typename TypeData = real_t>
	struct TPoint;

	template<size_t SizeData, typename TypeData = real_t>
	struct TPoint
	{
		TypeData _Data[SizeData];

		size_t Size()
		{
			return SizeData;
		}

		TypeData * Data()
		{
			return &_Data[SizeData];
		}

		const TypeData * Data() const
		{
			return &_Data[SizeData];
		}

		FDescriptor Descriptor()
		{
			FDescriptor _Descriptor;

			_Descriptor.SizeOf = sizeof(TypeData);
			_Descriptor.Size = SizeData;
			_Descriptor.bHeap = true;
			_Descriptor.Pointer = (pointer_t) &_Data[0];
			return _Descriptor;
		}

		const FDescriptor Descriptor() const
		{
			return Descriptor();
		}

		TypeData & operator[](size_t Index)
		{
			return _Data[Index];
		}

		const TypeData & operator[](size_t Index) const
		{
			return _Data[Index];
		}

		TypeData * begin()
		{
			return &_Data[0];
		}

		const TypeData * begin() const
		{
			return &_Data[0];
		}

		TypeData * end()
		{
			return &_Data[SizeData];
		}

		const TypeData * end() const
		{
			return &_Data[SizeData];
		}

		template<size_t SizeLhs, typename TypeLhs>
		operator TPoint<SizeLhs, TypeLhs>()
		{
			TPoint<SizeLhs, TypeLhs> Lhs;
			size_t Index, End;

			End = SizeData;
			for (Index = 0; Index < End; ++Index)
			{
				Lhs._Data[Index] = static_cast<TypeLhs>(_Data[Index]);
			}
			return Lhs;
		}



	};
}