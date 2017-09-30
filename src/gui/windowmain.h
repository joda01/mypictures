///
/// \file       windowmain.h
/// \author     Joachim Danmayr
/// \date       2017-08-15
///
/// \copyright  This program is licensed under the
///             European Union Public License 1.1
///             Copyright 2017 by Joachim Danmayr,
///             All rights reserved!
///

#ifndef WINDOWMAIN_H
#define WINDOWMAIN_H

#include "database/settings.h"
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QMainWindow>
#include "widget_top_menu.h"
#include "widget_table_view.h"
#include "widget_big_picture_view.h"
#include "widget_picture_info.h"
#include "widget_settings.h"
#include "database/database.h"
#include "database/database_worker.h"

///
/// \class      WindowMain
/// \author     Joachim Danmayr
/// \date       2017-08-05
/// \brief		Main window class
///
class WindowMain : public QMainWindow
{
    Q_OBJECT
public:
    explicit WindowMain(Settings* settings, Database*, DatabaseWorker*,QWidget *parent = nullptr);

signals:

public slots:
    void slotNewBigPictureLoaded(Picture &);
    void slotBackToGridView();
    void slotOpenSettingsWidget();

private:
    Settings* mSettings;
    Database *mDatabase;
    DatabaseWorker *mDatabaseWorker;

    WidgetTopMenu* mWidgetTopMenu;
    WidgetMenuPicture* mWidgetMenuPicture;
    WidgetBigPictureView* mWidgetBigPicture;
    WidgetTableView* mWidgetTableView;
    WidgetPictureInfo* mWidgetPicInfo;
    WidgetSettings* mWidgetSettings;
    QStackedWidget* mStackedWidget;


};

#endif // WINDOWMAIN_H
