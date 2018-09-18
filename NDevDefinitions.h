#pragma once

#include "NDevTypes.h"

namespace NDev
{
	using namespace Types;
	
	struct FDescriptor
	{
		FSize Type, SizeOf, Size, _Size, Stride, Offset, N;
		FBoolean bHeap;
		union
		{
			FPointer Pointer;
			FRaw *Raw;
			FByte *Bytes;
		};
	};

	/* Helper Functions */

	template<typename Type>
	Type Min(const Type &Lhs, const Type &Rhs)
	{
		return Lhs < Rhs ? Lhs : Rhs;
	}

	template<typename Type>
	Type Max(const Type &Lhs, const Type &Rhs)
	{
		return Lhs > Rhs ? Lhs : Rhs;
	}

	template<typename Type>
	Type &Swap(Type &Lhs, Type &Rhs)
	{
		Type Temp;

		Temp = Lhs;
		Lhs = Rhs;
		Rhs = Temp;
		return Rhs;
	}

	/* Pure Memory Functions */

	static void * _Make(FSize Bytes)
	{
		FPointer Pointer = malloc(Bytes);
		if (!Pointer) { exit(Failure); }
		return Pointer;
	}

	static void * _Swap2(void *From, void *To, FSize Bytes)
	{
		FSize Index, End;

		if (!From) { exit(Failure); }
		if (!To) { To = _Make(Bytes); }
		auto _From = (FRaw *)From;
		auto _To = (FRaw *)To;
		End = Bytes;
		for (Index = 0; Index < End; ++Index) { Swap(_From[Index], _To[Index]); }
		return _To;
	}

	static void * _Resize(void *Pointer, FSize Bytes)
	{
		FPointer _Pointer = realloc(Pointer, Bytes);
		if (!_Pointer) { exit(Failure); }
		Pointer = _Pointer;
		return Pointer;
	}

	static void * _Move(void *From, void *To, FSize Bytes)
	{
		FSize Index, End;

		if (!From) { exit(Failure); }
		if (!To) { To = _Make(Bytes); }
		auto _From = (FRaw *)From;
		auto _To = (FRaw *)To;
		End = Bytes;
		for (Index = 0; Index < End; ++Index) { _To[Index] = _From[Index]; _From[Index] = 0; }
		return _To;
	}

	static void * _Copy(const void *From, void *To, FSize Bytes)
	{
		FSize Index, End;

		if (!From) { exit(Failure); }
		if (!To) { To = _Make(Bytes); }
		auto _From = (const FRaw *)From;
		auto _To = (FRaw *)To;
		End = Bytes;
		for (Index = 0; Index < End; ++Index) { _To[Index] = _From[Index]; }
		return _To;
	}

	static void * _Remove(void *Pointer)
	{
		if (!Pointer) { return NullPtr; }
		free(Pointer);
		return NullPtr;
	}

	static void * _Text(const void *String)
	{
		FSize Size;

		if (!String) { exit(Failure); }
		auto _String = (FCharacter *)String;
		for (Size = 0; _String[Size]; ++Size) {}
		return _Copy(_String, NullPtr, Size);
	}

	/* Template Memory Functions */

	template<typename Type, typename TypeFrom>
	Type To(TypeFrom Value)
	{
		return static_cast<Type>(Value);
	}

	template<typename Type>
	Type DefaultValue(Type Value, Type Default)
	{
		return Value ? Type : Default;
	}

	template<typename Type>
	Type * Swap2(Type *From, Type *To, FSize Size = 1)
	{
		return (Type *)_Swap2(From, To, Size * sizeof(Type));
	}

	template<typename Type>
	Type * Make(FSize Size = 1)
	{
		return (Type *) _Make(Size * sizeof(Type));
	}

	template<typename Type>
	Type * Resize(Type *Pointer, FSize Size = 1)
	{
		return (Type *) _Resize(Pointer, Size * sizeof(Type));
	}

	template<typename Type>
	Type * Move(Type *From, Type *To, FSize Size = 1)
	{
		return (Type *) _Move(From, To, Size * sizeof(Type));
	}

	template<typename Type>
	Type * Copy(const Type *From, Type *To, FSize Size = 1)
	{
		return (Type *) _Copy(From, To, Size * sizeof(Type));
	}

	template<typename Type>
	Type * Remove(Type *Pointer)
	{
		return (Type *) _Remove(Pointer);
	}

	static FString Text(const char *String)
	{
		return (FString) _Text(String);
	}

	static FString Text(const FString String)
	{
		return (FString) _Text(String);
	}



}