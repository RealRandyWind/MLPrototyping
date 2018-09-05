#pragma once

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


using namespace MLPrototyping;

namespace MLPrototypingScript
{
	const size_t _NMinimum = 8;

	using FRingDataParametersF2L3 = TRingDataParameters<2, 3>;

	using FGammaDataParametersF2L3 = TRingDataParameters<2, 3>;

	using FNormalDataParametersF2L3 = TRingDataParameters<2, 3>;

	using FUniformDataParametersF2L3 = TRingDataParameters<2, 3>;

	using FModelF2L3 = TModel<2, 3>;

	QMainWindow *DisplayMeasure(QScatterSeries *Train, QScatterSeries *Validate, QScatterSeries *Prototypes, QScatterSeries *Error, QLineSeries* ErrorEpochs, QList<QLineSeries*> *Paths)
	{
		auto Layout = new QGridLayout();
		auto InfoLayout = new QVBoxLayout();
		auto Window = new QMainWindow();
		auto Widget = new QWidget(Window);
		auto Info = new QWidget(Window);
		auto ChartData = new QChart();
		auto ChartError = new QPolarChart();
		auto ChartErrorEpochs = new QChart();
		auto ChartViewData = new QChartView(ChartData, Widget);
		auto ChartViewError = new QChartView(ChartError, Widget);
		auto ChartViewErrorEpochs = new QChartView(ChartErrorEpochs, Widget);

		if (!Train) { Train = new QScatterSeries(); }
		if (!Validate) { Validate = new QScatterSeries(); }
		if (!Prototypes) { Prototypes = new QScatterSeries(); }
		if (!Error) { Error = new QScatterSeries(); }
		if (!ErrorEpochs) { ErrorEpochs = new QLineSeries(); }
		if (!Paths) { Paths = new QList<QLineSeries *>(); }

		ChartViewData->setFixedSize(720, 720);
		ChartViewError->setFixedSize(360, 360);

		ChartData->addSeries(Train);
		ChartData->addSeries(Validate);
		ChartError->addSeries(Error);
		ChartErrorEpochs->addSeries(ErrorEpochs);

		Train->setName("Train");
		Train->setMarkerShape(QScatterSeries::MarkerShapeCircle);
		Train->setMarkerSize(3.0);
		Train->setOpacity(0.7);
		Train->setBorderColor(Qt::transparent);

		Validate->setName("Validate");
		Validate->setMarkerShape(QScatterSeries::MarkerShapeCircle);
		Validate->setMarkerSize(3.0);
		Validate->setOpacity(0.7);
		Validate->setBorderColor(Qt::transparent);

		Error->setName("Error");
		Error->setMarkerShape(QScatterSeries::MarkerShapeCircle);
		Error->setMarkerSize(3.0);
		Error->setBorderColor(Qt::transparent);

		ErrorEpochs->setName("Error Epochs");

		ChartErrorEpochs->legend()->setMarkerShape(QLegend::MarkerShapeFromSeries);
		ChartErrorEpochs->setTitle("Line Plot Epochs vs Error");
		ChartErrorEpochs->setDropShadowEnabled(false);
		ChartErrorEpochs->createDefaultAxes();

		ChartError->legend()->setMarkerShape(QLegend::MarkerShapeFromSeries);
		ChartError->setTitle("Scatter Plot Error");
		ChartError->setDropShadowEnabled(false);
		ChartError->createDefaultAxes();

		ChartData->legend()->setMarkerShape(QLegend::MarkerShapeFromSeries);
		ChartData->setTitle("Scatter Plot Data");
		ChartData->setDropShadowEnabled(false);
		ChartData->createDefaultAxes();
		ChartData->axisX()->setRange(-8, 8);
		ChartData->axisY()->setRange(-8, 8);

		Info->setLayout(InfoLayout);
		InfoLayout->addWidget(new QLabel("Model info"));

		Layout->addWidget(ChartViewData, 0, 0, 2, 1);
		Layout->addWidget(ChartViewError, 0, 1);
		Layout->addWidget(Info, 0, 2);
		Layout->addWidget(ChartViewErrorEpochs, 1, 1, 1, 2);
		
		Widget->setLayout(Layout);
		Window->setWindowTitle("Measure Model Normal Data");
		Window->setCentralWidget(Widget);

		Window->setFixedSize(1280, 720);
		Window->show();

		return Window;
	}


	QMainWindow *MeasureNormal(FModelF2L3 &Model, size_t Factor = 1)
	{
		using FModel = FModelF2L3;
		using FParameters = FNormalDataParametersF2L3;

		TData<FModel::FSample> Train, Validate;
		TData<FModel::FError> Errors;

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
		auto SeriesError = new QScatterSeries();

		for (const auto &Point : Train) { SeriesTrain->append(Point.Feature[0], Point.Feature[1]); }
		for (const auto &Point : Validate) { SeriesValidate->append(Point.Feature[0], Point.Feature[1]); }
		for (const auto &Point : Errors)
		{
			SeriesValidate->append(Norm(Point.Value), Norm(Point.Label));
		}

		return DisplayMeasure(SeriesTrain, SeriesValidate, nullptr, SeriesError, nullptr, nullptr);
	}

}