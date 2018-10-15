#include "pch.h"
#include "Window.h"

#include <QtGui/QtGui>
#include <QtWidgets/QtWidgets>
#include <QtCharts/QtCharts>
#include <QtCore/QtCore>

using namespace MLPrototyping;

namespace MLPrototyping
{
	struct _FWindow
	{
		_FWindow()
		{
			Main = new QMainWindow();
			Chart = new QChart();
			View = new QChartView(Chart, Main);

			Chart->setDropShadowEnabled(False);
			Chart->layout()->setContentsMargins(0, 0, 0, 0);
			Chart->setBackgroundRoundness(0);

			Main->setCentralWidget(View);
		}

		~_FWindow() { Main = NullPtr; Chart = NullPtr; View = NullPtr; }
		
		QPointer<QMainWindow> Main;
		QPointer<QChart> Chart;
		QPointer<QChartView> View;
	};
}

static char** _InitializeArguments(char** Arguments, const int &Count)
{ 
	const char* Name = "MLPrototyping";
	FSize _Size = sizeof(Name);
	Arguments = Make<char*>(Count);
	Arguments[0] = NullPtr;
	Arguments[0] = Copy<char>(Name, NullPtr, _Size);
	return Arguments;
}

FPointer FWindow::_Application = NullPtr;
int FWindow::_ArgumentCount = 1;
char** FWindow::_Arguments = _InitializeArguments(FWindow::_Arguments, FWindow::_ArgumentCount);

FWindow::FWindow() { Title = NullPtr; }

FWindow::~FWindow()
{ 
	if (!_Application) { return;  }
	auto Application = (QApplication *)_Application;

	if (bWait) { _ErrorNo = Application->exec(); } 
	if (Title) { Remove(Title); }
}

FWindow::FMeta::FMeta() { Name = NullPtr; }

FWindow::FMeta::~FMeta() { if (Name) { } }

FWindow FWindow::Default()
{
	FWindow Window;
	Window.Min.X = Window.Min.Y = -8;
	Window.Max.X = Window.Max.Y = 8;
	Window.Origin.X = Window.Origin.Y = 0;
	Window.Width = 720;
	Window.Height = 720;
	Window.bWait = false;
	Window.bHold = false;
	Window.bReconfigure = false;
	Window.Title = NullPtr;
	Window._State = NullPtr;
	Window._UpdateCount = 0;
	Window._ErrorNo = Success;
	return Window;
}

FWindow::FMeta FWindow::FMeta::Default()
{
	FMeta Meta;
	Meta.Type = FMeta::EType::Scatter;
	Meta.Name = NullPtr;
	Meta.Size = 3;
	Meta.Opacity = 1.0;
	return Meta;
}

FVoid FWindow::_Display(const _FData &Data, FWindow &Window)
{
	if (!_Application) { _Application = new QApplication(_ArgumentCount, _Arguments); }
	auto Application = (QApplication *)_Application;

	if (Window._State) { _Update(Data, Window); }
	else { _Make(Data, Window); }
}

FVoid FWindow::_Make(const _FData &Data, FWindow &Window)
{
	_FWindow *State = new _FWindow();
	Window._State = State;
	State->Main->show();
	auto bHold = Window.bHold;
	Window.bHold = False;
	_Update(Data, Window);
	Window.bHold = bHold;
}

FVoid FWindow::_Update(const _FData &Data, FWindow &Window)
{
	auto State = (_FWindow *) Window._State;
	if (!Window.bHold) { State->Chart->removeAllSeries(); }

	QXYSeries *Series = NullPtr;
	
	if (Data.Meta.Type == FWindow::FMeta::EType::Scatter)
	{
		auto Scatter = new QScatterSeries();
		Scatter->setMarkerShape(QScatterSeries::MarkerShapeCircle);
		Scatter->setMarkerSize(Data.Meta.Size);
		Scatter->setBorderColor(Qt::transparent);
		Series = Scatter;
	}

	if (Data.Meta.Type == FWindow::FMeta::EType::Line)
	{
		auto Line = new QLineSeries();
		Series = Line;
	}

	for (const auto& Point : Data.Points) { Series->append(Point.X, Point.Y); }
	Series->setName(Data.Meta.Name);
	Series->setOpacity(Data.Meta.Opacity);
	
	State->Main->setWindowTitle(Window.Title);
	State->Main->setFixedSize(Window.Width, Window.Height);

	State->Chart->addSeries(Series);
	State->Chart->setTitle(Window.Title);
	State->Chart->createDefaultAxes();

	++Window._UpdateCount;
}

FReturn FWindow::Wait()
{
	if (!_Application) { return Success; }
	auto Application = (QApplication *)_Application;
	return Application->exec();
}

