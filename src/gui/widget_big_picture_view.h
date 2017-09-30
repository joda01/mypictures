///
/// \file       widget_big_picture_view.h
/// \author     Joachim Danmayr
/// \date       2017-08-15
///
/// \copyright  This program is licensed under the
///             European Union Public License 1.1
///             Copyright 2017 by Joachim Danmayr,
///             All rights reserved!
///

#ifndef WIDGET_BIG_PICTURE_VIEW_VIEW_H
#define WIDGET_BIG_PICTURE_VIEW_VIEW_H

#include <QWidget>
#include <QLabel>
#include "picture/picture.h"
#include "widget_top_menu.h"
#include "widget_menu_picture.h"

///
/// \class      WidgetBigPictureView
/// \author     Joachim Danmayr
/// \date       2017-08-15
/// \brief      Shows a big picture
///
class WidgetBigPictureView : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetBigPictureView(WidgetTopMenu *widgetTopMenu, WidgetMenuPicture*, QWidget *parent = nullptr);

private slots:
    void slotSetPicture(Picture& picture);

private:
    void resizeEvent(QResizeEvent* ev);
    void scaleImage();
    void placeMenu();
    WidgetTopMenu* mWidgetTopMenu;
    WidgetMenuPicture* mWidgetMenuPicture;
    QLabel mLabelPicture;
};

#endif // WIDGET_BIG_PICTURE_VIEW_VIEW_H
