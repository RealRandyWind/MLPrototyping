#include "stdafx.h"
#include "QMLPrototypingApp.h"
#include "QMLPrototypingApp.moc"

#define MLPrototypingApp_Title tr("MLPrototyping")
#define MLPrototypingApp_FileTitle tr("File")
#define MLPrototypingApp_SelectTitle tr("Select")
#define MLPrototypingApp_ProjectTitle tr("Project")
#define MLPrototypingApp_ExitTile tr("Exit")
#define MLPrototypingApp_WindowSize QSize(1080, 720)
#define MLPrototypingApp_ImageFormat QImage::Format_RGBA8888
#define MLPrototypingApp_Disabled false
#define MLPrototypingApp_Enable true
#define MLPrototypingApp_Visible true
#define MLPrototypingApp_Invisible false

using namespace MLPrototypingApp;

QMLPrototypingApp::QMLPrototypingApp() :
	//API(CMLPrototyping::GetInstance()),
	Canvas(new QLabel(this))
{
	CreateMain();
	CreateActions();
	CreateMenus();
}

QMLPrototypingApp::~QMLPrototypingApp()
{

}

void QMLPrototypingApp::CreateMain()
{
	resize(MLPrototypingApp_WindowSize);
	setWindowTitle(MLPrototypingApp_Title);
	setCentralWidget(Canvas);
	MainStatusBar = statusBar();
}

void QMLPrototypingApp::CreateActions()
{
	ExitAction = new QAction(MLPrototypingApp_ExitTile, this);
	ExitAction->setShortcut(QKeySequence::Quit);
	connect(ExitAction, SIGNAL(triggered()), this, SLOT(close()));
}

void QMLPrototypingApp::CreateMenus()
{
	FileMenu = menuBar()->addMenu(MLPrototypingApp_FileTitle);
	FileMenu->addSeparator();
	FileMenu->addAction(ExitAction);

	ProjectMenu = menuBar()->addMenu(MLPrototypingApp_ProjectTitle);
	ProjectMenu->setEnabled(MLPrototypingApp_Disabled);

	SelectMenu = menuBar()->addMenu(MLPrototypingApp_SelectTitle);
	SelectMenu->setEnabled(MLPrototypingApp_Disabled);

	ContextMenu = new QMenu(this);
}

#ifndef QT_NO_CONTEXTMENU
void QMLPrototypingApp::contextMenuEvent(QContextMenuEvent *Event)
{
	ContextMenu->exec(Event->globalPos());
}
#endif