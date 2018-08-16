#include "stdafx.h"
#include "QMLPrototypingApp.h"
#include "QMLPrototypingApp.moc"
#include "MLPrototyping_Math.h";

#define MLPrototypingApp_Title tr("MLPrototyping")
#define MLPrototypingApp_FileTitle tr("File")
#define MLPrototypingApp_SelectTitle tr("Select")
#define MLPrototypingApp_ExitTile tr("Exit")
#define MLPrototypingApp_GenerateNormalDataTile tr("Generate Normal")
#define MLPrototypingApp_GenerateGammaDataTile tr("Generate Gamma")
#define MLPrototypingApp_WindowSize QSize(720, 720)
#define MLPrototypingApp_ImageFormat QImage::Format_RGBA8888
#define MLPrototypingApp_Disabled false
#define MLPrototypingApp_Enable true
#define MLPrototypingApp_Visible true
#define MLPrototypingApp_Invisible false

using namespace MLPrototypingApp;
using namespace MLPrototyping;

QMLPrototypingApp::QMLPrototypingApp() :
	API(CMLPrototyping::GetInstance()),
	Canvas(new QChartView(new QChart(), this)),
	Series(new QScatterSeries())
{
	Canvas ->chart()->addSeries(Series);
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

	DataActionGroup = new QActionGroup(this);
	DataActionGroup->addAction(GenerateNormalDataAction);
	DataActionGroup->addAction(GenerateGammaDataAction);
}

void QMLPrototypingApp::CreateMenus()
{
	FileMenu = menuBar()->addMenu(MLPrototypingApp_FileTitle);
	FileMenu->addSeparator();
	FileMenu->addAction(ExitAction);

	SelectMenu = menuBar()->addMenu(MLPrototypingApp_SelectTitle);
	SelectMenu->setEnabled(MLPrototypingApp_Enable);
	SelectMenu->addActions(DataActionGroup->actions());

	ContextMenu = new QMenu(this);
	ContextMenu->addActions(DataActionGroup->actions());
}

void QMLPrototypingApp::GenerateNormalData()
{
	TData<FNormalDataParameters::FPoint> Data;
	TSequence<FNormalDataParameters> List;

	auto API = CMLPrototyping::GetInstance();
	
	Series->clear();
	Series->setName("Normal Data");
	Series->setMarkerShape(QScatterSeries::MarkerShapeCircle);
	Series->setMarkerSize(6.0);
	Series->setBorderColor(Qt::transparent);

	List.Reserve(3, true);
	List[0].N = 1024;
	List[0].SD = 1.2;
	List[0].Norm = 1;
	List[0].Mean = { -3, 4 };
	List[1].N = 1024;
	List[1].SD = 1;
	List[1].Norm = 1;
	List[1].Mean = { -4, -4 };
	List[2].N = 1024;
	List[2].SD = 0.8;
	List[2].Norm = 1;
	List[2].Mean = { 3, 0 };

	API->ModelData(Data, List);

	for (auto &Point : Data)
	{
		Series->append(Point[0], Point[1]);
	}

	auto Chart = Canvas->chart();
	auto Legend = Chart->legend();
	Chart->setTitle("Scatter Plot 2D");
	Chart->setDropShadowEnabled(false);
	Chart->createDefaultAxes();
	Chart->axisX()->setRange(-8, 8);
	Chart->axisY()->setRange(-8, 8);
	Legend->setMarkerShape(QLegend::MarkerShapeFromSeries);
}

void QMLPrototypingApp::GenerateGammaData()
{
	TData<FGammaDataParameters::FPoint> Data;
	TSequence<FGammaDataParameters> List;

	auto API = CMLPrototyping::GetInstance();

	Series->clear();
	Series->setName("Gamma Data");
	Series->setMarkerShape(QScatterSeries::MarkerShapeCircle);
	Series->setMarkerSize(6.0);
	Series->setBorderColor(Qt::transparent);

	List.Reserve(2, true);
	List[0].N = 1024;
	List[0].Alpha = 1.2;
	List[0].Beta = 2.8;
	List[0].Norm = 0.6;
	List[0].Mean = { -6, -6 };
	List[0].Along = { 1, 1 };
	List[1].N = 1024;
	List[1].Alpha = 2.0;
	List[1].Beta = 2.0;
	List[1].Norm = 0.6;
	List[1].Mean = { -2, 0 };
	List[1].Along = { 1, 0 };

	API->ModelData(Data, List);

	for (auto &Point : Data)
	{
		Series->append(Point[0], Point[1]);
	}

	auto Chart = Canvas->chart();
	auto Legend = Chart->legend();
	Chart->setTitle("Scatter Plot 2D");
	Chart->setDropShadowEnabled(false);
	Chart->createDefaultAxes();
	Chart->axisX()->setRange(-8, 8);
	Chart->axisY()->setRange(-8, 8);
	Legend->setMarkerShape(QLegend::MarkerShapeFromSeries);
}

#ifndef QT_NO_CONTEXTMENU
void QMLPrototypingApp::contextMenuEvent(QContextMenuEvent *Event)
{
	ContextMenu->exec(Event->globalPos());
}
#endif