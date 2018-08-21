#pragma once

#include <stdlib.h>
#include <inttypes.h>
#include <chrono>

namespace MLPrototyping
{
	using bool_t = bool;

	using char_t = char;

	using string_t = char *;

	using pointer_t = void *;

	using size_t = size_t;

	using real_t = float;

	using raw_t = uint8_t;

	using block_t = uint64_t;

	using byte_t = char;

	using integer_t = int;

	using enum_t = size_t;

	using clock_t = std::chrono::high_resolution_clock;

	using time_t = clock_t::time_point;
	
	using duration_t = clock_t::duration;

	using return_t = decltype(EXIT_SUCCESS);

	const size_t bytesize = 8;
	/*
	const decltype(nullptr) nullptr = nullptr;
	const decltype("") nullstr = "";
	const decltype('\0') nullchr = '\0';
	*/
	const decltype(nullptr) null = nullptr;
	const decltype(0) none = 0;
	const decltype(0) unknown = 0;
	const decltype(EXIT_SUCCESS) success = EXIT_SUCCESS;
	const decltype(EXIT_FAILURE) failure = EXIT_FAILURE;



}