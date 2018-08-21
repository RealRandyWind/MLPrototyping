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

		TEST_METHOD(ModelDataNormal)
		{
			const size_t N0 = 0, NK = 32, NN = 2048;
			FNormalDataParameters Item;
			TSequence<FNormalDataParameters> List;
			TData<FNormalDataParameters::FFeature> Data;
			TData<FNormalDataParameters::FSample> SData;

			Item = FNormalDataParameters::Default();
			Item.N = NN;

			auto API = CMLPrototyping::Instance();

			API->ModelData(Data, Item);
			Assert::AreEqual(NN, Data.Size(), L"", LINE_INFO());
			API->ModelData(SData, Item);
			Assert::AreEqual(NN, SData.Size(), L"", LINE_INFO());

			List.Reserve(NK, true);
			for (auto &Parameters : List)
			{
				Parameters = Item;
			}
			API->ModelData(Data, List);
			Assert::AreEqual(NK * NN, Data.Size(), L"", LINE_INFO());
			API->ModelData(SData, List);
			Assert::AreEqual(NK * NN, SData.Size(), L"", LINE_INFO());
		}

		TEST_METHOD(ModelDataGamma)
		{
			const size_t N0 = 0, NK = 32, NN = 2048;
			FGammaDataParameters Item;
			TSequence<FGammaDataParameters> List;
			TData<FGammaDataParameters::FFeature> Data;
			TData<FGammaDataParameters::FSample> SData;

			Item = FGammaDataParameters::Default();
			Item.N = NN;

			auto API = CMLPrototyping::Instance();

			API->ModelData(Data, Item);
			Assert::AreEqual(NN, Data.Size(), L"", LINE_INFO());
			API->ModelData(SData, Item);
			Assert::AreEqual(NN, SData.Size(), L"", LINE_INFO());

			List.Reserve(NK, true);
			for (auto &Parameters : List)
			{
				Parameters = Item;
			}
			API->ModelData(Data, List);
			Assert::AreEqual(NK * NN, Data.Size(), L"", LINE_INFO());
			API->ModelData(SData, List);
			Assert::AreEqual(NK * NN, SData.Size(), L"", LINE_INFO());
		}


		TEST_METHOD(ModelDataRing)
		{
			const size_t N0 = 0, NK = 32, NN = 2048;
			FRingDataParameters Item;
			TSequence<FRingDataParameters> List;
			TData<FRingDataParameters::FFeature> Data;
			TData<FRingDataParameters::FSample> SData;

			Item = FRingDataParameters::Default();
			Item.N = NN;

			auto API = CMLPrototyping::Instance();

			API->ModelData(Data, Item);
			Assert::AreEqual(NN, Data.Size(), L"", LINE_INFO());
			API->ModelData(SData, Item);
			Assert::AreEqual(NN, SData.Size(), L"", LINE_INFO());

			List.Reserve(NK, true);
			for (auto &Parameters : List)
			{
				Parameters = Item;
			}
			API->ModelData(Data, List);
			Assert::AreEqual(NK * NN, Data.Size(), L"", LINE_INFO());
			API->ModelData(SData, List);
			Assert::AreEqual(NK * NN, SData.Size(), L"", LINE_INFO());
		}

	};



}