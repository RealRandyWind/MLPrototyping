// MLPrototyping.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "MLPrototyping.h"
#include "MLPrototyping_Math.h"


using namespace MLPrototyping;

CMLPrototyping* CMLPrototyping::_Instance = nullptr;

CMLPrototyping::CMLPrototyping()
{

}

CMLPrototyping::~CMLPrototyping()
{
	
}

CMLPrototyping* CMLPrototyping::Instance()
{
	if (!_Instance) { _Instance = new CMLPrototyping(); }
	return _Instance;
}
