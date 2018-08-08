// MLPrototyping.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "MLPrototyping.h"

using namespace MLPrototyping;

CMLPrototyping* CMLPrototyping::Instance = nullptr;

CMLPrototyping::CMLPrototyping()
{

}

CMLPrototyping::~CMLPrototyping()
{

}

CMLPrototyping* CMLPrototyping::GetInstance()
{
	if (!Instance) { Instance = new CMLPrototyping(); }
	return Instance;
}