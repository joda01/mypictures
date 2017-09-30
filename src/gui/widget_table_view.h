///
/// \file       widget_table_view.h
/// \author     Joachim Danmayr
/// \date       2017-08-15
///
/// \copyright  This program is licensed under the
///             European Union Public License 1.1
///             Copyright 2017 by Joachim Danmayr,
///             All rights reserved!
///

#ifndef WIDGET_TABLE_VIEW_H
#define WIDGET_TABLE_VIEW_H

#include <QWidget>
#include <QSlider>
#include "table_model.h"
#include "table_view.h"
#include "widget_top_menu.h"
#include "widget_menu_picture.h"
#include "picture/picture.h"
#include "database/settings.h"


///
/// \class      WidgetTableView
/// \author     Joachim Danmayr
/// \date       2017-08-15
/// \brief      WidgetTableView
///
class WidgetTableView : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetTableView(Settings* settings, WidgetTopMenu* widgetTopMenu,WidgetMenuPicture*, Database *database, QWidget *parent = nullptr);
    QModelIndexList selectedElements();

signals:
    void signalOpenNewPicture(Picture& picture);
    void signalPictureSelected(Picture& picture);

private slots:
    void setThumbnailSize(int value);
    void startSearch(QString text);
    void nextPicture();
    void prevPicture();
    void openSelectedTableElement(QModelIndex index);
    void slotCurrentIndexChanged(QModelIndex index);
    void slotSetTagsToSelectedelements(QStringList tags);
    void slotBackButtonPressed();
    void slotViewChanged(WidgetTopMenu::View view);

private:

    WidgetTopMenu* mWidgetTopMenu;
    WidgetMenuPicture* mWidgetMenuPicture;
    Settings* mSettings;
    Database* mDatabase;
    TableModel* mTableModel;
    TableView mTableView;
    QSlider*  mSlider;

    Database* mCopy=nullptr;
    WidgetTopMenu::View mActView=WidgetTopMenu::View::Pictures;
    QString mActSearchText;


};

#endif // WIDGET_TABLE_VIEW_H
