#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "NN.h"
#include "LVQ1.h"


using namespace MLPrototyping;
using namespace LVQ;

namespace MLPrototypingTest
{		
	TEST_CLASS(UnitTestMLPrototypingLVQ)
	{
	public:
		TEST_METHOD(TestNN)
		{
			Assert::Fail();
		}

		TEST_METHOD(TestLVQ1)
		{
			const real_t Alpha = 0.01;
			const size_t K = 3, N = 9;
			TLVQ1<3, 3> LVQ1;

			Assert::IsFalse(LVQ1.Initialized(), nullptr, LINE_INFO());
			LVQ1.Parameters.KNearest = K;
			LVQ1.Parameters.NPrototypes = N;
			LVQ1.Parameters.LearningRate = Alpha;
			LVQ1.Initialize();
			Assert::IsTrue(LVQ1.Initialized(), nullptr, LINE_INFO());
		}

		TEST_METHOD(TestSMDLVQ)
		{
			Assert::Fail();
		}

	};



}