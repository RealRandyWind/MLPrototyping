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
		size_t _Size, _BufferSize, _ActiveIndex, _LastIndex;
		bool_t _bIterateAll, _bClearData;
		TypeData *_Data;

		TSequence()
		{
			_Size = _BufferSize = 0;
			_ActiveIndex = _LastIndex = 0;
			_bIterateAll = false;
			_bClearData = true;
			_Data = nullptr;
		}

		TSequence(size_t ReserveSize) : TSequence()
		{
			Reserve(ReserveSize);
		}

		~TSequence()
		{
			if (_bClearData && _Data)
			{
				free(_Data);
			}
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
			return Data[_ActiveIndex];
		}

		const TypeData & Active() const
		{
			return Data[_ActiveIndex];
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
			_LastIndex = Index;
			return _Data[Index];
		}

		const TypeData & operator[](size_t Index) const
		{
			_LastIndex = Index;
			return _Data[Index];
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