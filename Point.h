#pragma once

#include "MLPrototyping_Types.h"
#include "MLPrototyping_Definitions.h"

namespace MLPrototyping
{
	template<FSize SizeData, typename TypeData>
	struct TPoint
	{
		TypeData _Data[SizeData];

		FSize Size()
		{
			return SizeData;
		}

		const FSize Size() const
		{
			return SizeData;
		}

		FSize SizeOf()
		{
			return sizeof(TypeData) * SizeData;
		}

		const FSize SizeOf() const
		{
			return sizeof(TypeData) * SizeData;
		}

		FByte * Bytes()
		{
			return (FByte *) &_Data[0];
		}

		const FByte * Bytes() const
		{
			return (FByte *) &_Data[0];
		}

		TypeData * Data()
		{
			return &_Data[SizeData];
		}

		const TypeData * Data() const
		{
			return &_Data[SizeData];
		}

		const FDescriptor Descriptor() const
		{
			FDescriptor _Descriptor;

			_Descriptor.Type = None;
			_Descriptor.SizeOf = sizeof(TypeData);
			_Descriptor.Size = SizeData;
			_Descriptor._Size = SizeData;
			_Descriptor.N = 0;
			_Descriptor.bHeap = False;
			_Descriptor.Pointer = (FPointer) &_Data[0];
			return _Descriptor;
		}

		TypeData & operator[](FSize Index)
		{
			return _Data[Index];
		}

		const TypeData & operator[](FSize Index) const
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

		template<FSize SizeLhs, typename TypeLhs>
		operator TPoint<SizeLhs, TypeLhs>()
		{
			TPoint<SizeLhs, TypeLhs> Lhs;
			FSize Index, End;

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
			FSize Index, End;

			End = SizeData;
			for (Index = 0; Index < End; ++Index)
			{
				_Data[Index] = static_cast<TypeData>(Rhs);
			}
			return *this;
		}

		template<FSize SizeRhs, typename TypRhs>
		TPoint<SizeData, TypeData> & operator=(const TPoint<SizeRhs, TypRhs> &Rhs)
		{
			FSize Index, End;

			End = Min(SizeData, SizeRhs);
			for (Index = 0; Index < End; ++Index)
			{
				_Data[Index] = static_cast<TypeData>(Rhs._Data[Index]);
			}
			return *this;
		}
	};



}