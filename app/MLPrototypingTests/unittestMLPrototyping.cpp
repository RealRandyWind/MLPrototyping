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
			Assert::AreEqual(P1D.Size(), End, L"Point Size");
			P1D = Zero;
			for (auto Value : P1D) { Assert::AreEqual(Value, Zero, L"Alpha Assign Zero"); }
			P1D = One;
			for (auto Value : P1D) { Assert::AreEqual(Value, One, L"Alpha Assign One"); }
			Center = End / 2;
			P1D[Center] = Two;
			for (Index = 0; Index < End; ++Index)
			{
				auto &Value = P1D._Data[Index];
				if (Index == Center) { Assert::AreEqual(Value, Two, L"Index Assign Center Two"); }
				else { Assert::AreEqual(Value, One, L"Index Assign Center Unchanged");  }
			}

			/* 2D Point test */
			TPoint<H2D, real_t> P2D;
			End = H2D;
			Assert::AreEqual(P2D.Size(), End, L"Point Size");
			P2D = Zero;
			for (auto Value : P2D) { Assert::AreEqual(Value, Zero, L"Alpha Assign Zero"); }
			P2D = One;
			for (auto Value : P2D) { Assert::AreEqual(Value, One, L"Alpha Assign One"); }
			Center = End / 2;
			P2D[Center] = Two;
			for (Index = 0; Index < End; ++Index)
			{
				auto &Value = P2D._Data[Index];
				if (Index == Center) { Assert::AreEqual(Value, Two, L"Index Assign Center Two"); }
				else { Assert::AreEqual(Value, One, L"Index Assign Center Unchanged"); }
			}

			/* 3D Point test */
			TPoint<H3D, real_t> P3D;
			End = H3D;
			Assert::AreEqual(P3D.Size(), End, L"Point Size");
			P3D = Zero;
			for (auto Value : P3D) { Assert::AreEqual(Value, Zero, L"Alpha Assign Zero"); }
			P3D = One;
			for (auto Value : P3D) { Assert::AreEqual(Value, One, L"Alpha Assign One"); }
			Center = End / 2;
			P3D[Center] = Two;
			for (Index = 0; Index < End; ++Index)
			{
				auto &Value = P3D._Data[Index];
				if (Index == Center) { Assert::AreEqual(Value, Two, L"Index Assign Center Two"); }
				else { Assert::AreEqual(Value, One, L"Index Assign Center Unchanged"); }
			}

			/* ND Point test */
			TPoint<HND, real_t> PND;
			End = HND;
			Assert::AreEqual(PND.Size(), End, L"Point Size");
			PND = Zero;
			for (auto Value : PND) { Assert::AreEqual(Value, Zero, L"Alpha Assign Zero"); }
			PND = One;
			for (auto Value : PND) { Assert::AreEqual(Value, One, L"Alpha Assign One"); }
			Center = End / 2;
			PND[Center] = Two;
			for (Index = 0; Index < End; ++Index)
			{
				auto &Value = PND._Data[Index];
				if (Index == Center) { Assert::AreEqual(Value, Two, L"Index Assign Center Two"); }
				else { Assert::AreEqual(Value, One, L"Index Assign Center Unchanged"); }
			}

			/* casting and assignmnet tests */
			TPoint<HND, size_t> PNDT;
			PNDT = Three;
			PND = PNDT;
			for (auto Value : PND) { Assert::AreEqual(Value, Three, L"Alpha Assign Three"); }
			PNDT = Four;
			PND = static_cast<TPoint<HND, real_t>>(PNDT);
			for (auto Value : PND) { Assert::AreEqual(Value, Four, L"Alpha Assign Four"); }
			P3D = Zero;
			P3D = PND;
			for (auto Value : P3D) { Assert::AreEqual(Value, Four, L"Alpha Assign Four"); }
			P3D = Four;
			PND = One;
			PND = P3D;
			End = HND;
			for (Index = 0; Index < End; ++Index)
			{
				auto &Value = PND._Data[Index];
				if (Index < H3D) { Assert::AreEqual(Value, Four, L"Alpha Assign Four"); }
				else { Assert::AreEqual(Value, One, L"Alpha Unchanged Assign One"); }
			}
		}

		TEST_METHOD(TestSequence)
		{
			// TODO: Your test code here
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