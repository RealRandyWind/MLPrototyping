#pragma once

#include "MLPrototyping_Types.h"
#include "MLPrototyping_Definitions.h"
#include "Resource.h"

namespace MLPrototyping
{
	template<typename TypeData>
	struct TData : public CResource
	{
		size_t _Size, _BufferSize;
		bool_t _bIterateAll, _bClearDataOnDestroy, _bClearDataOnReplace, _bHeap;
		TypeData *_Data;

		TData()
		{
			_Size = _BufferSize = 0;
			_bIterateAll = false;
			_bClearDataOnDestroy = true;
			_bClearDataOnReplace = _bClearDataOnDestroy;
			_bHeap = true;
			_Data = nullptr;
		}

		TData(size_t ReserveSize, bool_t SetSizeToReserveSize = false) : TData()
		{
			Reserve(ReserveSize, SetSizeToReserveSize);
		}

		~TData()
		{
			if (_bHeap && _bClearDataOnDestroy && _Data)
			{
				free(_Data);
			}
			_Data = nullptr;
		}

		bool_t Empty()
		{
			return !_Size || !_Data;
		}

		const bool_t Empty() const
		{
			return !_Size || !_Data;
		}

		void_t IterateAll(bool_t IsTrue = true)
		{
			_bIterateAll = IsTrue;
		}

		void_t ClearDataOnDestroy(bool_t IsTrue = true)
		{
			_bClearDataOnDestroy = IsTrue;
		}

		void_t ClearDataOnReplace(bool_t IsTrue = true)
		{
			_bClearDataOnReplace = IsTrue;
		}

		size_t Size()
		{
			return _Size;
		}

		const size_t Size() const
		{
			return _Size;
		}

		size_t BufferSize()
		{
			return _BufferSize;
		}

		size_t SizeOf()
		{
			return sizeof(TypeData) * _Size;
		}

		const size_t SizeOf() const
		{
			return sizeof(TypeData) * _Size;
		}

		size_t BufferSizeOf()
		{
			return sizeof(TypeData) * _BufferSize;
		}

		const size_t BufferSizeOf() const
		{
			return sizeof(TypeData) * _BufferSize;
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
			return &_Data[0];
		}

		const TypeData * Data() const
		{
			return &_Data[0];
		}

		TypeData *Data(TypeData *Pointer, size_t SizeData, size_t SizeBuffer = 0, bool_t bHeap = true)
		{
			if (_bHeap && _bClearDataOnReplace && _Data) { free(_Data); _Data = nullptr; }
			if (SizeBuffer < SizeData) { SizeBuffer = SizeData; }
			_Size = SizeData;
			_BufferSize = SizeBuffer;
			_Data = Pointer;
			_bHeap = bHeap;
			return &_Data[0];
		}

		const FDescriptor Descriptor() const
		{
			FDescriptor _Descriptor;

			_Descriptor.Type = none;
			_Descriptor.SizeOf = sizeof(TypeData);
			_Descriptor.Size = _Size;
			_Descriptor._Size = _BufferSize;
			_Descriptor.N = 0;
			_Descriptor.bHeap = _bHeap;
			_Descriptor.Pointer = (pointer_t) &_Data[0];
			return _Descriptor;
		}

		TypeData & operator[](size_t Index)
		{
			return _Data[Index];
		}

		const TypeData & operator[](size_t Index) const
		{
			return _Data[Index];
		}

		void_t Reserve(size_t ReserveSize, bool_t SetSizeToReserveSize = false)
		{
			if (_bHeap)
			{
				_Data = nullptr;
				_bHeap = true;
				_bClearDataOnDestroy = true;
			}
			_Data = (TypeData *) realloc(_Data, ReserveSize * sizeof(TypeData));
			if (SetSizeToReserveSize) { _Size = ReserveSize; }
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