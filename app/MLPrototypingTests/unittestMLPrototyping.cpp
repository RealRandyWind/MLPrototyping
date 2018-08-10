#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "Point.h"
#include "Sequence.h"
#include "Data.h"
#include "Model.h"

using namespace MLPrototyping;

namespace MLPrototypingTest
{		
	

	TEST_CLASS(UnitTestMLPrototyping)
	{
	public:
		TEST_METHOD(TestPoint)
		{
			const real_t Zero = 0, One = 1, Two = 2, Three = 3, Four = 4;
			const size_t H1D = 1, H2D = 2, H3D = 3, HND = 2048;
			size_t Index, Center, End;

			/* 1D Point test */
			TPoint<H1D, real_t> P1D;
			End = H1D;
			Assert::AreEqual(P1D.Size(), End, L"", LINE_INFO());
			P1D = Zero;
			for (auto Value : P1D) { Assert::AreEqual(Value, Zero, L"", LINE_INFO()); }
			P1D = One;
			for (auto Value : P1D) { Assert::AreEqual(Value, One, L"", LINE_INFO()); }
			Center = End / 2;
			P1D[Center] = Two;
			for (Index = 0; Index < End; ++Index)
			{
				auto &Value = P1D._Data[Index];
				if (Index == Center) { Assert::AreEqual(Value, Two, L"", LINE_INFO()); }
				else { Assert::AreEqual(Value, One, L"", LINE_INFO());  }
			}
			const auto ConstValue1 = P1D[Center];
			Assert::AreEqual(ConstValue1, Two, L"", LINE_INFO());

			/* 2D Point test */
			TPoint<H2D, real_t> P2D;
			End = H2D;
			Assert::AreEqual(P2D.Size(), End);
			P2D = Zero;
			for (auto Value : P2D) { Assert::AreEqual(Value, Zero, L"", LINE_INFO()); }
			P2D = One;
			for (auto Value : P2D) { Assert::AreEqual(Value, One, L"", LINE_INFO()); }
			Center = End / 2;
			P2D[Center] = Two;
			for (Index = 0; Index < End; ++Index)
			{
				auto &Value = P2D._Data[Index];
				if (Index == Center) { Assert::AreEqual(Value, Two, L"", LINE_INFO()); }
				else { Assert::AreEqual(Value, One, L"", LINE_INFO()); }
			}
			const auto ConstValue2 = P2D[Center];
			Assert::AreEqual(ConstValue2, Two, L"", LINE_INFO());

			/* 3D Point test */
			TPoint<H3D, real_t> P3D;
			End = H3D;
			Assert::AreEqual(P3D.Size(), End, L"", LINE_INFO());
			P3D = Zero;
			for (auto Value : P3D) { Assert::AreEqual(Value, Zero, L"", LINE_INFO()); }
			P3D = One;
			for (auto Value : P3D) { Assert::AreEqual(Value, One, L"", LINE_INFO()); }
			Center = End / 2;
			P3D[Center] = Two;
			for (Index = 0; Index < End; ++Index)
			{
				auto &Value = P3D._Data[Index];
				if (Index == Center) { Assert::AreEqual(Value, Two, L"", LINE_INFO()); }
				else { Assert::AreEqual(Value, One, L"", LINE_INFO()); }
			}
			const auto ConstValue3 = P3D[Center];
			Assert::AreEqual(ConstValue3, Two, L"", LINE_INFO());

			/* ND Point test */
			TPoint<HND, real_t> PND;
			End = HND;
			Assert::AreEqual(PND.Size(), End, L"", LINE_INFO());
			PND = Zero;
			for (auto Value : PND) { Assert::AreEqual(Value, Zero, L"", LINE_INFO()); }
			PND = One;
			for (auto Value : PND) { Assert::AreEqual(Value, One, L"", LINE_INFO()); }
			Center = End / 2;
			PND[Center] = Two;
			for (Index = 0; Index < End; ++Index)
			{
				auto &Value = PND._Data[Index];
				if (Index == Center) { Assert::AreEqual(Value, Two, L"", LINE_INFO()); }
				else { Assert::AreEqual(Value, One, L"", LINE_INFO()); }
			}
			const auto ConstValueN = PND[Center];
			Assert::AreEqual(ConstValueN, Two, L"", LINE_INFO());

			/* casting and assignmnet tests */
			TPoint<HND, size_t> PNDT;
			PNDT = Three;
			PND = PNDT;
			for (auto Value : PND) { Assert::AreEqual(Value, Three, L"", LINE_INFO()); }
			PNDT = Four;
			PND = static_cast<TPoint<HND, real_t>>(PNDT);
			for (auto Value : PND) { Assert::AreEqual(Value, Four, L"", LINE_INFO()); }
			P3D = Zero;
			P3D = PND;
			for (auto Value : P3D) { Assert::AreEqual(Value, Four, L"", LINE_INFO()); }
			P3D = Four;
			PND = One;
			PND = P3D;
			End = HND;
			for (Index = 0; Index < End; ++Index)
			{
				auto &Value = PND._Data[Index];
				if (Index < H3D) { Assert::AreEqual(Value, Four, L"", LINE_INFO()); }
				else { Assert::AreEqual(Value, One, L"", LINE_INFO()); }
			}
			
		}

		TEST_METHOD(TestSequence)
		{
			const real_t Zero = 0, One = 1, Two = 2, Three = 3, Four = 4;
			const size_t HS0 = 0, HS1 = 1, HS2 = 2, HS3 = 3, HSN = 4096, HSK = 8192;
			TSequence<real_t> S0, S1, S2, S3, SN;
			size_t Index, End, Center, Size = 0;
			real_t Number;

			/* reserve buffer tests */
			S1.Reserve(HS1);
			Assert::AreEqual(S1.BufferSize(), HS1, L"", LINE_INFO());
			Assert::AreEqual(S1.Size(), HS0, L"", LINE_INFO());
			S2.Reserve(HS2);
			Assert::AreEqual(S2.BufferSize(), HS2, L"", LINE_INFO());
			Assert::AreEqual(S2.Size(), HS0, L"", LINE_INFO());
			S3.Reserve(HS3);
			Assert::AreEqual(S3.BufferSize(), HS3, L"", LINE_INFO());
			Assert::AreEqual(S3.Size(), HS0, L"", LINE_INFO());
			SN.Reserve(HSN);
			Assert::AreEqual(SN.BufferSize(), HSN, L"", LINE_INFO());
			Assert::AreEqual(SN.Size(), HS0, L"", LINE_INFO());

			/* index access tests */
			S1[HS1 - 1] = One;
			S1[HS1 - 1] = Two;
			Assert::AreEqual(S1._Data[HS1 - 1], Two, L"", LINE_INFO());
			S2[HS2 - 1] = One;
			S2[HS2 - 1] = Two;
			Assert::AreEqual(S2._Data[HS2 - 1], Two, L"", LINE_INFO());
			S3[HS3 - 1] = One;
			S3[HS3 - 1] = Two;
			Assert::AreEqual(S3._Data[HS3 - 1], Two, L"", LINE_INFO());
			SN[HSN - 1] = One;
			SN[HSN - 1] = Two;
			Assert::AreEqual(SN._Data[HSN - 1], Two, L"", LINE_INFO());
			const auto ConstValue = SN[HSN - 1];
			Assert::AreEqual(ConstValue, Two, L"", LINE_INFO());

			/* size/resize on access tests */
			SN.SizeOnAccess();
			SN.ResizeOnAccess();
			Assert::AreEqual(SN.Size(), HS0, L"", LINE_INFO());
			SN[HSN - 1] = Three;
			Assert::AreEqual(SN.BufferSize(), HSN, L"", LINE_INFO());
			Assert::AreEqual(SN.Size(), HSN, L"", LINE_INFO());
			SN[HSN] = Four;
			Assert::AreEqual(SN.BufferSize(), HSN + SN._IncrementSize, L"", LINE_INFO());
			Assert::AreEqual(SN.Size(), HSN + 1, L"", LINE_INFO());
			Assert::AreEqual(SN._Data[HSN], Four, L"", LINE_INFO());


			/* constructor tests */
			Assert::AreEqual(S0.BufferSize(), HS0, L"", LINE_INFO());
			Assert::IsTrue(S0.Empty(), L"", LINE_INFO());
			TSequence<real_t> SK(HSK);
			Assert::AreEqual(SK.BufferSize(), HSK, L"", LINE_INFO());

			/* iterator tests */
			for (auto &Value : SK) { Assert::Fail(L"", LINE_INFO()); }
			SK.IterateAll();
			Size = 0;
			for (auto &Value : SK) { Value = Zero; ++Size; }
			Assert::AreEqual(Size, HSK, L"", LINE_INFO());
			SK.IterateAll(false);
			for (auto &Value : SK) { Assert::Fail(L"", LINE_INFO()); }

			/* add element tests */
			Center = HSK / 2;
			End = Center;
			for (Index = 0; Index < End; ++Index)
			{
				Assert::AreEqual(SK._Data[Index], Zero, L"", LINE_INFO());
				SK.Add(Three);
				Assert::AreEqual(SK.Size(), Index + 1, L"", LINE_INFO());
				Assert::AreEqual(SK._Data[Index], Three, L"", LINE_INFO());
			}
			Size = 0;
			for (auto &Value : SK) { Assert::AreEqual(Value, Three, L"", LINE_INFO()); ++Size; }
			Assert::AreEqual(Size, Center, L"", LINE_INFO());

			/* swap buffer tests */
			Size = 0;
			for (auto &Value : S3) { Value = (real_t) Size; ++Size; }
			End = HS3 * HS3;
			for (Index = 0; Index < End; ++Index)
			{
				Number = (real_t) Index;
				S3.Swap(Number);
				Assert::AreEqual(Number, S3.Active(), L"", LINE_INFO());
			}
		}

		TEST_METHOD(TestModel)
		{
			// TODO: Your test code here
		}

		TEST_METHOD(TestData)
		{
			// TODO: Your test code here
		}

		TEST_METHOD(TestLVQ1)
		{
			// TODO: Your test code here
		}

		TEST_METHOD(TestNN)
		{
			// TODO: Your test code here
		}

		TEST_METHOD(TestSMLVQ)
		{
			// TODO: Your test code here
		}

	};



}