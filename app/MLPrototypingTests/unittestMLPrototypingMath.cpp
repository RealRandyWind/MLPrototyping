#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include "NDev.h"

namespace MLPrototypingTest
{
	using namespace NDev;
	using namespace NDev::Types;

	TEST_CLASS(UnitTestMLPrototypingMath)
	{
	public:
		TEST_METHOD(TestQuinsor)
		{
			/*
			const FSize N0 = 0, ND1 = 1, ND2 = 2, ND3 = 3, NDN = 4096;
			const FReal Zero = 0, One = 1, Two = 2 , Half = .5;
			FSize Index, End;
			
			TPoint<ND1, FReal> P1;
			TQuinsor<ND1, FReal> Q1, R1;
			Q1 = Half;
			Q1[ND1 - 1] = 1;
			P1 = Two;
			IntoPoint(P1, Q1);
			Assert::AreEqual(One, Norm(P1), NullPtr, LINE_INFO());
			IntoQuinsor(R1, P1);
			End = ND1;
			for (Index = 0; Index < End; ++Index)
			{
				Assert::AreEqual(Q1[Index], R1[Index], NullPtr, LINE_INFO());
			}
			*/
		}

		TEST_METHOD(TestPointTypes)
		{
			const FReal Zero = 0, Half = .5, One = 1, OneHalf = 1.5;
			TColor<FReal> C0, C1, C2;
			FSize Index, End, Empty = 0, Green = 1;

			C0.Point = Half;
			C1.Point = One;
			C2.Point = OneHalf;
			C0.Point += C1.Point;
			Assert::AreNotEqual(C0.Point.Size(), Empty, NullPtr, LINE_INFO());
			End = C0.Point.Size();
			for (Index = 0; Index < End; ++Index)
			{
				Assert::AreEqual(C0.Point[Index], C2.Point[Index], NullPtr, LINE_INFO());
			}
			C0.G = 0.5;
			Assert::AreEqual(C0.G, C0.Point[Green], NullPtr, LINE_INFO());
		}

		TEST_METHOD(TestLimit)
		{
			const FReal Zero = 0, One = 1;
			FReal Maximum, Minimum, Lower, Upper, Epsilon, NaN;

			Maximum = TLimit<FReal>::Infinity();
			Minimum = -TLimit<FReal>::Infinity();
			Upper = TLimit<FReal>::Upper();
			Lower = TLimit<FReal>::Lower();
			Epsilon = TLimit<FReal>::Epsilon();
			NaN = TLimit<FReal>::NaN();

			Assert::IsTrue(Epsilon > Zero, NullPtr, LINE_INFO());
			Assert::IsTrue(Epsilon < One, NullPtr, LINE_INFO());
			Assert::IsTrue(Maximum > Upper, NullPtr, LINE_INFO());
			Assert::IsTrue(Minimum < Lower, NullPtr, LINE_INFO());
			Assert::AreEqual(Min(Minimum, Lower), Minimum, NullPtr, LINE_INFO());
			Assert::AreEqual(Max(Upper, Maximum), Maximum, NullPtr, LINE_INFO());
			Assert::AreEqual(Max(Minimum, Lower), Lower, NullPtr, LINE_INFO());
			Assert::AreEqual(Min(Maximum, Upper), Upper, NullPtr, LINE_INFO());
		}

		TEST_METHOD(TestDistribution)
		{
			const FReal Parm1 = .5, Parm2 = 1.5;
			const FSize N0 = 0;
			FReal Number;
			TPoint<4096, FReal> PND;

			TNormal<FReal> NDistribution;
			NDistribution.Seed(N0);
			NDistribution.Parameters(Parm1, Parm2);
			PND = NDistribution();
			Number = NDistribution();
			NDistribution(PND);
			NDistribution(Number);

			TGamma<FReal> GDistribution;
			GDistribution.Seed(N0);
			GDistribution.Parameters(Parm1, Parm2);
			PND = GDistribution();
			Number = GDistribution();
			GDistribution(PND);
			GDistribution(Number);

			TUniform<FReal> UDistribution;
			UDistribution.Seed(N0);
			UDistribution.Parameters(Parm1, Parm2);
			PND = UDistribution();
			Number = UDistribution();
			UDistribution(PND);
			UDistribution(Number);
		}

		TEST_METHOD(TestSum)
		{
			const FSize ND1 = 1, ND2 = 2, ND3 = 3, NDN = 4096;
			const FReal Two = 2, Four = 4;
			const FReal R1 = ND1 * Two, R2 = ND2 * Two, R3 = ND3 * Two, RN = NDN * Two;
			FReal Result;

			TPoint<ND1, FReal> P1D;
			P1D = Two;
			Result = Sum(P1D);
			Assert::AreEqual(Result, R1, NullPtr, LINE_INFO());

			TPoint<ND2, FReal> P2D;
			P2D = Two;
			Result = Sum(P2D);
			Assert::AreEqual(Result, R2, NullPtr, LINE_INFO());

			TPoint<ND3, FReal> P3D;
			P3D = Two;
			Result = Sum(P3D);
			Assert::AreEqual(Result, R3, NullPtr, LINE_INFO());

			TPoint<NDN, FReal> PND;
			PND = Two;
			Result = Sum(PND);
			Assert::AreEqual(Result, RN, NullPtr, LINE_INFO());
		}

		TEST_METHOD(TestNorm2)
		{
			const FSize ND1 = 1, ND2 = 2, ND3 = 3, NDN = 4096;
			const FReal Two = 2, Four = 4;
			const FReal R1 = ND1 * Four, R2 = ND2 * Four, R3 = ND3 * Four, RN = NDN * Four;
			FReal Result;

			TPoint<ND1, FReal> P1D;
			P1D = Two;
			Result = Norm2(P1D);
			Assert::AreEqual(Result, R1, NullPtr, LINE_INFO());

			TPoint<ND2, FReal> P2D;
			P2D = Two;
			Result = Norm2(P2D);
			Assert::AreEqual(Result, R2, NullPtr, LINE_INFO());

			TPoint<ND3, FReal> P3D;
			P3D = Two;
			Result = Norm2(P3D);
			Assert::AreEqual(Result, R3, NullPtr, LINE_INFO());

			TPoint<NDN, FReal> PND;
			PND = Two;
			Result = Norm2(PND);
			Assert::AreEqual(Result, RN, NullPtr, LINE_INFO());
		}

		TEST_METHOD(TestNorm)
		{
			const FSize ND1 = 1, ND2 = 2, ND3 = 3, NDN = 4096;
			const FReal Zero = 0, Two = 2, Four = 4;
			const FReal R1 = sqrt(ND1 * Four), R2 = sqrt(ND2 * Four), R3 = sqrt(ND3 * Four), RN = sqrt(NDN * Four);
			FReal Result;

			TPoint<ND1, FReal> P1D;
			P1D = Two;
			Result = Norm(P1D);
			Assert::AreEqual(Result, R1, NullPtr, LINE_INFO());

			TPoint<ND2, FReal> P2D;
			P2D = Two;
			Result = Norm(P2D);
			Assert::AreEqual(Result, R2, NullPtr, LINE_INFO());

			TPoint<ND3, FReal> P3D;
			P3D = Two;
			Result = Norm(P3D);
			Assert::AreEqual(Result, R3, NullPtr, LINE_INFO());

			TPoint<NDN, FReal> PND;
			PND = Two;
			Result = Norm(PND);
			Assert::AreEqual(Result, RN, NullPtr, LINE_INFO());
		}

		TEST_METHOD(TestNormalize)
		{
			const FSize ND1 = 1, ND2 = 2, ND3 = 3, NDN = 4096;
			const FReal Zero = 0, Two = 2, Four = 4;
			const FReal N1 = sqrt(ND1 * Four), N2 = sqrt(ND2 * Four), N3 = sqrt(ND3 * Four), NN = sqrt(NDN * Four);
			FSize Index, End;

			TPoint<ND1, FReal> P1D, R1;
			R1 = Two / N1;
			P1D = Two;
			Normalize(P1D);
			End = ND1;
			for (Index = 0; Index < End; ++Index)
			{
				Assert::AreEqual(R1[Index], P1D[Index], NullPtr, LINE_INFO());
			}

			TPoint<ND2, FReal> P2D, R2;
			R2 = Two / N2;
			P2D = Two;
			Normalize(P2D);
			End = ND2;
			for (Index = 0; Index < End; ++Index)
			{
				Assert::AreEqual(R2[Index], P2D[Index], NullPtr, LINE_INFO());
			}

			TPoint<ND3, FReal> P3D, R3;
			R3 = Two / N3;
			P3D = Two;
			Normalize(P3D);
			End = ND3;
			for (Index = 0; Index < End; ++Index)
			{
				Assert::AreEqual(R3[Index], P3D[Index], NullPtr, LINE_INFO());
			}

			TPoint<NDN, FReal> PND, RN;
			RN = Two / NN;
			PND = Two;
			Normalize(PND);
			End = NDN;
			for (Index = 0; Index < End; ++Index)
			{
				Assert::AreEqual(RN[Index], PND[Index], NullPtr, LINE_INFO());
			}
		}

		TEST_METHOD(TestNormalize2)
		{
			const FSize ND1 = 1, ND2 = 2, ND3 = 3, NDN = 4096;
			const FReal Two = 2, Four = 4;
			const FReal N1 = ND1 * Four, N2 = ND2 * Four, N3 = ND3 * Four, NN = NDN * Four;
			FSize Index, End;

			TPoint<ND1, FReal> P1D, R1;
			R1 = Two / N1;
			P1D = Two;
			Normalize2(P1D);
			End = ND1;
			for (Index = 0; Index < End; ++Index)
			{
				Assert::AreEqual(R1[Index], P1D[Index], NullPtr, LINE_INFO());
			}

			TPoint<ND2, FReal> P2D, R2;
			R2 = Two / N2;
			P2D = Two;
			Normalize2(P2D);
			End = ND2;
			for (Index = 0; Index < End; ++Index)
			{
				Assert::AreEqual(R2[Index], P2D[Index], NullPtr, LINE_INFO());
			}

			TPoint<ND3, FReal> P3D, R3;
			R3 = Two / N3;
			P3D = Two;
			Normalize2(P3D);
			End = ND3;
			for (Index = 0; Index < End; ++Index)
			{
				Assert::AreEqual(R3[Index], P3D[Index], NullPtr, LINE_INFO());
			}

			TPoint<NDN, FReal> PND, RN;
			RN = Two / NN;
			PND = Two;
			Normalize2(PND);
			End = NDN;
			for (Index = 0; Index < End; ++Index)
			{
				Assert::AreEqual(RN[Index], PND[Index], NullPtr, LINE_INFO());
			}
		}

		TEST_METHOD(TestMin)
		{
			const FSize ND1 = 1, ND2 = 2, ND3 = 3, NDN = 4096;
			const FReal Zero = 0, One = 1, Two = 2, Three = 3, Four = 4;
			FSize Index, End;

			TPoint<ND1, FReal> P1D1, P2D1, P3D1, R1;
			P1D1 = Three;
			P2D1 = Four;
			End = ND1 / 2 + 1;
			for (Index = 0; Index < End; ++Index) { P1D1[Index] = R1[Index] = Two; }
			End = ND1;
			for (; Index < End; ++Index) { P2D1[Index] = R1[Index] = One; }
			P3D1 = Min(P1D1, P2D1);
			End = ND1;
			for (Index = 0; Index < End; ++Index)
			{
				Assert::AreEqual(R1[Index], P3D1[Index], NullPtr, LINE_INFO());
			}

			TPoint<ND2, FReal> P1D2, P2D2, P3D2, R2;
			P1D2 = Three;
			P2D2 = Four;
			End = ND2 / 2 + 1;
			for (Index = 0; Index < End; ++Index) { P1D2[Index] = R2[Index] = Two; }
			End = ND2;
			for (; Index < End; ++Index) { P2D2[Index] = R2[Index] = One; }
			P3D2 = Min(P1D2, P2D2);
			End = ND2;
			for (Index = 0; Index < End; ++Index)
			{
				Assert::AreEqual(R2[Index], P3D2[Index], NullPtr, LINE_INFO());
			}

			TPoint<ND3, FReal> P1D3, P2D3, P3D3, R3;
			P1D3 = Three;
			P2D3 = Four;
			End = ND3 / 2 + 1;
			for (Index = 0; Index < End; ++Index) { P1D3[Index] = R3[Index] = Two; }
			End = ND3;
			for (; Index < End; ++Index) { P2D3[Index] = R3[Index] = One; }
			P3D3 = Min(P1D3, P2D3);
			End = ND3;
			for (Index = 0; Index < End; ++Index)
			{
				Assert::AreEqual(R3[Index], P3D3[Index], NullPtr, LINE_INFO());
			}

			TPoint<NDN, FReal> P1DN, P2DN, P3DN, RN;
			P1DN = Three;
			P2DN = Four;
			End = NDN / 2 + 1;
			for (Index = 0; Index < End; ++Index) { P1DN[Index] = RN[Index] = Two; }
			End = NDN;
			for (; Index < End; ++Index) { P2DN[Index] = RN[Index] = One; }
			P3DN = Min(P1DN, P2DN);
			End = NDN;
			for (Index = 0; Index < End; ++Index)
			{
				Assert::AreEqual(RN[Index], P3DN[Index], NullPtr, LINE_INFO());
			}
		}

		TEST_METHOD(TestMax)
		{
			const FSize ND1 = 1, ND2 = 2, ND3 = 3, NDN = 4096;
			const FReal Zero = 0, One = 1, Two = 2, Three = 3, Four = 4;
			FSize Index, End;

			TPoint<ND1, FReal> P1D1, P2D1, P3D1, R1;
			P1D1 = Two;
			P2D1 = One;
			End = ND1 / 2 + 1;
			for (Index = 0; Index < End; ++Index) { P1D1[Index] = R1[Index] = Four; }
			End = ND1;
			for (; Index < End; ++Index) { P2D1[Index] = R1[Index] = Three; }
			P3D1 = Max(P1D1, P2D1);
			End = ND1;
			for (Index = 0; Index < End; ++Index)
			{
				Assert::AreEqual(R1[Index], P3D1[Index], NullPtr, LINE_INFO());
			}

			TPoint<ND2, FReal> P1D2, P2D2, P3D2, R2;
			P1D2 = Two;
			P2D2 = One;
			End = ND2 / 2 + 1;
			for (Index = 0; Index < End; ++Index) { P1D2[Index] = R2[Index] = Four; }
			End = ND2;
			for (; Index < End; ++Index) { P2D2[Index] = R2[Index] = Three; }
			P3D2 = Max(P1D2, P2D2);
			End = ND2;
			for (Index = 0; Index < End; ++Index)
			{
				Assert::AreEqual(R2[Index], P3D2[Index], NullPtr, LINE_INFO());
			}

			TPoint<ND3, FReal> P1D3, P2D3, P3D3, R3;
			P1D3 = Two;
			P2D3 = One;
			End = ND3 / 2 + 1;
			for (Index = 0; Index < End; ++Index) { P1D3[Index] = R3[Index] = Four; }
			End = ND3;
			for (; Index < End; ++Index) { P2D3[Index] = R3[Index] = Three; }
			P3D3 = Max(P1D3, P2D3);
			End = ND3;
			for (Index = 0; Index < End; ++Index)
			{
				Assert::AreEqual(R3[Index], P3D3[Index], NullPtr, LINE_INFO());
			}

			TPoint<NDN, FReal> P1DN, P2DN, P3DN, RN;
			P1DN = Two;
			P2DN = One;
			End = NDN / 2 + 1;
			for (Index = 0; Index < End; ++Index) { P1DN[Index] = RN[Index] = Four; }
			End = NDN;
			for (; Index < End; ++Index) { P2DN[Index] = RN[Index] = Three; }
			P3DN = Max(P1DN, P2DN);
			End = NDN;
			for (Index = 0; Index < End; ++Index)
			{
				Assert::AreEqual(RN[Index], P3DN[Index], NullPtr, LINE_INFO());
			}
		}

		TEST_METHOD(TestOppVectorVector)
		{
			const FSize ND1 = 1, ND2 = 2, ND3 = 3, NDN = 4096;
			const FReal Zero = 0, One = 1, Two = 2, Three = 3, Four = 4;
			FSize Index, End;

			TPoint<ND1, FReal> P1D1, P2D1, P3D1, R1;
			P1D1 = Four;
			P2D1 = Two;
			R1 = Two;
			P3D1 = P1D1 - P2D1;
			End = ND1;
			for (Index = 0; Index < End; ++Index)
			{
				Assert::AreEqual(P3D1[Index], R1[Index], NullPtr, LINE_INFO());
			}
			R1 = -Two;
			P3D1 = P2D1 - P1D1;
			for (Index = 0; Index < End; ++Index)
			{
				Assert::AreEqual(P3D1[Index], R1[Index], NullPtr, LINE_INFO());
			}

			TPoint<ND2, FReal> P1D2, P2D2, P3D2, R2;
			P1D2 = Four;
			P2D2 = Two;
			R2 = Two;
			P3D2 = P1D2 - P2D2;
			End = ND2;
			for (Index = 0; Index < End; ++Index)
			{
				Assert::AreEqual(P3D2[Index], R2[Index], NullPtr, LINE_INFO());
			}
			R2 = -Two;
			P3D2 = P2D2 - P1D2;
			for (Index = 0; Index < End; ++Index)
			{
				Assert::AreEqual(P3D2[Index], R2[Index], NullPtr, LINE_INFO());
			}

			TPoint<ND3, FReal> P1D3, P2D3, P3D3, R3;
			P1D3 = Four;
			P2D3 = Two;
			R3 = Two;
			P3D3 = P1D3 - P2D3;
			End = ND3;
			for (Index = 0; Index < End; ++Index)
			{
				Assert::AreEqual(P3D3[Index], R3[Index], NullPtr, LINE_INFO());
			}
			R3 = -Two;
			P3D3 = P2D3 - P1D3;
			for (Index = 0; Index < End; ++Index)
			{
				Assert::AreEqual(P3D3[Index], R3[Index], NullPtr, LINE_INFO());
			}

			TPoint<NDN, FReal> P1DN, P2DN, P3DN, RN;
			P1DN = Four;
			P2DN = Two;
			RN = Two;
			P3DN = P1DN - P2DN;
			End = NDN;
			for (Index = 0; Index < End; ++Index)
			{
				Assert::AreEqual(P3DN[Index], RN[Index], NullPtr, LINE_INFO());
			}
			RN = -Two;
			P3DN = P2DN - P1DN;
			for (Index = 0; Index < End; ++Index)
			{
				Assert::AreEqual(P3DN[Index], RN[Index], NullPtr, LINE_INFO());
			}
		}

		TEST_METHOD(TestOppIntoVectorVector)
		{
			const FSize ND1 = 1, ND2 = 2, ND3 = 3, NDN = 4096;
			const FReal Zero = 0, One = 1, Two = 2, Three = 3, Four = 4;
			FSize Index, End;

			TPoint<ND1, FReal> P1D1, P2D1, R1;
			P1D1 = Four;
			P2D1 = Two;
			R1 = Two;
			P1D1 -= P2D1;
			End = ND1;
			for (Index = 0; Index < End; ++Index)
			{
				Assert::AreEqual(P1D1[Index], R1[Index], NullPtr, LINE_INFO());
			}

			TPoint<ND2, FReal> P1D2, P2D2, R2;
			P1D2 = Four;
			P2D2 = Two;
			R2 = Two;
			P1D2 -= P2D2;
			End = ND2;
			for (Index = 0; Index < End; ++Index)
			{
				Assert::AreEqual(P1D2[Index], R2[Index], NullPtr, LINE_INFO());
			}

			TPoint<ND3, FReal> P1D3, P2D3, R3;
			P1D3 = Four;
			P2D3 = Two;
			R3 = Two;
			P1D3 -= P2D3;
			End = ND3;
			for (Index = 0; Index < End; ++Index)
			{
				Assert::AreEqual(P1D3[Index], R3[Index], NullPtr, LINE_INFO());
			}

			TPoint<NDN, FReal> P1DN, P2DN, RN;
			P1DN = Four;
			P2DN = Two;
			RN = Two;
			P1DN -= P2DN;
			End = NDN;
			for (Index = 0; Index < End; ++Index)
			{
				Assert::AreEqual(P1DN[Index], RN[Index], NullPtr, LINE_INFO());
			}
		}

		TEST_METHOD(TestOppAlphaVector)
		{
			const FSize ND1 = 1, ND2 = 2, ND3 = 3, NDN = 4096;
			const FReal Zero = 0, One = 1, Two = 2, Three = 3, Four = 4;
			FSize Index, End;

			TPoint<ND1, FReal> P1D1, P3D1, R1;
			FReal R1D1;
			P1D1 = Two;
			R1D1 = Four;
			R1 = -Two;
			P3D1 = P1D1 - R1D1;
			End = ND1;
			for (Index = 0; Index < End; ++Index)
			{
				Assert::AreEqual(P3D1[Index], R1[Index], NullPtr, LINE_INFO());
			}
			R1 = Two;
			P3D1 = R1D1 - P1D1;
			for (Index = 0; Index < End; ++Index)
			{
				Assert::AreEqual(P3D1[Index], R1[Index], NullPtr, LINE_INFO());
			}

			TPoint<ND2, FReal> P1D2, P3D2, R2;
			FReal R1D2;
			P1D2 = Two;
			R1D2 = Four;
			R1 = -Two;
			P3D1 = P1D2 - R1D2;
			End = ND2;
			for (Index = 0; Index < End; ++Index)
			{
				Assert::AreEqual(P3D2[Index], R2[Index], NullPtr, LINE_INFO());
			}
			R2 = Two;
			P3D2 = R1D2 - P1D2;
			for (Index = 0; Index < End; ++Index)
			{
				Assert::AreEqual(P3D2[Index], R2[Index], NullPtr, LINE_INFO());
			}

			TPoint<ND3, FReal> P1D3, P3D3, R3;
			FReal R1D3;
			P1D3 = Two;
			R1D3 = Four;
			R3 = -Two;
			P3D3 = P1D3 - R1D3;
			End = ND3;
			for (Index = 0; Index < End; ++Index)
			{
				Assert::AreEqual(P3D3[Index], R3[Index], NullPtr, LINE_INFO());
			}
			R3 = Two;
			P3D3 = R1D3 - P1D3;
			for (Index = 0; Index < End; ++Index)
			{
				Assert::AreEqual(P3D3[Index], R3[Index], NullPtr, LINE_INFO());
			}

			TPoint<NDN, FReal> P1DN, P3DN, RN;
			FReal R1DN;
			P1DN = Two;
			R1DN = Four;
			RN = -Two;
			P3DN = P1DN - R1DN;
			End = NDN;
			for (Index = 0; Index < End; ++Index)
			{
				Assert::AreEqual(P3DN[Index], RN[Index], NullPtr, LINE_INFO());
			}
			RN = Two;
			P3DN = R1DN - P1DN;
			for (Index = 0; Index < End; ++Index)
			{
				Assert::AreEqual(P3DN[Index], RN[Index], NullPtr, LINE_INFO());
			}
		}

		TEST_METHOD(TestOppIntoVectorAlpha)
		{
			const FSize ND1 = 1, ND2 = 2, ND3 = 3, NDN = 4096;
			const FReal Zero = 0, One = 1, Two = 2, Three = 3, Four = 4;
			FSize Index, End;

			TPoint<ND1, FReal> P1D1, R1;
			FReal R1D1;
			P1D1 = Four;
			R1D1 = Two;
			R1 = Two;
			P1D1 -= R1D1;
			End = ND1;
			for (Index = 0; Index < End; ++Index)
			{
				Assert::AreEqual(P1D1[Index], R1[Index], NullPtr, LINE_INFO());
			}

			TPoint<ND2, FReal> P1D2, R2;
			FReal R1D2;
			P1D2 = Four;
			R1D2 = Two;
			R2 = Two;
			P1D2 -= R1D2;
			End = ND2;
			for (Index = 0; Index < End; ++Index)
			{
				Assert::AreEqual(P1D2[Index], R2[Index], NullPtr, LINE_INFO());
			}

			TPoint<ND3, FReal> P1D3, R3;
			FReal R1D3;
			P1D3 = Four;
			R1D3 = Two;
			R3 = Two;
			P1D3 -= R1D3;
			End = ND3;
			for (Index = 0; Index < End; ++Index)
			{
				Assert::AreEqual(P1D3[Index], R3[Index], NullPtr, LINE_INFO());
			}

			TPoint<NDN, FReal> P1DN, RN;
			FReal R1DN;
			P1DN = Four;
			R1DN = Two;
			RN = Two;
			P1DN -= R1DN;
			End = NDN;
			for (Index = 0; Index < End; ++Index)
			{
				Assert::AreEqual(P1DN[Index], RN[Index], NullPtr, LINE_INFO());
			}
		}
	};



}