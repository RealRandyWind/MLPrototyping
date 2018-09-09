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
			TNN<FN, LN> Model;
			TData<TNN<FN, LN>::FSample> Samples(DN, true);
			TData<TNN<FN, LN>::FFeature> Features(DN, true);
			TData<TNN<FN, LN>::FLabel> Labels;
			TData<TNN<FN, LN>::FError> Errors;
			TNormal<real_t> Distribution;

			for (auto &Sample : Samples)
			{
				Sample.Feature = Two;
				Sample.Label = Five;
			}

			for (auto &Feature : Features)
			{
				Feature = One;
			}

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
			const real_t Alpha = 0.01;
			const size_t K = 3, N = 9, DN = 512, FN = 3, LN = 3;
			TLVQ1<FN, LN> Model;
			TData<TLVQ1<FN, LN>::FSample> Samples(DN, true);
			TData<TLVQ1<FN, LN>::FFeature> Features(DN, true);
			TData<TLVQ1<FN, LN>::FLabel> Labels;
			TData<TLVQ1<FN, LN>::FError> Errors;
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

			Model.Parameters.KNearest = K;
			Model.Parameters.NPrototypes = N;
			Model.Parameters.LearningRate = Alpha;
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
			const real_t Alpha = 0.01, Beta = 0.05, Gamma = 0.03;
			const size_t K = 3, N = 9, DN = 512, FN = 3, LN = 3;
			TSMDLVQ<FN, LN> Model;
			TData<TSMDLVQ<FN, LN>::FSample> Samples(DN, true);
			TData<TSMDLVQ<FN, LN>::FFeature> Features(DN, true);
			TData<TSMDLVQ<FN, LN>::FLabel> Labels;
			TData<TSMDLVQ<FN, LN>::FError> Errors;
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

			Model.Parameters.bDynamic = false;
			Model.Parameters.KNearest = K;
			Model.Parameters.NPrototypes = N;
			Model.Parameters.LearningRate = Alpha;
			Model.Parameters.MergeTreshold = Beta;
			Model.Parameters.SplitTreshold = Gamma;
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