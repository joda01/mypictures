///
/// \file       widget_settings.h
/// \author     Joachim Danmayr
/// \date       2017-08-15
///
/// \copyright  This program is licensed under the
///             European Union Public License 1.1
///             Copyright 2017 by Joachim Danmayr,
///             All rights reserved!
///

#ifndef WIDGET_SETTINGS_H
#define WIDGET_SETTINGS_H

#include "database/settings.h"
#include <QWidget>
#include <QListWidget>
#include "picture/picture.h"
#include "widget_top_menu.h"
#include "learning/learing_algorithm.h"

///
/// \class      WidgetBigPictureView
/// \author     Joachim Danmayr
/// \date       2017-08-15
/// \brief      Shows a big picture
///
class WidgetSettings : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetSettings(WidgetTopMenu *widgetTopMenu, Settings *settings, QWidget *parent = nullptr);

private slots:
    void slotAddFolderPressed();
    void slotRemoveFolderPressed();

private:
    void savePathsToSettings();


    WidgetTopMenu* mWidgetTopMenu;
    Settings *mSettings;
    QListWidget *mPaths;

};

#endif // WIDGET_SETTINGS_H
