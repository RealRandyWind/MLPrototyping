#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "MLPrototyping.h"
#include "MLPrototyping_Generate.h"
#include "NDev.h"

using namespace MLPrototyping;

namespace MLPrototypingTest
{	
	using namespace NDev;
	using namespace NDev::Types;

	TEST_CLASS(UnitTestMLPrototypingGenerate)
	{
	public:
		TEST_METHOD(ModelDataNormal)
		{
			const FSize N0 = 0, NK = 32, NN = 2048;

			using FNormalDataParameters = TNormalDataParameters<3, 3>;
			FNormalDataParameters Item;
			TSequence<FNormalDataParameters> List;
			TData<FNormalDataParameters::FFeature> Data;
			TData<FNormalDataParameters::FSample> SData;

			Item = FNormalDataParameters::Default();
			Item.N = NN;

			auto API = CMLPrototyping::Instance();

			ModelData(Data, Item);
			Assert::AreEqual(NN, Data.Size(), NullPtr, LINE_INFO());
			ModelData(SData, Item);
			Assert::AreEqual(NN, SData.Size(), NullPtr, LINE_INFO());

			List.Reserve(NK, True);
			for (auto &Parameters : List)
			{
				Parameters = Item;
			}
			ModelData(Data, List);
			Assert::AreEqual(NK * NN, Data.Size(), NullPtr, LINE_INFO());
			ModelData(SData, List);
			Assert::AreEqual(NK * NN, SData.Size(), NullPtr, LINE_INFO());
		}

		TEST_METHOD(ModelDataGamma)
		{
			const FSize N0 = 0, NK = 32, NN = 2048;
			using FGammaDataParameters = TGammaDataParameters<3, 3>;
			FGammaDataParameters Item;
			TSequence<FGammaDataParameters> List;
			TData<FGammaDataParameters::FFeature> Data;
			TData<FGammaDataParameters::FSample> SData;

			Item = FGammaDataParameters::Default();
			Item.N = NN;

			auto API = CMLPrototyping::Instance();

			ModelData(Data, Item);
			Assert::AreEqual(NN, Data.Size(), NullPtr, LINE_INFO());
			ModelData(SData, Item);
			Assert::AreEqual(NN, SData.Size(), NullPtr, LINE_INFO());

			List.Reserve(NK, True);
			for (auto &Parameters : List)
			{
				Parameters = Item;
			}
			ModelData(Data, List);
			Assert::AreEqual(NK * NN, Data.Size(), NullPtr, LINE_INFO());
			ModelData(SData, List);
			Assert::AreEqual(NK * NN, SData.Size(), NullPtr, LINE_INFO());
		}

		TEST_METHOD(ModelDataRing)
		{
			const FSize N0 = 0, NK = 32, NN = 2048;
			using FRingDataParameters = TRingDataParameters<3, 3>;
			FRingDataParameters Item;
			TSequence<FRingDataParameters> List;
			TData<FRingDataParameters::FFeature> Data;
			TData<FRingDataParameters::FSample> SData;

			Item = FRingDataParameters::Default();
			Item.N = NN;

			auto API = CMLPrototyping::Instance();

			ModelData(Data, Item);
			Assert::AreEqual(NN, Data.Size(), NullPtr, LINE_INFO());
			ModelData(SData, Item);
			Assert::AreEqual(NN, SData.Size(), NullPtr, LINE_INFO());

			List.Reserve(NK, True);
			for (auto &Parameters : List)
			{
				Parameters = Item;
			}
			ModelData(Data, List);
			Assert::AreEqual(NK * NN, Data.Size(), NullPtr, LINE_INFO());
			ModelData(SData, List);
			Assert::AreEqual(NK * NN, SData.Size(), NullPtr, LINE_INFO());
		}

		TEST_METHOD(ModelDataUniform)
		{
			const FSize N0 = 0, NK = 32, NN = 2048;
			using FUniformDataParameters = TUniformDataParameters<3, 3>;
			FUniformDataParameters Item;
			TSequence<FUniformDataParameters> List;
			TData<FUniformDataParameters::FFeature> Data;
			TData<FUniformDataParameters::FSample> SData;

			Item = FUniformDataParameters::Default();
			Item.N = NN;

			auto API = CMLPrototyping::Instance();

			ModelData(Data, Item);
			Assert::AreEqual(NN, Data.Size(), NullPtr, LINE_INFO());
			ModelData(SData, Item);
			Assert::AreEqual(NN, SData.Size(), NullPtr, LINE_INFO());

			List.Reserve(NK, True);
			for (auto &Parameters : List)
			{
				Parameters = Item;
			}
			ModelData(Data, List);
			Assert::AreEqual(NK * NN, Data.Size(), NullPtr, LINE_INFO());
			ModelData(SData, List);
			Assert::AreEqual(NK * NN, SData.Size(), NullPtr, LINE_INFO());
		}


	};



}