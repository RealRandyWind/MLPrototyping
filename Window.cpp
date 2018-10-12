#include "pch.h"
#include "Window.h"

#include "QtWidgets/QApplication"
#include "QtWidgets/QMainWindow"
#include "QtCharts/QtCharts"
#include "QtCore/QPointer"


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
			Chart->createDefaultAxes();
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
	const char* Name = "ModelingAndSimulation";
	FSize _Size = sizeof(Name);
	Arguments = NDev::Make<char*>(Count);
	Arguments[0] = NullPtr;
	Arguments[0] = NDev::Copy<char>(Name, NullPtr, _Size);
	return Arguments;
}

FPointer FWindow::_Application = NullPtr;
int FWindow::_ArgumentCount = 1;
char** FWindow::_Arguments = _InitializeArguments(FWindow::_Arguments, FWindow::_ArgumentCount);

FWindow FWindow::Default()
{
	FWindow Window;
	Window.Min.X = Window.Min.Y = -8;
	Window.Max.X = Window.Max.Y = 8;
	Window.Origin.X = Window.Origin.Y = 0;
	Window.Width = 720;
	Window.Height = 720;
	Window.X = Window.Y = 32;
	Window.bWait = false;
	Window.bHold = false;
	Window.bReconfigure = false;
	Window.Title = NullPtr;
	Window._State = NullPtr;
	Window._UpdateCount = 0;
	Window._ErrorNo = Success;
	return Window;
}

FVoid FWindow::Display(const NDev::FDescriptor &Buffer, FWindow &Window)
{
	if (!_Application) { _Application = new QApplication(_ArgumentCount, _Arguments); }
	auto Application = (QApplication *)_Application;

	if (Window._State) { _Update(Buffer, Window); }
	else { _Make(Buffer, Window); }
	
	if (Window.bWait) { Window._ErrorNo = Application->exec(); }
}

FVoid FWindow::_Make(const NDev::FDescriptor &Buffer, FWindow &Window)
{
	_FWindow *State = new _FWindow();
	
	State->Main->show();
	Window._State = State;
}

FVoid FWindow::_Update(const NDev::FDescriptor &Buffer, FWindow &Window)
{
	if (!Window.bHold) { /* Clear Screen */ }
	++Window._UpdateCount;
}

FReturn FWindow::Wait()
{
	if (!_Application) { return Success; }
	auto Application = (QGuiApplication *)_Application;
	return Application->exec();
}

