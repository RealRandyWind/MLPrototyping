// MLPrototypingApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <QtWidgets\QApplication>
#include "QMLPrototypingApp.h"

using namespace MLPrototypingApp;

int main(int ArgumentCount, char** Arguments)
{
	QApplication Application(ArgumentCount, Arguments);
	QMLPrototypingApp MainWindow;
	MainWindow.show();
	return Application.exec();
}

