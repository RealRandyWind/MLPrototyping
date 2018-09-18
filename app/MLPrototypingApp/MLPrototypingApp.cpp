// MLPrototypingApp.cpp : Defines the entry point for the console application.
//

#include <functional>

#include "stdafx.h"
#include "NDev.h"
#include "MLPrototypingApp_Definitions.h"
#include "NN.h"
#include "LVQ1.h"
#include "SMDLVQ.h"
#include <QtWidgets\QApplication>

using namespace MLPrototypingScript;

using namespace NDev;
using namespace NDev::Types;

int main(int ArgumentCount, char** Arguments)
{
	QApplication Application(ArgumentCount, Arguments);

	using FNNF2L3 = LVQ::TNN<2, 3>;
	TData<FNNF2L3::FError> ErrorsNN;
	FNNF2L3 NN;
	NN.UseDefaultParameters();
	MeasureNormal(NN, ErrorsNN, 32, [&NN](auto Series) {
		for (const auto &Prototype : NN.State.Prototypes)
		{
			Series->append(Prototype.Feature[0], Prototype.Feature[1]);
		}
	});



	/*
	using FLVQ1F2L3 = LVQ::TLVQ1<2, 3>;
	TData<FLVQ1F2L3::FError> ErrorsLVQ1;
	FLVQ1F2L3 LVQ1;
	LVQ1.UseDefaultParameters();
	MeasureNormal(LVQ1, ErrorsNN, 32, [&LVQ1](auto Series) {
		for (const auto &Prototype : LVQ1.State.Prototypes)
		{
			Series->append(Prototype.Feature[0], Prototype.Feature[1]);
		}
	});

	using FSMDLVQF2L3 = LVQ::TSMDLVQ<2, 3>;
	TData<FSMDLVQF2L3::FError> ErrorsSMDLVQ;
	FSMDLVQF2L3 SMDLVQ;
	SMDLVQ.UseDefaultParameters();
	MeasureNormal(SMDLVQ, ErrorsNN, 32, [&SMDLVQ](auto Series) {
		for (const auto &Prototype : SMDLVQ.State.Prototypes)
		{
			Series->append(Prototype.Feature[0], Prototype.Feature[1]);
		}
	});
	*/
	return Application.exec();
}

