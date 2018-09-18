#pragma once

#include <stdlib.h>
#include <inttypes.h>
#include <chrono>

namespace MLPrototyping
{
	using FVoid = void;

	using FBoolean = bool;

	using FCharacter = char;

	using FString = char *;

	using FPointer = void *;

	using FSize = size_t;

	using FReal = double;

	using FRaw = uint8_t;

	using FBlock = uint64_t;

	using FByte = char;

	using FInteger = int;

	using FEnum = size_t;

	using FClock = std::chrono::high_resolution_clock;

	using FTime = FClock::time_point;
	
	using FDuration = FClock::duration;

	using FReturn = decltype(EXIT_SUCCESS);

	static const FSize ByteSize = 8;
	
	static const decltype("") Nullstr = "";
	static const decltype('\0') Nullchr = '\0';
	static const decltype(nullptr) NullPtr = nullptr;
	static const decltype(nullptr) Null = nullptr;
	static const decltype(true) True = true;
	static const decltype(false) False = false;
	static const decltype(0) None = 0;
	static const decltype(0) Unknown = 0;
	static const decltype(EXIT_SUCCESS) Success = EXIT_SUCCESS;
	static const decltype(EXIT_FAILURE) Failure = EXIT_FAILURE;



}