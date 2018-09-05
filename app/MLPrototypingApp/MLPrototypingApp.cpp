// MLPrototypingApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "MLPrototypingApp_Definitions.h"
#include "NN.h"
#include <QtWidgets\QApplication>

using namespace MLPrototypingScript;

int main(int ArgumentCount, char** Arguments)
{
	QApplication Application(ArgumentCount, Arguments);
	LVQ::TNN<2, 3> NN;
	NN.Parameters.KNearest = 3;
	NN.Parameters.NPrototypes = 3;
	auto Window = MeasureNormal(NN, 64);
	return Application.exec();
}

