///
/// \file       widget_picture_menu.cpp
/// \author     Joachim Danmayr
/// \date       2017-08-15
///
/// \copyright  This program is licensed under the
///             European Union Public License 1.1
///             Copyright 2017 by Joachim Danmayr,
///             All rights reserved!
///

#include "widget_menu_picture.h"

#include <QHBoxLayout>
#include <QToolButton>

///
/// \brief      Constructor
/// \author     Joachim Danmayr
/// \date       2017-08-15
/// \param[in]	parent  Pointer to the parent widget
///
WidgetMenuPicture::WidgetMenuPicture(QWidget *parent) : QWidget(parent)
{

    ////////////////////////////////////////////////////////
    /// Layout settings
    setObjectName("WidgetMenuPicture");
    QHBoxLayout* layout = new QHBoxLayout();
    setLayout(layout);

    QToolButton* buttonPrevPic = new QToolButton();
    buttonPrevPic->setIcon(QIcon(":icons/left_white.png"));
    buttonPrevPic->setCursor(Qt::PointingHandCursor);
    buttonPrevPic->setAutoRaise(true);
    buttonPrevPic->setAutoFillBackground(false);
    connect(buttonPrevPic,SIGNAL(pressed()),this,SLOT(slotButtonPrevPic()));
    layout->addWidget(buttonPrevPic);

    QToolButton* buttonNextPic = new QToolButton();
    buttonNextPic->setIcon(QIcon(":icons/right_white.png"));
    buttonNextPic->setCursor(Qt::PointingHandCursor);
    connect(buttonNextPic,SIGNAL(pressed()),this,SLOT(slotButtonNextPic()));
    layout->addWidget(buttonNextPic);

    setAutoFillBackground(false);
}


void WidgetMenuPicture::slotButtonNextPic()
{
    emit nextPicPressed();
}

void WidgetMenuPicture::slotButtonPrevPic()
{
    emit prevPicPressed();
}
