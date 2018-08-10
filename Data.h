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
		bool_t _bIterateAll, _bClearDataOnDestroy, _bHeap;
		TypeData *_Data;

		TData()
		{
			_Size = _BufferSize = 0;
			_bIterateAll = false;
			_bClearDataOnDestroy = true;
			_bHeap = true;
			_Data = nullptr;
		}

		TData(size_t ReserveSize) : TData()
		{
			Reserve(ReserveSize);
		}

		~TData()
		{
			if (_bClearDataOnDestroy && _Data)
			{
				free(_Data);
			}
		}

		bool_t Empty()
		{
			return !_Size || !_Data;
		}

		void IterateAll(bool_t IsTrue = true)
		{
			_bIterateAll = IsTrue;
		}

		void ClearDataOnDestroy(bool_t IsTrue = true)
		{
			_bClearDataOnDestroy = IsTrue;
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

		TypeData *Data(TypeData *Pointer, size_t SizeData, size_t SizeBuffer = 0, bool_t bHeap = true)
		{
			if (SizeBuffer < SizeData) { SizeBuffer = SizeData; }
			_Size = SizeData;
			_BufferSize = SizeBuffer;
			_Data = Pointer;
			_bHeap = bHeap;
			return &_Data[0];
		}

		const TypeData *Data(TypeData *Pointer, size_t SizeData, size_t SizeBuffer = 0, bool_t bHeap = true) const
		{
			return Data(Pointer, SizeData, SizeBuffer, bHeap);
		}

		FDescriptor Descriptor()
		{
			FDescriptor _Descriptor;

			_Descriptor.Type = none;
			_Descriptor.SizeOf = sizeof(TypeData);
			_Descriptor.Size = _Size;
			_Descriptor._Size = _BufferSize;
			_Descriptor.bHeap = _bHeap;
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