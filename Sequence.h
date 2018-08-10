#pragma once

#include "MLPrototyping_Types.h"
#include "MLPrototyping_Definitions.h"

namespace MLPrototyping
{
	template<typename TypeData>
	struct TSequence;

	template<typename TypeData>
	struct TSequence
	{
		size_t _Size, _BufferSize, _ActiveIndex, _LastIndex, _IncrementSize;
		bool_t _bIterateAll, _bClearDataOnDestroy, _bFixedSize, _bResizeOnAccess, _bSizeOnAccess, _bHeap;
		TypeData *_Data;

		TSequence()
		{
			_IncrementSize = 64;
			_Size = _BufferSize = 0;
			_ActiveIndex = _LastIndex = 0;
			_bIterateAll = false;
			_bClearDataOnDestroy = true;
			_bFixedSize = false;
			_bResizeOnAccess = true;
			_bSizeOnAccess = false;
			_Data = nullptr;
		}

		TSequence(size_t ReserveSize) : TSequence()
		{
			Reserve(ReserveSize);
		}

		~TSequence()
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

		void FixedSize(bool_t IsTrue = true)
		{
			_bFixedSize = IsTrue;
		}

		void ResizeOnAccess(bool_t IsTrue = true)
		{
			_bResizeOnAccess = IsTrue;
		}

		void SizeOnAccess(bool_t IsTrue = true)
		{
			_bSizeOnAccess = IsTrue;
		}

		void Add(TypeData Rhs)
		{
			bool_t bResize = !_bFixedSize && _Size >= _BufferSize;

			if (bResize)
			{
				Reserve(_BufferSize + _IncrementSize);
			}
			_Data[_Size] = Rhs;
			++_Size;
		}

		void Swap(TypeData Rhs)
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
			bool_t bResize = !_bFixedSize && _bResizeOnAccess && _BufferSize <= Index;
			bool_t bSize = _bSizeOnAccess && Index >= _Size;

			if (bResize) { Reserve(Index + _IncrementSize); }
			if (bSize) { _Size = Index + 1; }
			_LastIndex = Index;
			return _Data[Index];
		}

		const TypeData & operator[](size_t Index) const
		{
			return *this[Index];
		}

		void Reserve(size_t ReserveSize)
		{
			_Data = (TypeData *) realloc(_Data, ReserveSize * sizeof(TypeData));
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