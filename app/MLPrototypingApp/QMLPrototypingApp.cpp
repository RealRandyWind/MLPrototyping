#include "stdafx.h"
#include "QMLPrototypingApp.h"
#include "QMLPrototypingApp.moc"
#include "MLPrototyping_Math.h"
#include "NN.h"
#include "MLPrototyping_Generate.h"

#define MLPrototypingApp_Title tr("MLPrototyping")
#define MLPrototypingApp_FileTitle tr("File")
#define MLPrototypingApp_SelectTitle tr("Select")
#define MLPrototypingApp_GenerateTitle tr("Generate")
#define MLPrototypingApp_ExitTile tr("Exit")
#define MLPrototypingApp_GenerateNormalDataTile tr("Normal Data")
#define MLPrototypingApp_GenerateGammaDataTile tr("Gamma Data")
#define MLPrototypingApp_GenerateRingDataTile tr("Ring Data")
#define MLPrototypingApp_GenerateUniformDataTile tr("Uniform Data")
#define MLPrototypingApp_ScatterPlotTile tr("Scatter Plot")
#define MLPrototypingApp_WindowSize QSize(720, 720)
#define MLPrototypingApp_Disabled false
#define MLPrototypingApp_Enable true
#define MLPrototypingApp_Visible true
#define MLPrototypingApp_Invisible false

using namespace MLPrototypingApp;
using namespace MLPrototyping;

QMLPrototypingApp::QMLPrototypingApp() :
	API(CMLPrototyping::Instance()),
	Canvas(new QChartView(new QChart(), this)),
	Chart(Canvas->chart()),
	Series(new QScatterSeries())
{
	Chart->addSeries(Series);
	CreateMain();
	CreateActions();
	CreateMenus();
}

QMLPrototypingApp::~QMLPrototypingApp()
{

}

void QMLPrototypingApp::CreateMain()
{
	resize(MLPrototypingApp_WindowSize);
	setWindowTitle(MLPrototypingApp_Title);
	setCentralWidget(Canvas);
	MainStatusBar = statusBar();
}

void QMLPrototypingApp::CreateActions()
{
	ExitAction = new QAction(MLPrototypingApp_ExitTile, this);
	ExitAction->setShortcut(QKeySequence::Quit);
	connect(ExitAction, SIGNAL(triggered()), this, SLOT(close()));

	GenerateNormalDataAction = new QAction(MLPrototypingApp_GenerateNormalDataTile, this);
	GenerateNormalDataAction->setShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::ALT + Qt::Key_N));
	connect(GenerateNormalDataAction, SIGNAL(triggered()), this, SLOT(GenerateNormalData()));

	GenerateGammaDataAction = new QAction(MLPrototypingApp_GenerateGammaDataTile, this);
	GenerateGammaDataAction->setShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::ALT + Qt::Key_G));
	connect(GenerateGammaDataAction, SIGNAL(triggered()), this, SLOT(GenerateGammaData()));

	GenerateRingDataAction = new QAction(MLPrototypingApp_GenerateRingDataTile, this);
	GenerateRingDataAction->setShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::ALT + Qt::Key_R));
	connect(GenerateRingDataAction, SIGNAL(triggered()), this, SLOT(GenerateRingData()));

	GenerateUniformDataAction = new QAction(MLPrototypingApp_GenerateUniformDataTile, this);
	GenerateUniformDataAction->setShortcut(QKeySequence(Qt::CTRL + Qt::SHIFT + Qt::ALT + Qt::Key_U));
	connect(GenerateUniformDataAction, SIGNAL(triggered()), this, SLOT(GenerateUniformData()));

	DataActionGroup = new QActionGroup(this);
	DataActionGroup->addAction(GenerateNormalDataAction);
	DataActionGroup->addAction(GenerateGammaDataAction);
	DataActionGroup->addAction(GenerateRingDataAction);
	DataActionGroup->addAction(GenerateUniformDataAction);
}

void QMLPrototypingApp::CreateMenus()
{
	FileMenu = menuBar()->addMenu(MLPrototypingApp_FileTitle);
	FileMenu->addSeparator();
	FileMenu->addAction(ExitAction);

	SelectMenu = menuBar()->addMenu(MLPrototypingApp_SelectTitle);
	SelectMenu->setEnabled(MLPrototypingApp_Disabled);

	GenerateMenu = menuBar()->addMenu(MLPrototypingApp_GenerateTitle);
	GenerateMenu->setEnabled(MLPrototypingApp_Enable);
	GenerateMenu->addActions(DataActionGroup->actions());

	ContextMenu = new QMenu(this);
	ContextMenu->addActions(DataActionGroup->actions());
}

