#pragma once

#ifdef MLPROTOTYPING_EXPORTS
#define MLPrototyping_Exports __declspec(dllexport)
#else
#define MLPrototyping_Exports __declspec(dllimport)
#endif
