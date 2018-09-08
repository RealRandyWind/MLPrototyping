#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "MLPrototyping.h"
#include "MLPrototyping_Generate.h"

using namespace MLPrototyping;

namespace MLPrototypingTest
{		
	TEST_CLASS(UnitTestMLPrototypingGenerate)
	{
	public:
		TEST_METHOD(ModelDataNormal)
		{
			const size_t N0 = 0, NK = 32, NN = 2048;

			using FNormalDataParameters = TNormalDataParameters<3, 3>;
			FNormalDataParameters Item;
			TSequence<FNormalDataParameters> List;
			TData<FNormalDataParameters::FFeature> Data;
			TData<FNormalDataParameters::FSample> SData;

			Item = FNormalDataParameters::Default();
			Item.N = NN;

			auto API = CMLPrototyping::Instance();

			ModelData(Data, Item);
			Assert::AreEqual(NN, Data.Size(), L"", LINE_INFO());
			ModelData(SData, Item);
			Assert::AreEqual(NN, SData.Size(), L"", LINE_INFO());

			List.Reserve(NK, true);
			for (auto &Parameters : List)
			{
				Parameters = Item;
			}
			ModelData(Data, List);
			Assert::AreEqual(NK * NN, Data.Size(), L"", LINE_INFO());
			ModelData(SData, List);
			Assert::AreEqual(NK * NN, SData.Size(), L"", LINE_INFO());
		}

		TEST_METHOD(ModelDataGamma)
		{
			const size_t N0 = 0, NK = 32, NN = 2048;
			using FGammaDataParameters = TGammaDataParameters<3, 3>;
			FGammaDataParameters Item;
			TSequence<FGammaDataParameters> List;
			TData<FGammaDataParameters::FFeature> Data;
			TData<FGammaDataParameters::FSample> SData;

			Item = FGammaDataParameters::Default();
			Item.N = NN;

			auto API = CMLPrototyping::Instance();

			ModelData(Data, Item);
			Assert::AreEqual(NN, Data.Size(), L"", LINE_INFO());
			ModelData(SData, Item);
			Assert::AreEqual(NN, SData.Size(), L"", LINE_INFO());

			List.Reserve(NK, true);
			for (auto &Parameters : List)
			{
				Parameters = Item;
			}
			ModelData(Data, List);
			Assert::AreEqual(NK * NN, Data.Size(), L"", LINE_INFO());
			ModelData(SData, List);
			Assert::AreEqual(NK * NN, SData.Size(), L"", LINE_INFO());
		}

		TEST_METHOD(ModelDataRing)
		{
			const size_t N0 = 0, NK = 32, NN = 2048;
			using FRingDataParameters = TRingDataParameters<3, 3>;
			FRingDataParameters Item;
			TSequence<FRingDataParameters> List;
			TData<FRingDataParameters::FFeature> Data;
			TData<FRingDataParameters::FSample> SData;

			Item = FRingDataParameters::Default();
			Item.N = NN;

			auto API = CMLPrototyping::Instance();

			ModelData(Data, Item);
			Assert::AreEqual(NN, Data.Size(), L"", LINE_INFO());
			ModelData(SData, Item);
			Assert::AreEqual(NN, SData.Size(), L"", LINE_INFO());

			List.Reserve(NK, true);
			for (auto &Parameters : List)
			{
				Parameters = Item;
			}
			ModelData(Data, List);
			Assert::AreEqual(NK * NN, Data.Size(), L"", LINE_INFO());
			ModelData(SData, List);
			Assert::AreEqual(NK * NN, SData.Size(), L"", LINE_INFO());
		}

		TEST_METHOD(ModelDataUniform)
		{
			const size_t N0 = 0, NK = 32, NN = 2048;
			using FUniformDataParameters = TUniformDataParameters<3, 3>;
			FUniformDataParameters Item;
			TSequence<FUniformDataParameters> List;
			TData<FUniformDataParameters::FFeature> Data;
			TData<FUniformDataParameters::FSample> SData;

			Item = FUniformDataParameters::Default();
			Item.N = NN;

			auto API = CMLPrototyping::Instance();

			ModelData(Data, Item);
			Assert::AreEqual(NN, Data.Size(), L"", LINE_INFO());
			ModelData(SData, Item);
			Assert::AreEqual(NN, SData.Size(), L"", LINE_INFO());

			List.Reserve(NK, true);
			for (auto &Parameters : List)
			{
				Parameters = Item;
			}
			ModelData(Data, List);
			Assert::AreEqual(NK * NN, Data.Size(), L"", LINE_INFO());
			ModelData(SData, List);
			Assert::AreEqual(NK * NN, SData.Size(), L"", LINE_INFO());
		}


	};



}