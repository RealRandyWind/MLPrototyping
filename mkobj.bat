@echo off
set Directory=%2
if not defined Directory set Directory=.\
echo.#include ^<%1^>> %Directory%%1.cpp
echo.#pragma once> %Directory%%1.hpp
echo.#include "%1.hpp"> %Directory%%1