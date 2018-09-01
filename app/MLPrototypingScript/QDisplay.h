#pragma once

#include <MLPrototyping.h>
#include <QtCore\QtCore>
#include <QtGui\QtGui>
#include <QtWidgets\QtWidgets>
#include <QtCharts\QtCharts>

namespace MLPrototypingScript
{
	class QDisplay : public QMainWindow
	{
		Q_OBJECT


	public:
		QDisplay();

		~QDisplay();


	private:
		QPainter *Painter;

		QStatusBar* MainStatusBar;


		/* Menus */
		QMenu* FileMenu;

		QMenu* ContextMenu;


		/* Actions */
		QAction* ExitAction;


		void CreateMain();

		void CreateActions();

		void CreateMenus();


	protected:
#ifndef QT_NO_CONTEXTMENU
		void contextMenuEvent(QContextMenuEvent *Event) override;
#endif

	public slots:

	};



}