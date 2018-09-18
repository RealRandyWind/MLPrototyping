// MLPrototyping.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "MLPrototyping.h"

#include "NDev.h"


using namespace MLPrototyping;

using namespace NDev;
using namespace NDev::Types;

CMLPrototyping* CMLPrototyping::_Instance = NullPtr;

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
