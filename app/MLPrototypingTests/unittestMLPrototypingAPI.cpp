#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "MLPrototyping.h";

using namespace MLPrototyping;

namespace MLPrototypingTest
{		
	TEST_CLASS(UnitTestMLPrototypingAPI)
	{
	public:
		TEST_METHOD(GetAPI)
		{
			auto API = CMLPrototyping::GetInstance();
			Assert::IsNotNull(API, L"", LINE_INFO());
		}

		TEST_METHOD(ModelDataNormal)
		{
			const size_t N0 = 0, NK = 32, NN = 2048;
			FNormalDataParameters Item;
			TSequence<FNormalDataParameters> List;
			TData<FNormalDataParameters::FPoint> Data;

			Item.Mean = 0;
			Item.N = NN;
			Item.SD = 1.5;
			Item.Norm = 1;

			auto API = CMLPrototyping::GetInstance();

			Assert::AreEqual(N0, Data.Size(), L"", LINE_INFO());
			API->ModelData(Data, Item);
			Assert::AreEqual(NN, Data.Size(), L"", LINE_INFO());

			List.Reserve(NK, true);
			for (auto &Parameters : List)
			{
				Parameters = Item;
			}
			API->ModelData(Data, List);
			Assert::AreEqual(NK * NN, Data.Size(), L"", LINE_INFO());
		}

		TEST_METHOD(ModelDataGamma)
		{
			const size_t N0 = 0, NK = 32, NN = 2048;
			FGammaDataParameters Item;
			TSequence<FGammaDataParameters> List;
			TData<FGammaDataParameters::FPoint> Data;

			Item.Mean = 0;
			Item.N = NN;
			Item.Alpha = 1.5;
			Item.Beta = 2.0;
			Item.Norm = 1;

			auto API = CMLPrototyping::GetInstance();

			Assert::AreEqual(N0, Data.Size(), L"", LINE_INFO());
			API->ModelData(Data, Item);
			Assert::AreEqual(NN, Data.Size(), L"", LINE_INFO());

			List.Reserve(NK, true);
			for (auto &Parameters : List)
			{
				Parameters = Item;
			}
			API->ModelData(Data, List);
			Assert::AreEqual(NK * NN, Data.Size(), L"", LINE_INFO());
		}


	};



}