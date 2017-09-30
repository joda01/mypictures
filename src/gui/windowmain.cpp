///
/// \file       windowmain.cpp
/// \author     Joachim Danmayr
/// \date       2017-08-15
///
/// \copyright  This program is licensed under the
///             European Union Public License 1.1
///             Copyright 2017 by Joachim Danmayr,
///             All rights reserved!
///

#include "windowmain.h"
#include "borderlayout.h"

WindowMain::WindowMain(Settings* settings, Database *database, DatabaseWorker *databaseWorker, QWidget *parent) : QMainWindow(parent),
    mSettings(settings),
    mDatabase(database),
    mDatabaseWorker(databaseWorker)
{
    QWidget* centralWidget = new QWidget(this);
    BorderLayout*  centralLayout = new BorderLayout(this->centralWidget(),0,-1);
    centralLayout->setObjectName("CentralWidget");

    mWidgetTopMenu = new WidgetTopMenu();
    mWidgetMenuPicture = new WidgetMenuPicture();
    mWidgetTableView = new WidgetTableView(settings,mWidgetTopMenu,mWidgetMenuPicture,database);
    mWidgetBigPicture = new WidgetBigPictureView(mWidgetTopMenu,mWidgetMenuPicture,this);
    mWidgetPicInfo = new WidgetPictureInfo(mWidgetTopMenu,mWidgetTableView,database,this);
    mWidgetSettings = new WidgetSettings(mWidgetTopMenu,settings);


    centralLayout->addWidget(mWidgetTopMenu,BorderLayout::North);

    /// Stacked widget
    mStackedWidget = new QStackedWidget(this);
    mStackedWidget->addWidget(mWidgetTableView);
    mStackedWidget->addWidget(mWidgetBigPicture);
    mStackedWidget->addWidget(mWidgetSettings);
    centralLayout->addWidget(mStackedWidget,BorderLayout::Center);

    /// Picture info
    centralLayout->addWidget(mWidgetPicInfo,BorderLayout::East);

    centralWidget->setLayout(centralLayout);
    setCentralWidget(centralWidget);
    setMinimumSize(1024,768);


    /// Signals and slots
    /// New picture selected to load
    connect(mWidgetTableView,SIGNAL(signalOpenNewPicture(Picture&)),this,SLOT(slotNewBigPictureLoaded(Picture&)));
    connect(mWidgetTableView,SIGNAL(signalOpenNewPicture(Picture&)),mWidgetBigPicture,SLOT(slotSetPicture(Picture&)));
    connect(mWidgetTableView,SIGNAL(signalPictureSelected(Picture&)),mWidgetPicInfo,SLOT(slotSetPicture(Picture&)));

    /// Menu buttons
    connect(mWidgetTopMenu,SIGNAL(buttonBackPressed()),SLOT(slotBackToGridView()));
    connect(mWidgetTopMenu,SIGNAL(buttonSettingsPressed()),SLOT(slotOpenSettingsWidget()));

}


///
/// \brief      Slot which is called when a new big
///             picture is loaded
/// \author     Joachim Danmayr
/// \date       2017-08-16
///
void WindowMain::slotNewBigPictureLoaded(Picture&)
{
    centralWidget()->setStyleSheet(".QWidget, WidgetTopMenu, WidgetTopMenu > QToolButton, QPlainTextEdit{background-color:black;color:gray;}");
    centralWidget()->setAutoFillBackground(true);

    mWidgetTopMenu->setBlackStyle(true);
    mWidgetPicInfo->setBlackStyle(true);
    mStackedWidget->setCurrentIndex(1);
}

///
/// \brief      Switch back to grid view
/// \author     Joachim Danmayr
/// \date       2017-08-16
///
void WindowMain::slotBackToGridView()
{
    centralWidget()->setStyleSheet(".QWidget, WidgetTopMenu, WidgetTopMenu > QToolButton, QPlainTextEdit{background-color:white;color:black;}");
    centralWidget()->setAutoFillBackground(true);

    mWidgetTopMenu->setBlackStyle(false);
    mWidgetPicInfo->setBlackStyle(false);
    mWidgetTopMenu->setViewButtonsVisible(true);
    mStackedWidget->setCurrentIndex(0);
}

///
/// \brief      Open the settings widget
/// \author     Joachim Danmayr
/// \date       2017-08-16
///
void WindowMain::slotOpenSettingsWidget()
{
    mWidgetTopMenu->setViewButtonsVisible(false);
    mStackedWidget->setCurrentIndex(2);
}
