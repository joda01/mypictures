///
/// \file       widget_picture_info.h
/// \author     Joachim Danmayr
/// \date       2017-08-15
///
/// \copyright  This program is licensed under the
///             European Union Public License 1.1
///             Copyright 2017 by Joachim Danmayr,
///             All rights reserved!
///

#ifndef WIDGET_PICTURE_INFO_H
#define WIDGET_PICTURE_INFO_H

#include <QWidget>
#include <QPlainTextEdit>
#include "picture/picture.h"
#include "widget_top_menu.h"
#include "learning/learing_algorithm.h"
#include "widget_table_view.h"

#include <QLabel>
#include <QGridLayout>
#include <QPushButton>
#include <QToolButton>

///
/// \class      WidgetBigPictureView
/// \author     Joachim Danmayr
/// \date       2017-08-15
/// \brief      Shows a big picture
///
class WidgetPictureInfo : public QWidget
{
    Q_OBJECT
public:
    explicit WidgetPictureInfo(WidgetTopMenu *widgetTopMenu, WidgetTableView*,Database *database, QWidget *parent = nullptr);
    void setBlackStyle(bool blackStyle);


private slots:
    void slotSetPicture(Picture& picture);
    void slotSetTags(bool);
    void slotRemoveTags(bool);
    void slotSetAlbum();
    void slotSetGPS();
    void slotPictureInfoButtonPressed(bool);
    void slotLearningFinished(QStringList);


private:
    QWidget* createExifWidget();
    void loadPictureInfo();
    QToolButton * addElementToExifWidget(QGridLayout *layout, QString name, QString icon, QString placeHolder);
    QToolButton *addElementToExifWidgetWithButton(QGridLayout *layout, QString text, QString name, QString icon);
    void addLine(QGridLayout *layout);

    WidgetTopMenu* mWidgetTopMenu;
    WidgetTableView* mWidgetTableView;
    Database* mDatabase;

    QWidget* mWidgetExif;

    QPlainTextEdit* mTagSuggestions;

    Picture* mActPicture=nullptr;
    LearingAlgorithm mLearningAlgorithm;
    int mExifGridLayoutRowCounter = 0;

};

#endif // WIDGET_PICTURE_INFO_H
