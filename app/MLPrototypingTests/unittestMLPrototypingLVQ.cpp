#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "NDev.h"
#include "NN.h"
#include "LVQ1.h"
#include "SMDLVQ.h"

namespace MLPrototypingTest
{
	using namespace MLPrototyping;
	using namespace NDev;
	using namespace NDev::Types;
	using namespace LVQ;

	TEST_CLASS(UnitTestMLPrototypingLVQ)
	{
	public:
		TEST_METHOD(TestNN)
		{
			const FReal One = 1, Two = 2, Five = 5;
			const FSize Zero = 0,  K = 3, N = 9, DN = 512, FN = 3, LN = 3;
			
			using FModel = TNN<FN, LN>;

			FModel Model;
			TData<FModel::FSample> Samples(DN, True);
			TData<FModel::FFeature> Features(DN, True);
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
			Assert::AreEqual(DN, Model.State.Prototypes.Size(), NullPtr, LINE_INFO());
			
			for (const auto &Prototype : Model.State.Prototypes)
			{
				Assert::AreEqual(Five, Prototype.Label[Zero], NullPtr, LINE_INFO());
				Assert::AreEqual(Two, Prototype.Feature[Zero], NullPtr, LINE_INFO());
			}
			
			Model.Validate(Samples, Errors);
			Model.Use(Features, Labels);
			Model.Optimize(Samples);
			Model.Optimize();
		}

		TEST_METHOD(TestLVQ1)
		{
			const FSize K = 3, N = 9, DN = 512, FN = 3, LN = 3;

			using FModel = TLVQ1<FN, LN>;

			FModel Model;
			TData<FModel::FSample> Samples(DN, True);
			TData<FModel::FFeature> Features(DN, True);
			TData<FModel::FLabel> Labels;
			TData<FModel::FError> Errors;
			TNormal<FReal> Distribution;

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
			const FSize K = 3, N = 9, DN = 512, FN = 3, LN = 3;

			using FModel = TSMDLVQ<FN, LN>;

			FModel Model;
			TData<FModel::FSample> Samples(DN, True);
			TData<FModel::FFeature> Features(DN, True);
			TData<FModel::FLabel> Labels;
			TData<FModel::FError> Errors;
			TNormal<FReal> Distribution;

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

			Model.Parameters.bDynamic = True;
			Model.Use(Features, Labels);
		}


	};



}