///
/// \file       widget_big_picture_view.cpp
/// \author     Joachim Danmayr
/// \date       2017-08-15
///
/// \copyright  This program is licensed under the
///             European Union Public License 1.1
///             Copyright 2017 by Joachim Danmayr,
///             All rights reserved!
///

#include <QMessageBox>
#include <QHBoxLayout>
#include <QString>
#include <QMessageBox>

#include "widget_big_picture_view.h"

///
/// \brief      Constructor
/// \author     Joachim Danmayr
/// \date       2017-08-15
/// \param[in]  parent  Pointer to the parent class
///
WidgetBigPictureView::WidgetBigPictureView(WidgetTopMenu* widgetTopMenu, WidgetMenuPicture* widgetMenuPic, QWidget *parent) : QWidget(parent),
    mWidgetTopMenu(widgetTopMenu),
    mWidgetMenuPicture(widgetMenuPic)
{

    ////////////////////////////////////////////////////////
    /// Layout settings
    QHBoxLayout* layout = new QHBoxLayout();
    setLayout(layout);

    /// Picture label
    mLabelPicture.setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    mLabelPicture.setScaledContents(true);
    layout->addWidget(&mLabelPicture);


    mWidgetMenuPicture->setParent(this);
}

///
/// \brief      Display a new picture
/// \author     Joachim Danmayr
/// \date       2017-08-16
/// \param[in]	picture reference to the picture
///             which should be shown
///
void WidgetBigPictureView::slotSetPicture(Picture& picture)
{
    QPixmap pic(picture.absoluteFilePath());
    mLabelPicture.setPixmap(pic);
    scaleImage();
    placeMenu();
}

///
/// \brief      Scale image
/// \author     Joachim Danmayr
/// \date       2017-08-16
/// \param[in]	ev  Resize event information
///
void WidgetBigPictureView::scaleImage()
{
    const QPixmap* pic = mLabelPicture.pixmap();
    if(nullptr!=pic){
        float ratio = (float)pic->width()/(float)pic->height();
        float picWidth = (float)height()*(float)ratio;

        // Keep ratio also when widget shrinkedß
        if(width() < maximumWidth()){
            mLabelPicture.setMaximumHeight(width()/ratio);
        }else{
            mLabelPicture.setMaximumWidth(99999999);
        }

        mLabelPicture.setMaximumWidth(picWidth);
    }
}


///
/// \brief      Scale image
/// \author     Joachim Danmayr
/// \date       2017-08-16
/// \param[in]	ev  Resize event information
///
void WidgetBigPictureView::resizeEvent(QResizeEvent* ev)
{
    QWidget::resizeEvent(ev);
    scaleImage();
    placeMenu();
}

///
/// \brief      Places the pictue menu at the buttom of the widget
/// \author     Joachim Danmayr
/// \date       2017-08-19
///
void WidgetBigPictureView::placeMenu()
{
    mWidgetMenuPicture->setGeometry(width()/2-50,height()-100,150,50);
    mWidgetMenuPicture->setStyleSheet(QStringLiteral("QWidget#WidgetMenuPicture{background-color: rgba(0, 0, 0, 180);}"));
    mWidgetMenuPicture->setAutoFillBackground(true);
}
