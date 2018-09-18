#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "MLPrototyping.h"
#include "NDev.h"

using namespace MLPrototyping;

namespace MLPrototypingTest
{
	using namespace NDev::Types;

	TEST_CLASS(UnitTestMLPrototypingAPI)
	{
	public:
		TEST_METHOD(GetAPI)
		{
			auto API = CMLPrototyping::Instance();
			Assert::IsNotNull(API, NullPtr , LINE_INFO());
		}


	};



}