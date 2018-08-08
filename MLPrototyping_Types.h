#pragma once

#include <inttypes.h>
#include <stdlib.h>


#define MLPrototyping_Macro_Expand(Args) Args
#define MLPrototyping_Macro_Concat(Left, Right) Left ## Right
#define MLPrototyping_Macro_Select(Name, Count) MLPrototyping_Macro_Concat( Name ## _, Count)
#define MLPrototyping_Macro_Size(_1, _2, _3, _4, _5, _6, _7, _8, _9, Count, ...) Count
#define MLPrototyping_Macro_Va_Size(...) MLPrototyping_Macro_Expand(MLPrototyping_Macro_Size(__VA_ARGS__, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0))
#define MLPrototyping_Macro_Va_Select(Name, ...) MLPrototyping_Macro_Expand(MLPrototyping_Macro_Select(Name, MLPrototyping_Macro_Va_Size(__VA_ARGS__))(__VA_ARGS__))

#define MLPrototyping_NullCode 1
#define MLPrototyping_NoneCode 1001
#define MLPrototyping_FaildCode 2001
#define MLPrototyping_InvalidCode 3001
#define MLPrototyping_ActionCode 4001
#define MLPrototyping_SpecialCode 5001
#define MLPrototyping_OtherCode 6001

namespace MLPrototyping
{
	using string_t = char *;
	using pointer_t = void *;
	using size_t = size_t;
	using real_t = float;
	using raw_t = uint8_t;
	using int_t = int;
	using enum_t = size_t;

	const size_t  = 8;
	const decltype("") nullstr = "";
	const decltype('\0') nullchr = '\0';
	const decltype(nullptr) null = nullptr;
	const decltype(EXIT_SUCCESS) success = EXIT_SUCCESS;
	const decltype(EXIT_FAILURE) failure = EXIT_FAILURE;
}