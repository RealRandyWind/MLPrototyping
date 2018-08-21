#pragma once

#include "MLPrototyping_Types.h"
#include "MLPrototyping_Definitions.h"

namespace MLPrototyping
{
	template<size_t SizeData, typename TypeData>
	struct TPoint
	{
		TypeData _Data[SizeData];

		size_t Size()
		{
			return SizeData;
		}

		const size_t Size() const
		{
			return SizeData;
		}

		size_t SizeOf()
		{
			return sizeof(TypeData) * SizeData;
		}

		const size_t SizeOf() const
		{
			return sizeof(TypeData) * SizeData;
		}

		byte_t * Bytes()
		{
			return (byte_t *) &_Data[0];
		}

		const byte_t * Bytes() const
		{
			return (byte_t *) &_Data[0];
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

			_Descriptor.Type = none;
			_Descriptor.SizeOf = sizeof(TypeData);
			_Descriptor.Size = SizeData;
			_Descriptor._Size = SizeData;
			_Descriptor.N = 0;
			_Descriptor.bHeap = false;
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

			End = Min(SizeData, SizeLhs);
			for (Index = 0; Index < End; ++Index)
			{
				Lhs._Data[Index] = static_cast<TypeLhs>(_Data[Index]);
			}
			End = SizeLhs;
			for (; Index < End; ++Index)
			{
				Lhs._Data[Index] = TypeLhs();
			}
			return Lhs;
		}

		template<typename TypeRhs>
		TPoint<SizeData, TypeData> & operator=(const TypeRhs &Rhs)
		{
			size_t Index, End;

			End = SizeData;
			for (Index = 0; Index < End; ++Index)
			{
				_Data[Index] = static_cast<TypeData>(Rhs);
			}
			return *this;
		}

		template<size_t SizeRhs, typename TypRhs>
		TPoint<SizeData, TypeData> & operator=(const TPoint<SizeRhs, TypRhs> &Rhs)
		{
			size_t Index, End;

			End = Min(SizeData, SizeRhs);
			for (Index = 0; Index < End; ++Index)
			{
				_Data[Index] = static_cast<TypeData>(Rhs._Data[Index]);
			}
			return *this;
		}
	};



}