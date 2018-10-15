#pragma once

#include "NDevTypes.h"
#include "NDevDefinitions.h"
#include "NDevPoint.h"
#include "NDevData.h"
#include "NDevModel.h"
#include "NDevMathAliases.h"

namespace MLPrototyping
{
	using namespace NDev::Types;
	using namespace NDev;

	struct FWindow
	{
		struct FMeta
		{
			enum class EType
			{
				_Unknown = NDev::Types::Unknown,
				Scatter,
				Line,
				_Size
			};

			EType Type;
			FString Name;
			FReal Size, Opacity;

			FMeta();

			~FMeta();

			static FMeta Default();
		};

		struct _FData
		{
			using FPoint = TPoint2D<FReal>;
			using FPoints = TIterator<FPoint>;

			FPoints Points;
			FMeta Meta;
		};

		FSize Width, Height, _UpdateCount;
		FBoolean bWait, bHold, bReconfigure;
		TPoint2D<FReal> Min, Max, Origin;
		FString Title;
		FReturn _ErrorNo;
		FPointer _State;

		FWindow();

		~FWindow();

		template<FSize SizeFeature, FSize SizeLabel>
		static FVoid Display(const TData<typename TModel<SizeFeature, SizeLabel>::FSample> &, FWindow &, const FMeta = FMeta::Default());

		template<FSize SizeFeature, FSize SizeLabel>
		static FVoid Display(const TData<typename TModel<SizeFeature, SizeLabel>::FError> &, FWindow &, const FMeta = FMeta::Default());

		static FWindow Default();

		static FVoid _Display(const _FData &, FWindow &);

		static FVoid _Make(const _FData &, FWindow &);

		static FVoid _Update(const _FData &, FWindow &);

		static FReturn Wait();

		static FPointer _Application;
		static char** _Arguments;
		static int _ArgumentCount;
	};
	
	template<FSize SizeFeature, FSize SizeLabel>
	FVoid FWindow::Display(const TData<typename TModel<SizeFeature, SizeLabel>::FSample> &Data, FWindow &Window, const FMeta Meta)
	{
		const FSize SizeOf = sizeof(_FData::FPoint);
		_FData _Data;
		auto _Descriptor = Data.Descriptor();

		if (SizeFeature < 2) { exit(Failure); }

		_Descriptor.Stride = _Descriptor.Stride + _Descriptor.SizeOf - SizeOf;
		_Descriptor.SizeOf = SizeOf;
		_Data.Meta = Meta;
		_Data.Points = _FData::FPoints(_Descriptor);
		_Display(_Data, Window);
	}

	template<FSize SizeFeature, FSize SizeLabel>
	FVoid FWindow::Display(const TData<typename TModel<SizeFeature, SizeLabel>::FError> &Data, FWindow &Window, const FMeta Meta)
	{
		const FSize SizeOf = sizeof(_FData::FPoint);
		_FData _Data;
		auto _Descriptor = Data.Descriptor();

		if (SizeFeature < 2) { exit(Failure); }

		_Descriptor.Stride = _Descriptor.Stride + _Descriptor.SizeOf - SizeOf;
		_Descriptor.SizeOf = SizeOf;
		_Data.Meta = Meta;
		_Data.Points = _FData::FPoints(_Descriptor);
		_Display(_Data, Window);
	}

}