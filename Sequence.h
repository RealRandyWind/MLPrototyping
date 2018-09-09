#pragma once

#include "MLPrototyping_Types.h"
#include "MLPrototyping_Definitions.h"

namespace MLPrototyping
{
	template<typename TypeData>
	struct TSequence
	{
		size_t _Size, _BufferSize, _ActiveIndex, _LastIndex, _IncrementSize;
		bool_t _bIterateAll, _bClearDataOnDestroy, _bClearDataOnReplace, _bFixedSize, _bResizeOnAccess, _bSizeOnAccess, _bHeap;
		TypeData *_Data;

		TSequence()
		{
			_IncrementSize = 64;
			_Size = _BufferSize = 0;
			_ActiveIndex = _LastIndex = 0;
			_bIterateAll = false;
			_bClearDataOnDestroy = true;
			_bClearDataOnReplace = _bClearDataOnDestroy;
			_bFixedSize = false;
			_bResizeOnAccess = true;
			_bSizeOnAccess = false;
			_bHeap = true;
			_Data = nullptr;
		}

		TSequence(size_t ReserveSize, bool_t bSetSizeToReserveSize = false) : TSequence()
		{
			Reserve(ReserveSize, bSetSizeToReserveSize);
		}

		~TSequence()
		{
			bool_t bFree = _bHeap && _bClearDataOnDestroy && _Data;

			if (bFree) { free(_Data); }
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

		void_t FixedSize(bool_t IsTrue = true)
		{
			_bFixedSize = IsTrue;
		}

		void_t ResizeOnAccess(bool_t IsTrue = true)
		{
			_bResizeOnAccess = IsTrue;
		}

		void_t SizeOnAccess(bool_t IsTrue = true)
		{
			_bSizeOnAccess = IsTrue;
		}
		
		void_t Reset()
		{
			_Size = _ActiveIndex = _LastIndex = 0;
		}

		void_t Add(TypeData Rhs)
		{
			bool_t bResize = !_bFixedSize && _Size >= _BufferSize;

			if (bResize) { Reserve(_Size + _IncrementSize); }
			_Data[_Size] = Rhs;
			++_Size;
		}

		void_t Swap(TypeData Rhs)
		{
			if (_Size < _BufferSize)
			{
				++_Size;
			}

			++_ActiveIndex;
			if (_ActiveIndex >= _BufferSize)
			{
				_ActiveIndex = 0;
			}

			_Data[_ActiveIndex] = Rhs;
		}

		TypeData & Active()
		{
			return _Data[_ActiveIndex];
		}

		const TypeData & Active() const
		{
			return _Data[_ActiveIndex];
		}

		TypeData & Last()
		{
			return _Data[_LastIndex];
		}

		const TypeData & Last() const
		{
			return _Data[_LastIndex];
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

		const size_t BufferSize() const
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
			bool_t bFree = _bHeap && _bClearDataOnReplace && _Data;

			if (bFree) { free(_Data); }
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
			_Descriptor.bHeap = _bHeap;
			_Descriptor.Pointer = (pointer_t)&_Data[0];
			return _Descriptor;
		}

		TypeData & operator[](size_t Index)
		{
			bool_t bResize = !_bFixedSize && _bResizeOnAccess && _BufferSize <= Index;
			bool_t bSize = _bSizeOnAccess && Index >= _Size;

			if (bResize) { Reserve(Index + _IncrementSize); }
			if (bSize) { _Size = Index + 1; }
			_LastIndex = Index;
			return _Data[Index];
		}

		const TypeData & operator[](size_t Index) const
		{
			if (Index >= _Size) { exit(failure); }
			return _Data[Index];
		}

		void_t Reserve(size_t ReserveSize, bool_t bSetSizeToReserveSize = false)
		{
			if (_bHeap)
			{
				_bHeap = true;
				_bClearDataOnDestroy = true;
			}
			_Data = (TypeData *) realloc(_Data, ReserveSize * sizeof(TypeData));
			if (bSetSizeToReserveSize) { _Size = ReserveSize; }
			_BufferSize = ReserveSize;
			if (ReserveSize < _Size) { _Size = ReserveSize; }
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