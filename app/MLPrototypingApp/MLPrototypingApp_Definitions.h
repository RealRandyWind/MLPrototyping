#pragma once

#include <functional>

#include "MLPrototyping_Types.h"
#include "MLPrototyping_Math.h"
#include "MLPrototyping_Parameters.h"
#include "MLPrototyping_Generate.h"
#include "Model.h"
#include "Point.h"

#include <QtCore\QtCore>
#include <QtGui\QtGui>
#include <QtWidgets\QtWidgets>
#include <QtCharts\QtCharts>
#include <QtSvg\QtSvg>


using namespace MLPrototyping;

namespace MLPrototypingScript
{
	const size_t _NMinimum = 8;

	using FxScatterSeries = std::function<void(QScatterSeries *)> ;

	using FRingDataParametersF2L3 = TRingDataParameters<2, 3>;

	using FGammaDataParametersF2L3 = TRingDataParameters<2, 3>;

	using FNormalDataParametersF2L3 = TRingDataParameters<2, 3>;

	using FUniformDataParametersF2L3 = TRingDataParameters<2, 3>;

	using FModelF2L3 = TModel<2, 3>;

	QMainWindow *DisplayMeasure(QScatterSeries *Train, QScatterSeries *Validate, QScatterSeries *Prototypes)
	{
		auto Window = new QMainWindow();
		auto Chart = new QChart();
		auto ChartView = new QChartView(Chart, Window);

		if (!Train) { Train = new QScatterSeries(); }
		if (!Validate) { Validate = new QScatterSeries(); }
		if (!Prototypes) { Prototypes = new QScatterSeries(); }

		Train->setName("Train");
		Train->setMarkerShape(QScatterSeries::MarkerShapeCircle);
		Train->setMarkerSize(3.0);
		Train->setOpacity(0.9);
		Train->setBorderColor(Qt::transparent);

		Validate->setName("Validate");
		Validate->setMarkerShape(QScatterSeries::MarkerShapeCircle);
		Validate->setMarkerSize(3.0);
		Validate->setOpacity(0.7);
		Validate->setBorderColor(Qt::transparent);

		Prototypes->setName("Prototype");
		Prototypes->setMarkerShape(QScatterSeries::MarkerShapeCircle);
		Prototypes->setMarkerSize(8.0);
		Prototypes->setOpacity(0.4);
		Prototypes->setBorderColor(Qt::transparent);

		Chart->addSeries(Train);
		Chart->addSeries(Validate);
		Chart->addSeries(Prototypes);

		Chart->legend()->setMarkerShape(QLegend::MarkerShapeFromSeries);
		Chart->setTitle("Scatter Plot Data");
		Chart->setDropShadowEnabled(false);
		Chart->createDefaultAxes();
		Chart->axisX()->setRange(-8, 8);
		Chart->axisY()->setRange(-8, 8);

		Window->setWindowTitle("Measure Model Normal Data");
		Window->setCentralWidget(ChartView);
		Window->setFixedSize(720, 720);
		Window->show();
		return Window;
	}


	QMainWindow *MeasureNormal(FModelF2L3 &Model, TData<FModelF2L3::FError> &Errors, size_t Factor = 1, FxScatterSeries Populate = nullptr)
	{
		using FModel = FModelF2L3;
		using FParameters = FNormalDataParametersF2L3;

		TData<FModel::FSample> Train, Validate;

		/* Preparing Model Data Parameters */
		TSequence<FParameters> List(3, true);
		
		List[0] = FParameters::Default();
		List[0].N = Factor * _NMinimum;
		List[0].SD = 1.2;
		List[0].Norm = 1;
		List[0].Mean = { -3, 4 };

		List[1] = FParameters::Default();
		List[1].N = Factor * _NMinimum;
		List[1].SD = 1;
		List[1].Norm = 1;
		List[1].Mean = { -4, -4 };

		List[2] = FParameters::Default();
		List[2].N = Factor * _NMinimum;
		List[2].SD = 0.8;
		List[2].Norm = 1;
		List[2].Mean = { 3, 0 };

		/* Generate Model Data */
		ModelData(Train, List, 1);
		ModelData(Validate, List, 2);

		/* Run Model */
		if (!Model.Initialized()) { Model.Initialize(); }
		Model.Train(Train);
		Model.Validate(Validate, Errors);

		/* Prepairing To Display Results */
		auto SeriesTrain = new QScatterSeries();
		auto SeriesValidate = new QScatterSeries();
		auto SeriesPrototype = new QScatterSeries();

		for (const auto &Point : Train) { SeriesTrain->append(Point.Feature[0], Point.Feature[1]); }
		for (const auto &Point : Validate) { SeriesValidate->append(Point.Feature[0], Point.Feature[1]); }
		if (Populate) { Populate(SeriesPrototype); }

		return DisplayMeasure(SeriesTrain, SeriesValidate, SeriesPrototype);
	}



}