#include "stdafx.h"
#include "QDisplay.h"
#include "QDisplay.moc"

#define MLPrototypingApp_Title tr("MLPrototyping")
#define MLPrototypingApp_FileTitle tr("File")
#define MLPrototypingApp_ExitTile tr("Exit")
#define MLPrototypingApp_WindowSize QSize(720, 720)
#define MLPrototypingApp_Disabled false
#define MLPrototypingApp_Enable true
#define MLPrototypingApp_Visible true
#define MLPrototypingApp_Invisible false

using namespace MLPrototypingScript;

QDisplay::QDisplay()
{
	CreateMain();
	CreateActions();
	CreateMenus();
}

QDisplay::~QDisplay()
{

}

void QDisplay::CreateMain()
{
	resize(MLPrototypingApp_WindowSize);
	setWindowTitle(MLPrototypingApp_Title);
	MainStatusBar = statusBar();
}

void QDisplay::CreateActions()
{
	ExitAction = new QAction(MLPrototypingApp_ExitTile, this);
	ExitAction->setShortcut(QKeySequence::Quit);
	connect(ExitAction, SIGNAL(triggered()), this, SLOT(close()));
}

void QDisplay::CreateMenus()
{
	FileMenu = menuBar()->addMenu(MLPrototypingApp_FileTitle);
	FileMenu->addSeparator();
	FileMenu->addAction(ExitAction);

	ContextMenu = new QMenu(this);
}

#ifndef QT_NO_CONTEXTMENU
void QDisplay::contextMenuEvent(QContextMenuEvent *Event)
{
	ContextMenu->exec(Event->globalPos());
}
#endif