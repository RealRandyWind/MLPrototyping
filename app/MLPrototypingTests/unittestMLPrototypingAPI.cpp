#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "MLPrototyping.h"

using namespace MLPrototyping;

namespace MLPrototypingTest
{		
	TEST_CLASS(UnitTestMLPrototypingAPI)
	{
	public:
		TEST_METHOD(GetAPI)
		{
			auto API = CMLPrototyping::Instance();
			Assert::IsNotNull(API, L"", LINE_INFO());
		}


	};



}