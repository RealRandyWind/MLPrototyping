#pragma once

#include "MLPrototyping_Types.h"
#include "MLPrototyping_Definitions.h"

namespace MLPrototyping
{
	template<typename TypeData>
	struct TData;

	template<typename TypeData>
	struct TData
	{
		size_t _Size, _BufferSize;
		bool_t _bIterateAll, _bClearData;
		TypeData *_Data;

		TData()
		{
			_Size = _BufferSize = 0;
			_bIterateAll = false;
			_bClearData = true;
			_Data = nullptr;
		}

		TData(size_t ReserveSize) : TData()
		{
			Reserve(ReserveSize);
		}

		~TData()
		{
			if (_bClearData && _Data)
			{
				free(_Data);
			}
		}

		size_t Size()
		{
			return _Size;
		}

		size_t BufferSize()
		{
			return _BufferSize;
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

			_Descriptor.Type = none;
			_Descriptor.SizeOf = sizeof(TypeData);
			_Descriptor.Size = _bIterateAll ? _BufferSize : _Size;
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

		void Reserve(size_t ReserveSize)
		{
			_Data = (TypeData *) realloc(_Data, ReserveSize * sizeof(TypeData));
			_BufferSize = ReserveSize;
			if (ReserveSize < _Size) { _Size = ReserveSize;  }
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
			return _bIterateAll ? &_Data[_BufferSize] : &_Data[_Size];
		}

		const TypeData * end() const
		{
			return _bIterateAll ? &_Data[_BufferSize] : &_Data[_Size];
		}


	};



}