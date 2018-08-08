#pragma once

#include <MLPrototyping.h>
#include <QtCore\QtCore>
#include <QtGui\QtGui>
#include <QtWidgets\QtWidgets>

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

		QLabel *Canvas;

		QStatusBar* MainStatusBar;


		/* Menus */
		QMenu* FileMenu;

		QMenu* ProjectMenu;

		QMenu* SelectMenu;

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


	};



}