// MLPrototypingScript.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "MLPrototyping_Types.h"
#include "MLPrototyping_Math.h"
#include "Data.h"
#include "Sequence.h"

#include <QtWidgets\QApplication>
#include "QDisplay.h"
#include "Generate.h"


using namespace MLPrototypingScript;



int main(int ArgumentCount, char** Arguments)
{
	QApplication Application(ArgumentCount, Arguments);
	QDisplay MainWindow;
	return Application.exec();
}


