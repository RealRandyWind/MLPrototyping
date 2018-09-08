// MLPrototypingApp.cpp : Defines the entry point for the console application.
//

#include <functional>

#include "stdafx.h"
#include "MLPrototypingApp_Definitions.h"
#include "Data.h"
#include "NN.h"
#include <QtWidgets\QApplication>

using namespace MLPrototypingScript;

int main(int ArgumentCount, char** Arguments)
{
	QApplication Application(ArgumentCount, Arguments);

	using FNNF2L3 = LVQ::TNN<2, 3>;
	TData<FNNF2L3::FError> Errors;
	FNNF2L3 NN;
	NN.Parameters.KNearest = 3;
	auto Window = MeasureNormal(NN, Errors, 64, [&NN](auto List) {
		for (const auto &Prototype : NN.State.Prototypes)
		{
			List->append(Prototype.Feature[0], Prototype.Feature[1]);
		}
	});

	return Application.exec();
}

