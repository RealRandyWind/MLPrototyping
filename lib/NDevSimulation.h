#pragma once

#include "NDevTypes.h"
#include "NDevResource.h"
#include "NDevData.h"
#include "NDevPoint.h"
#include "NDevMathPoint.h"

namespace NDev
{
	using namespace Types;

	template<FSize SizePoint>
	struct TSimulation : public CResource
	{
		using FPoint = TPoint<SizePoint, FReal>;

        using FOnVisualizeResult = TFunction<void(TData<FPoint> &)>;
		
		FOnVisualizeResult OnVisualizeResult;
		FSize _NSteps;
		FBoolean _bInitialized, _bContinue;

		TSimulation()
		{
			_bInitialized = False;
			_bContinue = False;
			_NSteps = 0;
		}

		~TSimulation() { }

		FBoolean Initialized()
		{
			return _bInitialized;
		}

		FSize PointSize()
		{
			return SizePoint;
		}

		const FSize PointSize() const
		{
			return SizePoint;
		}

		FSize NSteps()
		{
			return _NSteps;
		}

		const FSize NSteps() const
		{
			return _NSteps;
		}

		FVoid Initialize()
		{
			_bInitialized = False;
			_NSteps = 0;
			_Initialize();
			_bInitialized = True;
		}

		FVoid Start(TData<FPoint> &Result)
		{
			if (!_bInitialized) { return; }

            _bContinue = True;
            while(_bContinue)
            {
				++_NSteps;
                _Step(Result);
            }
			_Result(Result);
		}

		FVoid Stop()
		{
			_bContinue = False;
		}
		

	protected:
		virtual FVoid _Initialize() = 0;

		virtual FVoid _Step(TData<FPoint> &) = 0;

		virtual FVoid _Result(TData<FPoint> &) = 0;


	};



}