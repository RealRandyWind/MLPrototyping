#pragma once

#include "MLPrototyping_Types.h"
#include "MLPrototyping_Definitions.h"

namespace MLPrototyping
{
	template<typename TypeData = real_t>
	struct TData;

	template<typename TypeData = real_t>
	struct TData
	{
		size_t _Size, _SizeBuffer;
		bool_t _bIterateAll;
		TypeData *_Data;


		size_t Size()
		{
			return _Size;
		}

		size_t Buffer()
		{
			return _SizeBuffer;
		}

		TypeData * Data()
		{
			return &_Data[0];
		}

		const TypeData * Data() const
		{
			return &_Data[0];
		}

		FDescriptor Descriptor()
		{
			FDescriptor _Descriptor;

			_Descriptor.SizeOf = sizeof(TypeData);
			_Descriptor.Size = _bIterateAll ? _SizeBuffer : _Size;
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

		void Reserve(size_t NewSize)
		{
			_Data = (TypeData *) realloc(_Data, NewSize * sizeof(TypeData));
			_SizeBuffer = NewSize;
			if (NewSize < _Size) { _Size = NewSize;  }
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
			return _bIterateAll ? &_Data[_SizeBuffer] : &_Data[_Size];
		}

		const TypeData * end() const
		{
			return _bIterateAll ? &_Data[_SizeBuffer] : &_Data[_Size];
		}


	};



}