void QMLPrototypingApp::GenerateNormalData()
{
	using FParameters = TNormalDataParameters<2, 3>;

	TData<FParameters::FFeature> Data;
	TSequence<FParameters> List;

	Series->clear();
	List.Reserve(3, true);
	List[0] = FParameters::Default();
	List[0].N = 1024;
	List[0].SD = 1.2;
	List[0].Norm = 1;
	List[0].Mean = { -3, 4 };
	List[1] = FParameters::Default();
	List[1].N = 1024;
	List[1].SD = 1;
	List[1].Norm = 1;
	List[1].Mean = { -4, -4 };
	List[2] = FParameters::Default();
	List[2].N = 1024;
	List[2].SD = 0.8;
	List[2].Norm = 1;
	List[2].Mean = { 3, 0 };

	ModelData(Data, List);

	for (auto &Point : Data)
	{
		Series->append(Point[0], Point[1]);
	}

	Series->setName(MLPrototypingApp_GenerateNormalDataTile);
	Series->setMarkerShape(QScatterSeries::MarkerShapeCircle);
	Series->setMarkerSize(6.0);
	Series->setBorderColor(Qt::transparent);

	Chart->legend()->setMarkerShape(QLegend::MarkerShapeFromSeries);
	Chart->setTitle(MLPrototypingApp_ScatterPlotTile);
	Chart->setDropShadowEnabled(false);
	Chart->createDefaultAxes();
	Chart->axisX()->setRange(-8, 8);
	Chart->axisY()->setRange(-8, 8);
}

void QMLPrototypingApp::GenerateGammaData()
{
	using FParameters = TGammaDataParameters<2, 3>;

	TData<FParameters::FFeature> Data;
	FParameters Item;

	Series->clear();
	Item = FParameters::Default();
	Item.N = 1024;
	Item.Alpha = 1.2;
	Item.Beta = 2.8;
	Item.Norm = 0.6;
	Item.Mean = { -6, -6 };

	ModelData(Data, Item);

	for (auto &Point : Data)
	{
		Series->append(Point[0], Point[1]);
	}

	Series->setName(MLPrototypingApp_GenerateGammaDataTile);
	Series->setMarkerShape(QScatterSeries::MarkerShapeCircle);
	Series->setMarkerSize(6.0);
	Series->setBorderColor(Qt::transparent);

	Chart->legend()->setMarkerShape(QLegend::MarkerShapeFromSeries);
	Chart->setTitle(MLPrototypingApp_ScatterPlotTile);
	Chart->setDropShadowEnabled(false);
	Chart->createDefaultAxes();
	Chart->axisX()->setRange(-8, 8);
	Chart->axisY()->setRange(-8, 8);
}

void QMLPrototypingApp::GenerateRingData()
{
	using FParameters = TRingDataParameters<2, 3>;

	TData<FParameters::FFeature> Data;
	TSequence<FParameters> List;
	
	Series->clear();
	List.Reserve(2, true);
	List[0] = FParameters::Default();
	List[0].N = 1024;
	List[0].SD = 1.0;
	List[0].Readius = 4;
	List[0].Norm = 1;
	List[0].Mean = { 2, 2 };
	List[1] = FParameters::Default();
	List[1].N = 1024;
	List[1].SD = 0.5;
	List[1].Readius = 2;
	List[1].Norm = 1;
	List[1].Mean = { -4, -4 };

	ModelData(Data, List);

	for (auto &Point : Data)
	{		
		Series->append(Point[0], Point[1]);
	}

	Series->setName(MLPrototypingApp_GenerateRingDataTile);
	Series->setMarkerShape(QScatterSeries::MarkerShapeCircle);
	Series->setMarkerSize(6.0);
	Series->setBorderColor(Qt::transparent);

	Chart->legend()->setMarkerShape(QLegend::MarkerShapeFromSeries);
	Chart->setTitle(MLPrototypingApp_ScatterPlotTile);
	Chart->setDropShadowEnabled(false);
	Chart->createDefaultAxes();
	Chart->axisX()->setRange(-8, 8);
	Chart->axisY()->setRange(-8, 8);
}

void QMLPrototypingApp::GenerateUniformData()
{
	using FParameters = TUniformDataParameters<2, 3>;

	TData<FParameters::FFeature> Data;
	TSequence<FParameters> List;

	Series->clear();
	List.Reserve(2, true);
	List[0] = FParameters::Default();
	List[0].N = 1024;
	List[0].Radius = 5;
	List[0].Norm = 1;
	List[0].Mean = { 2, 2 };
	List[1] = FParameters::Default();
	List[1].N = 1024;
	List[1].Radius = 3;
	List[1].Norm = 1;
	List[1].Mean = { -4, -4 };

	ModelData(Data, List);

	for (auto &Point : Data)
	{
		Series->append(Point[0], Point[1]);
	}

	Series->setName(MLPrototypingApp_GenerateUniformDataTile);
	Series->setMarkerShape(QScatterSeries::MarkerShapeCircle);
	Series->setMarkerSize(6.0);
	Series->setBorderColor(Qt::transparent);

	Chart->legend()->setMarkerShape(QLegend::MarkerShapeFromSeries);
	Chart->setTitle(MLPrototypingApp_ScatterPlotTile);
	Chart->setDropShadowEnabled(false);
	Chart->createDefaultAxes();
	Chart->axisX()->setRange(-8, 8);
	Chart->axisY()->setRange(-8, 8);
}

#ifndef QT_NO_CONTEXTMENU
void QMLPrototypingApp::contextMenuEvent(QContextMenuEvent *Event)
{
	ContextMenu->exec(Event->globalPos());
}
#endif