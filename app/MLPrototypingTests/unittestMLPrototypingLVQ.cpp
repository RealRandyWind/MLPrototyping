#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "MLPrototyping_Types.h"
#include "MLPrototyping_Math.h"
#include "NN.h"
#include "LVQ1.h"
#include "SMDLVQ.h"
#include "Data.h"


using namespace MLPrototyping;
using namespace LVQ;

namespace MLPrototypingTest
{
	TEST_CLASS(UnitTestMLPrototypingLVQ)
	{
	public:
		TEST_METHOD(TestNN)
		{
			const real_t One = 1, Two = 2, Five = 5;
			const size_t Zero = 0,  K = 3, N = 9, DN = 512, FN = 3, LN = 3;
			
			using FModel = TNN<FN, LN>;

			FModel Model;
			TData<FModel::FSample> Samples(DN, true);
			TData<FModel::FFeature> Features(DN, true);
			TData<FModel::FLabel> Labels;
			TData<FModel::FError> Errors;

			for (auto &Sample : Samples)
			{
				Sample.Feature = Two;
				Sample.Label = Five;
			}

			for (auto &Feature : Features)
			{
				Feature = One;
			}

			Model.UseDefaultParameters();
			Model.Parameters.KNearest = K;
			Model.Initialize();

			Model.Train(Samples);
			Assert::AreEqual(DN, Model.State.Prototypes.Size(), nullptr, LINE_INFO());
			
			for (const auto &Prototype : Model.State.Prototypes)
			{
				Assert::AreEqual(Five, Prototype.Label[Zero], nullptr, LINE_INFO());
				Assert::AreEqual(Two, Prototype.Feature[Zero], nullptr, LINE_INFO());
			}
			
			Model.Validate(Samples, Errors);
			Model.Use(Features, Labels);
			Model.Optimize(Samples);
			Model.Optimize();
		}

		TEST_METHOD(TestLVQ1)
		{
			const size_t K = 3, N = 9, DN = 512, FN = 3, LN = 3;

			using FModel = TLVQ1<FN, LN>;

			FModel Model;
			TData<FModel::FSample> Samples(DN, true);
			TData<FModel::FFeature> Features(DN, true);
			TData<FModel::FLabel> Labels;
			TData<FModel::FError> Errors;
			TNormal<real_t> Distribution;

			for (auto &Sample : Samples)
			{
				Distribution(Sample.Feature);
				Distribution(Sample.Label);
			}

			for (auto &Feature : Features)
			{
				Distribution(Feature);
			}

			Model.UseDefaultParameters();
			Model.Parameters.KNearest = K;
			Model.Parameters.NPrototypes = N;
			Model.Initialize();

			for (auto &Prototype : Model.State.Prototypes)
			{
				Distribution(Prototype.Feature);
				Distribution(Prototype.Label);
			}

			Model.Train(Samples);
			Model.Validate(Samples, Errors);
			Model.Use(Features, Labels);
			Model.Optimize(Samples);
			Model.Optimize();
		}

		TEST_METHOD(TestSMDLVQ)
		{
			const size_t K = 3, N = 9, DN = 512, FN = 3, LN = 3;

			using FModel = TSMDLVQ<FN, LN>;

			FModel Model;
			TData<FModel::FSample> Samples(DN, true);
			TData<FModel::FFeature> Features(DN, true);
			TData<FModel::FLabel> Labels;
			TData<FModel::FError> Errors;
			TNormal<real_t> Distribution;

			for (auto &Sample : Samples)
			{
				Distribution(Sample.Feature);
				Distribution(Sample.Label);
			}

			for (auto &Feature : Features)
			{
				Distribution(Feature);
			}

			Model.UseDefaultParameters();
			Model.Parameters.KNearest = K;
			Model.Parameters.NPrototypes = N;
			Model.Initialize();

			for (auto &Prototype : Model.State.Prototypes)
			{
				Distribution(Prototype.Feature);
				Distribution(Prototype.Label);
			}

			Model.Train(Samples);
			Model.Validate(Samples, Errors);
			Model.Use(Features, Labels);
			Model.Optimize(Samples);
			Model.Optimize();

			Model.Parameters.bDynamic = true;
			Model.Use(Features, Labels);
		}


	};



}