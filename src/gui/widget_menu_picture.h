///
/// \file       widget_menu_picture.h
/// \author     Joachim Danmayr
/// \date       2017-08-15
///
/// \copyright  This program is licensed under the
///             European Union Public License 1.1
///             Copyright 2017 by Joachim Danmayr,
///             All rights reserved!
///

#ifndef WIDGET_MENU_PICTURE_H
#define WIDGET_MENU_PICTURE_H

#include <QWidget>
#include <QLineEdit>
#include <QGroupBox>
#include <QRadioButton>


///
/// \class      WidgetMenuPicture
/// \author     Joachim Danmayr
/// \date       2017-08-15
/// \brief      This menu is shown when the picture is shown
///             big. It contains a back and orev button.
///
class WidgetMenuPicture : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetMenuPicture(QWidget *parent = nullptr);

signals:
    void nextPicPressed();
    void prevPicPressed();

public slots:
    void slotButtonNextPic();
    void slotButtonPrevPic();

};

#endif // WIDGET_TOP_MENU_H
