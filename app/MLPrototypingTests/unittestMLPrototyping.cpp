#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "NDev.h"
#include "ModelStub.h"


namespace MLPrototypingTest
{
	using namespace NDev;
	using namespace NDev::Types;

	TEST_CLASS(UnitTestMLPrototyping)
	{
	public:
		TEST_METHOD(TestResource)
		{
			const FSize N0 = 0, N1 = 1, N2 = 2, N3 = 3, N4 = 4, N5 = 5;

			Assert::AreEqual(N0, CResource::ResourceCount(), NullPtr, LINE_INFO());
			CResource R1, R2, *R3, *R4, *R5, *R7;
			Assert::AreEqual(N2, CResource::ResourceCount(), NullPtr, LINE_INFO());
			Assert::IsTrue(&R1 == &CResource::Reference(N1 - 1), NullPtr, LINE_INFO());
			Assert::IsTrue(&R2 == &CResource::Reference(N2 - 1), NullPtr, LINE_INFO());
			R3 = new CResource();
			R4 = new CResource();
			Assert::AreEqual(N4, CResource::ResourceCount(), NullPtr, LINE_INFO());
			Assert::AreEqual(N4 - 1, R4->Id(), NullPtr, LINE_INFO());
			Assert::IsTrue(R4 == CResource::Pointer(N4 - 1), NullPtr, LINE_INFO());
			delete R4;
			Assert::IsNull(CResource::Pointer(N4), NullPtr, LINE_INFO());
			Assert::AreEqual(N3, CResource::ResourceCount(), NullPtr, LINE_INFO());
			R5 = new CResource();
			Assert::AreEqual(N4, CResource::ResourceCount(), NullPtr, LINE_INFO());
			Assert::AreEqual(N4 - 1, R5->Id(), NullPtr, LINE_INFO());
			Assert::IsTrue(R5 == CResource::Pointer(N4 - 1), NullPtr, LINE_INFO());
			if (True)
			{
				CResource R6;
				Assert::AreEqual(N5, CResource::ResourceCount(), NullPtr, LINE_INFO());
				Assert::IsTrue(&R6 == CResource::Pointer(N5 - 1), NullPtr, LINE_INFO());
			}
			Assert::AreEqual(N4, CResource::ResourceCount(), NullPtr, LINE_INFO());
			Assert::IsNull(CResource::Pointer(N5 - 1), NullPtr, LINE_INFO());
			delete R5;
			delete R3;
			Assert::AreEqual(N2, CResource::ResourceCount(), NullPtr, LINE_INFO());
			R3 = new CResource();
			R5 = new CResource();
			R7 = new CResource();
			Assert::IsTrue(R3 == CResource::Pointer(N3 - 1), NullPtr, LINE_INFO());
			Assert::IsTrue(R5 == CResource::Pointer(N4 - 1), NullPtr, LINE_INFO());
			Assert::IsTrue(R7 == CResource::Pointer(N5 - 1), NullPtr, LINE_INFO());
			Assert::AreEqual(N5 - 1, R7->Id(), NullPtr, LINE_INFO());
		}

		TEST_METHOD(TestPoint)
		{
			const FReal Zero = 0, One = 1, Two = 2, Three = 3, Four = 4;
			const FSize H1D = 1, H2D = 2, H3D = 3, HND = 2048;
			FSize Index, Center, End;

			/* 1D Point test */
			TPoint<H1D, FReal> P1D;
			End = H1D;
			Assert::AreEqual(P1D.Size(), End, NullPtr, LINE_INFO());
			P1D = Zero;
			for (auto Value : P1D) { Assert::AreEqual(Value, Zero, NullPtr, LINE_INFO()); }
			P1D = One;
			for (auto Value : P1D) { Assert::AreEqual(Value, One, NullPtr, LINE_INFO()); }
			Center = End / 2;
			P1D[Center] = Two;
			for (Index = 0; Index < End; ++Index)
			{
				auto &Value = P1D._Data[Index];
				if (Index == Center) { Assert::AreEqual(Value, Two, NullPtr, LINE_INFO()); }
				else { Assert::AreEqual(Value, One, NullPtr, LINE_INFO());  }
			}
			const auto ConstValue1 = P1D[Center];
			Assert::AreEqual(ConstValue1, Two, NullPtr, LINE_INFO());

			/* 2D Point test */
			TPoint<H2D, FReal> P2D;
			End = H2D;
			Assert::AreEqual(P2D.Size(), End);
			P2D = Zero;
			for (auto Value : P2D) { Assert::AreEqual(Value, Zero, NullPtr, LINE_INFO()); }
			P2D = One;
			for (auto Value : P2D) { Assert::AreEqual(Value, One, NullPtr, LINE_INFO()); }
			Center = End / 2;
			P2D[Center] = Two;
			for (Index = 0; Index < End; ++Index)
			{
				auto &Value = P2D._Data[Index];
				if (Index == Center) { Assert::AreEqual(Value, Two, NullPtr, LINE_INFO()); }
				else { Assert::AreEqual(Value, One, NullPtr, LINE_INFO()); }
			}
			const auto ConstValue2 = P2D[Center];
			Assert::AreEqual(ConstValue2, Two, NullPtr, LINE_INFO());

			/* 3D Point test */
			TPoint<H3D, FReal> P3D;
			End = H3D;
			Assert::AreEqual(P3D.Size(), End, NullPtr, LINE_INFO());
			P3D = Zero;
			for (auto Value : P3D) { Assert::AreEqual(Value, Zero, NullPtr, LINE_INFO()); }
			P3D = One;
			for (auto Value : P3D) { Assert::AreEqual(Value, One, NullPtr, LINE_INFO()); }
			Center = End / 2;
			P3D[Center] = Two;
			for (Index = 0; Index < End; ++Index)
			{
				auto &Value = P3D._Data[Index];
				if (Index == Center) { Assert::AreEqual(Value, Two, NullPtr, LINE_INFO()); }
				else { Assert::AreEqual(Value, One, NullPtr, LINE_INFO()); }
			}
			const auto ConstValue3 = P3D[Center];
			Assert::AreEqual(ConstValue3, Two, NullPtr, LINE_INFO());

			/* ND Point test */
			TPoint<HND, FReal> PND;
			End = HND;
			Assert::AreEqual(PND.Size(), End, NullPtr, LINE_INFO());
			PND = Zero;
			for (auto Value : PND) { Assert::AreEqual(Value, Zero, NullPtr, LINE_INFO()); }
			PND = One;
			for (auto Value : PND) { Assert::AreEqual(Value, One, NullPtr, LINE_INFO()); }
			Center = End / 2;
			PND[Center] = Two;
			for (Index = 0; Index < End; ++Index)
			{
				auto &Value = PND._Data[Index];
				if (Index == Center) { Assert::AreEqual(Value, Two, NullPtr, LINE_INFO()); }
				else { Assert::AreEqual(Value, One, NullPtr, LINE_INFO()); }
			}
			const auto ConstValueN = PND[Center];
			Assert::AreEqual(ConstValueN, Two, NullPtr, LINE_INFO());

			/* casting and assignmnet tests */
			TPoint<HND, FSize> PNDT;
			PNDT = Three;
			PND = PNDT;
			for (auto Value : PND) { Assert::AreEqual(Value, Three, NullPtr, LINE_INFO()); }
			PNDT = Four;
			PND = static_cast<TPoint<HND, FReal>>(PNDT);
			for (auto Value : PND) { Assert::AreEqual(Value, Four, NullPtr, LINE_INFO()); }
			P3D = Zero;
			P3D = PND;
			for (auto Value : P3D) { Assert::AreEqual(Value, Four, NullPtr, LINE_INFO()); }
			P3D = Four;
			PND = One;
			PND = P3D;
			End = HND;
			for (Index = 0; Index < End; ++Index)
			{
				auto &Value = PND._Data[Index];
				if (Index < H3D) { Assert::AreEqual(Value, Four, NullPtr, LINE_INFO()); }
				else { Assert::AreEqual(Value, One, NullPtr, LINE_INFO()); }
			}
			
		}

		TEST_METHOD(TestSequence)
		{
			const FReal Zero = 0, One = 1, Two = 2, Three = 3, Four = 4;
			const FSize HS0 = 0, HS1 = 1, HS2 = 2, HS3 = 3, HSN = 4096, HSK = 8192;
			TSequence<FReal> S0, S1, S2, S3, SN;
			FSize Index, End, Center, Size = 0;
			FReal Number;

			/* reserve buffer tests */
			S1.Reserve(HS1);
			Assert::AreEqual(S1.BufferSize(), HS1, NullPtr, LINE_INFO());
			Assert::AreEqual(S1.Size(), HS0, NullPtr, LINE_INFO());
			S2.Reserve(HS2);
			Assert::AreEqual(S2.BufferSize(), HS2, NullPtr, LINE_INFO());
			Assert::AreEqual(S2.Size(), HS0, NullPtr, LINE_INFO());
			S3.Reserve(HS3);
			Assert::AreEqual(S3.BufferSize(), HS3, NullPtr, LINE_INFO());
			Assert::AreEqual(S3.Size(), HS0, NullPtr, LINE_INFO());
			SN.Reserve(HSN);
			Assert::AreEqual(SN.BufferSize(), HSN, NullPtr, LINE_INFO());
			Assert::AreEqual(SN.Size(), HS0, NullPtr, LINE_INFO());

			/* index access tests */
			S1[HS1 - 1] = One;
			S1[HS1 - 1] = Two;
			Assert::AreEqual(S1._Data[HS1 - 1], Two, NullPtr, LINE_INFO());
			S2[HS2 - 1] = One;
			S2[HS2 - 1] = Two;
			Assert::AreEqual(S2._Data[HS2 - 1], Two, NullPtr, LINE_INFO());
			S3[HS3 - 1] = One;
			S3[HS3 - 1] = Two;
			Assert::AreEqual(S3._Data[HS3 - 1], Two, NullPtr, LINE_INFO());
			SN[HSN - 1] = One;
			SN[HSN - 1] = Two;
			Assert::AreEqual(SN._Data[HSN - 1], Two, NullPtr, LINE_INFO());
			const auto ConstValue = SN[HSN - 1];
			Assert::AreEqual(ConstValue, Two, NullPtr, LINE_INFO());

			/* size/resize on access tests */
			SN.SizeOnAccess();
			SN.ResizeOnAccess();
			Assert::AreEqual(SN.Size(), HS0, NullPtr, LINE_INFO());
			SN[HSN - 1] = Three;
			Assert::AreEqual(SN.BufferSize(), HSN, NullPtr, LINE_INFO());
			Assert::AreEqual(SN.Size(), HSN, NullPtr, LINE_INFO());
			SN[HSN] = Four;
			Assert::AreEqual(SN.BufferSize(), HSN + SN._IncrementSize, NullPtr, LINE_INFO());
			Assert::AreEqual(SN.Size(), HSN + 1, NullPtr, LINE_INFO());
			Assert::AreEqual(SN._Data[HSN], Four, NullPtr, LINE_INFO());


			/* constructor tests */
			Assert::AreEqual(S0.BufferSize(), HS0, NullPtr, LINE_INFO());
			Assert::IsTrue(S0.Empty(), NullPtr, LINE_INFO());
			TSequence<FReal> SK(HSK);
			Assert::AreEqual(SK.BufferSize(), HSK, NullPtr, LINE_INFO());

			/* iterator tests */
			for (auto &Value : SK) { Assert::Fail(NullPtr, LINE_INFO()); }
			SK.IterateAll();
			Size = 0;
			for (auto &Value : SK) { Value = Zero; ++Size; }
			Assert::AreEqual(Size, HSK, NullPtr, LINE_INFO());
			SK.IterateAll(False);
			for (auto &Value : SK) { Assert::Fail(NullPtr, LINE_INFO()); }

			/* add element tests */
			Center = HSK / 2;
			End = Center;
			for (Index = 0; Index < End; ++Index)
			{
				Assert::AreEqual(SK._Data[Index], Zero, NullPtr, LINE_INFO());
				SK.Add(Three);
				Assert::AreEqual(SK.Size(), Index + 1, NullPtr, LINE_INFO());
				Assert::AreEqual(SK._Data[Index], Three, NullPtr, LINE_INFO());
			}
			Size = 0;
			for (auto &Value : SK) { Assert::AreEqual(Value, Three, NullPtr, LINE_INFO()); ++Size; }
			Assert::AreEqual(Size, Center, NullPtr, LINE_INFO());

			/* swap buffer tests */
			Size = 0;
			for (auto &Value : S3) { Value = (FReal) Size; ++Size; }
			End = HS3 * HS3;
			for (Index = 0; Index < End; ++Index)
			{
				Number = (FReal) Index;
				S3.Swap(Number);
				Assert::AreEqual(Number, S3.Active(), NullPtr, LINE_INFO());
			}
		}

		TEST_METHOD(TestData)
		{
			const FReal Zero = 0, One = 1, Two = 2, Three = 3, Four = 4;
			const FSize HD0 = 0, HD1 = 1, HD2 = 2, HD3 = 3, HDN = 4096, HSK = 8192;
			TData<FReal> D0, D1, D2, D3, DN;
			FSize Size = 0;

			/* reserve buffer tests */
			D1.Reserve(HD1);
			Assert::AreEqual(D1.BufferSize(), HD1, NullPtr, LINE_INFO());
			Assert::AreEqual(D1.Size(), HD0, NullPtr, LINE_INFO());
			D2.Reserve(HD2);
			Assert::AreEqual(D2.BufferSize(), HD2, NullPtr, LINE_INFO());
			Assert::AreEqual(D2.Size(), HD0, NullPtr, LINE_INFO());
			D3.Reserve(HD3);
			Assert::AreEqual(D3.BufferSize(), HD3, NullPtr, LINE_INFO());
			Assert::AreEqual(D3.Size(), HD0, NullPtr, LINE_INFO());
			DN.Reserve(HDN);
			Assert::AreEqual(DN.BufferSize(), HDN, NullPtr, LINE_INFO());
			Assert::AreEqual(DN.Size(), HD0, NullPtr, LINE_INFO());

			/* index access tests */
			D1[HD1 - 1] = One;
			D1[HD1 - 1] = Two;
			Assert::AreEqual(D1._Data[HD1 - 1], Two, NullPtr, LINE_INFO());
			D2[HD2 - 1] = One;
			D2[HD2 - 1] = Two;
			Assert::AreEqual(D2._Data[HD2 - 1], Two, NullPtr, LINE_INFO());
			D3[HD3 - 1] = One;
			D3[HD3 - 1] = Two;
			Assert::AreEqual(D3._Data[HD3 - 1], Two, NullPtr, LINE_INFO());
			DN[HDN - 1] = One;
			DN[HDN - 1] = Two;
			Assert::AreEqual(DN._Data[HDN - 1], Two, NullPtr, LINE_INFO());
			const auto ConstValue = DN[HDN - 1];
			Assert::AreEqual(ConstValue, Two, NullPtr, LINE_INFO());


			/* constructor tests */
			Assert::AreEqual(D0.BufferSize(), HD0, NullPtr, LINE_INFO());
			Assert::IsTrue(D0.Empty(), NullPtr, LINE_INFO());
			TData<FReal> SK(HSK);
			Assert::AreEqual(SK.BufferSize(), HSK, NullPtr, LINE_INFO());

			/* iterator tests */
			for (auto &Value : SK) { Assert::Fail(NullPtr, LINE_INFO()); }
			SK.IterateAll();
			Size = 0;
			for (auto &Value : SK) { Value = Zero; ++Size; }
			Assert::AreEqual(Size, HSK, NullPtr, LINE_INFO());
			SK.IterateAll(False);
			for (auto &Value : SK) { Assert::Fail(NullPtr, LINE_INFO()); }
		}

		TEST_METHOD(TestModel)
		{
			/*(F|L|M)\d   ${1}2*/
			const FReal Zero = 0, Half = .5, One = 1, Two = 2, Three = 3;
			const FSize N0 = 0, L1 = 1, F1 = 2, L2 = 2, F2 = 4, L3 = 3, F3 = 6, LN = 256, FN = 512;
			FSize Index, End;
			FReal RU, RT, RO, RO1;;
			
			/* 2D Feature 1D Label, 2 Data tests */
			RU = F1 * One; RT = Half - RU; RO = RT + F1 * Half * (F1 * One + L1 * Half), RO1 = Half * RO;
			TModelStub<F1, L1> M1;
			TData<TModelStub<F1, L1>::FError> Errors1;
			TData<TModelStub<F1, L1>::FFeature> Features1(F1, True);
			TData<TModelStub<F1, L1>::FLabel> Labels1;
			TData<TModelStub<F1, L1>::FSample> Samples1(F1, True);
			End = F1;
			for (Index = 0; Index < End; ++Index)
			{
				Features1[Index] = One;
				Samples1[Index].Feature = One;
				Samples1[Index].Label = Half;
			}
			Assert::AreEqual(M1.FeatureSize(), F1, NullPtr, LINE_INFO());
			Assert::AreEqual(M1.LabelSize(), L1, NullPtr, LINE_INFO());
			M1.Parameters = { One, Half, Zero, F1 };
			M1.Parameters.Alpha = One;
			M1.Parameters.Weight = Half;
			M1.Parameters.Difference = Zero;
			M1.Parameters.Size = F1;
			Assert::IsFalse(M1.Initialized(), NullPtr, LINE_INFO());
			M1.Initialize();
			Assert::IsTrue(M1.Initialized(), NullPtr, LINE_INFO());
			Assert::AreEqual(F1, M1.State.Weights.Size(), NullPtr, LINE_INFO());
			for (const auto &Weight : M1.State.Weights)
			{
				Assert::AreEqual(One, Weight, NullPtr, LINE_INFO());
			}
			for (const auto &Value : M1.State.Difference)
			{
				Assert::AreEqual(Zero, Value, NullPtr, LINE_INFO());
			}
			Assert::AreEqual(N0, Labels1.Size(), NullPtr, LINE_INFO());
			M1.Use(Features1, Labels1);
			Assert::AreEqual(F1, Labels1.Size(), NullPtr, LINE_INFO());
			for (const auto &Label : Labels1)
			{
				for (const auto &Value : Label)
				{
					Assert::AreEqual(RU, Value, NullPtr, LINE_INFO());
				}
			}
			M1.Train(Samples1);
			for (const auto &Value : M1.State.Difference)
			{
				Assert::AreEqual(RT, Value, NullPtr, LINE_INFO());
			}
			M1.Optimize(Samples1);
			for (const auto &Value : M1.State.Difference)
			{
				Assert::AreEqual(RO, Value, NullPtr, LINE_INFO());
			}
			M1.Optimize();
			for (const auto &Value : M1.State.Difference)
			{
				Assert::AreEqual(RO1, Value, NullPtr, LINE_INFO());
			}
			M1.Validate(Samples1, Errors1);
			for (const auto &Error : Errors1)
			{
				for (const auto &Value : Error.Value)
				{
					Assert::AreEqual(Half - RU, Value, NullPtr, LINE_INFO());
				}
			}

			/* 4D Feature 2D Label, 4 Data tests */
			RU = F2 * One; RT = Half - RU; RO = RT + F2 * Half * (F2 * One + L2 * Half), RO1 = Half * RO;
			TModelStub<F2, L2> M2;
			TData<TModelStub<F2, L2>::FError> Errors2;
			TData<TModelStub<F2, L2>::FFeature> Features2(F2, True);
			TData<TModelStub<F2, L2>::FLabel> Labels2;
			TData<TModelStub<F2, L2>::FSample> Samples2(F2, True);
			End = F2;
			for (Index = 0; Index < End; ++Index)
			{
				Features2[Index] = One;
				Samples2[Index].Feature = One;
				Samples2[Index].Label = Half;
			}
			Assert::AreEqual(M2.FeatureSize(), F2, NullPtr, LINE_INFO());
			Assert::AreEqual(M2.LabelSize(), L2, NullPtr, LINE_INFO());
			M2.Parameters = { One, Half, Zero, F2 };
			M2.Parameters.Alpha = One;
			M2.Parameters.Weight = Half;
			M2.Parameters.Difference = Zero;
			M2.Parameters.Size = F2;
			Assert::IsFalse(M2.Initialized(), NullPtr, LINE_INFO());
			M2.Initialize();
			Assert::IsTrue(M2.Initialized(), NullPtr, LINE_INFO());
			Assert::AreEqual(F2, M2.State.Weights.Size(), NullPtr, LINE_INFO());
			for (const auto &Weight : M2.State.Weights)
			{
				Assert::AreEqual(One, Weight, NullPtr, LINE_INFO());
			}
			for (const auto &Value : M2.State.Difference)
			{
				Assert::AreEqual(Zero, Value, NullPtr, LINE_INFO());
			}
			Assert::AreEqual(N0, Labels2.Size(), NullPtr, LINE_INFO());
			M2.Use(Features2, Labels2);
			Assert::AreEqual(F2, Labels2.Size(), NullPtr, LINE_INFO());
			for (const auto &Label : Labels2)
			{
				for (const auto &Value : Label)
				{
					Assert::AreEqual(RU, Value, NullPtr, LINE_INFO());
				}
			}
			M2.Train(Samples2);
			for (const auto &Value : M2.State.Difference)
			{
				Assert::AreEqual(RT, Value, NullPtr, LINE_INFO());
			}
			M2.Optimize(Samples2);
			for (const auto &Value : M2.State.Difference)
			{
				Assert::AreEqual(RO, Value, NullPtr, LINE_INFO());
			}
			M2.Optimize();
			for (const auto &Value : M2.State.Difference)
			{
				Assert::AreEqual(RO1, Value, NullPtr, LINE_INFO());
			}
			M2.Validate(Samples2, Errors2);
			for (const auto &Error : Errors2)
			{
				for (const auto &Value : Error.Value)
				{
					Assert::AreEqual(Half - RU, Value, NullPtr, LINE_INFO());
				}
			}

			/* 6D Feature 3D Label, 6 Data tests */
			RU = F3 * One; RT = Half - RU; RO = RT + F3 * Half * (F3 * One + L3 * Half), RO1 = Half * RO;
			TModelStub<F3, L3> M3;
			TData<TModelStub<F3, L3>::FError> Errors3;
			TData<TModelStub<F3, L3>::FFeature> Features3(F3, True);
			TData<TModelStub<F3, L3>::FLabel> Labels3;
			TData<TModelStub<F3, L3>::FSample> Samples3(F3, True);
			End = F3;
			for (Index = 0; Index < End; ++Index)
			{
				Features3[Index] = One;
				Samples3[Index].Feature = One;
				Samples3[Index].Label = Half;
			}
			Assert::AreEqual(M3.FeatureSize(), F3, NullPtr, LINE_INFO());
			Assert::AreEqual(M3.LabelSize(), L3, NullPtr, LINE_INFO());
			M3.Parameters = { One, Half, Zero, F3 };
			M3.Parameters.Alpha = One;
			M3.Parameters.Weight = Half;
			M3.Parameters.Difference = Zero;
			M3.Parameters.Size = F3;
			Assert::IsFalse(M3.Initialized(), NullPtr, LINE_INFO());
			M3.Initialize();
			Assert::IsTrue(M3.Initialized(), NullPtr, LINE_INFO());
			Assert::AreEqual(F3, M3.State.Weights.Size(), NullPtr, LINE_INFO());
			for (const auto &Weight : M3.State.Weights)
			{
				Assert::AreEqual(One, Weight, NullPtr, LINE_INFO());
			}
			for (const auto &Value : M3.State.Difference)
			{
				Assert::AreEqual(Zero, Value, NullPtr, LINE_INFO());
			}
			Assert::AreEqual(N0, Labels3.Size(), NullPtr, LINE_INFO());
			M3.Use(Features3, Labels3);
			Assert::AreEqual(F3, Labels3.Size(), NullPtr, LINE_INFO());
			for (const auto &Label : Labels3)
			{
				for (const auto &Value : Label)
				{
					Assert::AreEqual(RU, Value, NullPtr, LINE_INFO());
				}
			}
			M3.Train(Samples3);
			for (const auto &Value : M3.State.Difference)
			{
				Assert::AreEqual(RT, Value, NullPtr, LINE_INFO());
			}
			M3.Optimize(Samples3);
			for (const auto &Value : M3.State.Difference)
			{
				Assert::AreEqual(RO, Value, NullPtr, LINE_INFO());
			}
			M3.Optimize();
			for (const auto &Value : M3.State.Difference)
			{
				Assert::AreEqual(RO1, Value, NullPtr, LINE_INFO());
			}
			M3.Validate(Samples3, Errors3);
			for (const auto &Error : Errors3)
			{
				for (const auto &Value : Error.Value)
				{
					Assert::AreEqual(Half - RU, Value, NullPtr, LINE_INFO());
				}
			}

			/* 2ND Feature ND Label, 2N Data tests */
			RU = FN * One; RT = Half - RU; RO = RT + FN * Half * (FN * One + LN * Half), RO1 = Half * RO;
			TModelStub<FN, LN> MN;
			TData<TModelStub<FN, LN>::FError> ErrorsN;
			TData<TModelStub<FN, LN>::FFeature> FeaturesN(FN, True);
			TData<TModelStub<FN, LN>::FLabel> LabelsN;
			TData<TModelStub<FN, LN>::FSample> SamplesN(FN, True);
			End = FN;
			for (Index = 0; Index < End; ++Index)
			{
				FeaturesN[Index] = One;
				SamplesN[Index].Feature = One;
				SamplesN[Index].Label = Half;
			}
			Assert::AreEqual(MN.FeatureSize(), FN, NullPtr, LINE_INFO());
			Assert::AreEqual(MN.LabelSize(), LN, NullPtr, LINE_INFO());
			MN.Parameters = { One, Half, Zero, FN };
			MN.Parameters.Alpha = One;
			MN.Parameters.Weight = Half;
			MN.Parameters.Difference = Zero;
			MN.Parameters.Size = FN;
			Assert::IsFalse(MN.Initialized(), NullPtr, LINE_INFO());
			MN.Initialize();
			Assert::IsTrue(MN.Initialized(), NullPtr, LINE_INFO());
			Assert::AreEqual(FN, MN.State.Weights.Size(), NullPtr, LINE_INFO());
			for (const auto &Weight : MN.State.Weights)
			{
				Assert::AreEqual(One, Weight, NullPtr, LINE_INFO());
			}
			for (const auto &Value : MN.State.Difference)
			{
				Assert::AreEqual(Zero, Value, NullPtr, LINE_INFO());
			}
			Assert::AreEqual(N0, LabelsN.Size(), NullPtr, LINE_INFO());
			MN.Use(FeaturesN, LabelsN);
			Assert::AreEqual(FN, LabelsN.Size(), NullPtr, LINE_INFO());
			for (const auto &Label : LabelsN)
			{
				for (const auto &Value : Label)
				{
					Assert::AreEqual(RU, Value, NullPtr, LINE_INFO());
				}
			}
			MN.Train(SamplesN);
			for (const auto &Value : MN.State.Difference)
			{
				Assert::AreEqual(RT, Value, NullPtr, LINE_INFO());
			}
			MN.Optimize(SamplesN);
			for (const auto &Value : MN.State.Difference)
			{
				Assert::AreEqual(RO, Value, NullPtr, LINE_INFO());
			}
			MN.Optimize();
			for (const auto &Value : MN.State.Difference)
			{
				Assert::AreEqual(RO1, Value, NullPtr, LINE_INFO());
			}
			MN.Validate(SamplesN, ErrorsN);
			for (const auto &Error : ErrorsN)
			{
				for (const auto &Value : Error.Value)
				{
					Assert::AreEqual(Half - RU, Value, NullPtr, LINE_INFO());
				}
			}
		}


	};



}