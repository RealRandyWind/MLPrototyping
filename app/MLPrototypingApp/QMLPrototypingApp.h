#pragma once

#include <MLPrototyping.h>
#include <QtCore\QtCore>
#include <QtGui\QtGui>
#include <QtWidgets\QtWidgets>
#include <QtCharts\QtCharts>

using namespace MLPrototyping;

namespace MLPrototypingApp
{
	class QMLPrototypingApp : public QMainWindow
	{
		Q_OBJECT


	public:
		QMLPrototypingApp();

		~QMLPrototypingApp();


	private:
		CMLPrototyping *API;

		QPainter *Painter;

		QChartView *Canvas;

		QStatusBar* MainStatusBar;

		QScatterSeries *Series;


		/* Menus */
		QMenu* FileMenu;

		QMenu* SelectMenu;

		QMenu* ContextMenu;


		/* Actions */
		QActionGroup* DataActionGroup;

		QActionGroup* ModelActionGroup;


		QAction* ExitAction;

		QAction* GenerateNormalDataAction;

		QAction* GenerateGammaDataAction;


		void CreateMain();

		void CreateActions();

		void CreateMenus();


	protected:
#ifndef QT_NO_CONTEXTMENU
		void contextMenuEvent(QContextMenuEvent *Event) override;
#endif

	public slots:

		void GenerateNormalData();

		void GenerateGammaData();

	};



}