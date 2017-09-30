///
/// \file       widget_picture_info.cpp
/// \author     Joachim Danmayr
/// \date       2017-08-15
///
/// \copyright  This program is licensed under the
///             European Union Public License 1.1
///             Copyright 2017 by Joachim Danmayr,
///             All rights reserved!
///

#include <QPushButton>
#include <QVBoxLayout>
#include <QString>
#include <QMessageBox>
#include <QFormLayout>
#include <QListWidget>
#include "picture/picture.h"
#include <QStringList>

#include "widget_picture_info.h"
#include "dialog_list.h"
#include "dialog_geo_location.h"

///
/// \brief      Constructor
/// \author     Joachim Danmayr
/// \date       2017-08-15
/// \param[in]  parent  Pointer to the parent class
///
WidgetPictureInfo::WidgetPictureInfo(WidgetTopMenu* widgetTopMenu, WidgetTableView* widgetTableView, Database *database,  QWidget *parent) : QWidget(parent),
    mWidgetTopMenu(widgetTopMenu),
    mWidgetTableView(widgetTableView),
    mDatabase(database)
{
    setObjectName("WidgetPictureInfo");
    setAutoFillBackground(false);

    ////////////////////////////////////////////////////////
    /// Layout settings
    QVBoxLayout* layout = new QVBoxLayout();
    setMaximumWidth(0);
    /// Main Menu
    connect(mWidgetTopMenu,SIGNAL(signalPictureInfoPressed(bool)),this,SLOT(slotPictureInfoButtonPressed(bool)));
    connect(&mLearningAlgorithm,SIGNAL(analyseFinished(QStringList)),this,SLOT(slotLearningFinished(QStringList)));

    //////////////////////////////////////////////////////
    /// TAGS
    /// Text edit
    {
        QVBoxLayout* layoutTags = new QVBoxLayout();
        mTagSuggestions = new QPlainTextEdit();
        layoutTags->addWidget(mTagSuggestions);
    }
    layout->addWidget(createExifWidget());

    layout->addStretch(1);


    setLayout(layout);

}


///
/// \brief      Black style: White buttons black background
/// \author     Joachim Danmayr
/// \date       2017-08-24
/// \param[in]	blackStyle true = white buttons
///
void WidgetPictureInfo::setBlackStyle(bool blackStyle)
{
    if(true == blackStyle){
        QToolButton* tagIcon = mWidgetExif->findChild<QToolButton*>("TextTagsIcon");
        tagIcon->setIcon(QIcon(":/icons/tags_white.png"));

        tagIcon = mWidgetExif->findChild<QToolButton*>("TextAlbumIcon");
        tagIcon->setIcon(QIcon(":/icons/stack_of_photos_white.png"));

        tagIcon = mWidgetExif->findChild<QToolButton*>("TextCameraModelIcon");
        tagIcon->setIcon(QIcon(":/icons/camera_white.png"));

        tagIcon = mWidgetExif->findChild<QToolButton*>("TextDateTimeIcon");
        tagIcon->setIcon(QIcon(":/icons/clock_white.png"));

        tagIcon = mWidgetExif->findChild<QToolButton*>("TextApertureIcon");
        tagIcon->setIcon(QIcon(":/icons/aperture_white.png"));

        tagIcon = mWidgetExif->findChild<QToolButton*>("TextApertureIcon");
        tagIcon->setIcon(QIcon(":/icons/aperture_white.png"));

        tagIcon = mWidgetExif->findChild<QToolButton*>("TextGPSIcon");
        tagIcon->setIcon(QIcon(":/icons/marker_filled_white.png"));


    }else{
        QToolButton* tagIcon = mWidgetExif->findChild<QToolButton*>("TextTagsIcon");
        tagIcon->setIcon(QPixmap(":/icons/tags.png"));

        tagIcon = mWidgetExif->findChild<QToolButton*>("TextAlbumIcon");
        tagIcon->setIcon(QIcon(":/icons/stack_of_photos.png"));

        tagIcon = mWidgetExif->findChild<QToolButton*>("TextCameraModelIcon");
        tagIcon->setIcon(QIcon(":/icons/camera.png"));

        tagIcon = mWidgetExif->findChild<QToolButton*>("TextDateTimeIcon");
        tagIcon->setIcon(QIcon(":/icons/clock.png"));

        tagIcon = mWidgetExif->findChild<QToolButton*>("TextApertureIcon");
        tagIcon->setIcon(QIcon(":/icons/aperture.png"));

        tagIcon = mWidgetExif->findChild<QToolButton*>("TextGPSIcon");
        tagIcon->setIcon(QIcon(":/icons/marker_filled.png"));

    }
}

///
/// \brief      Creates the widgets which allows
///             to display and manipulate the
///             EXIF data of the picture
/// \author     Joachim Danmayr
/// \date       2017-08-23
///
QWidget* WidgetPictureInfo::createExifWidget()
{
    mWidgetExif = new QWidget(this);
    QGridLayout *layout = new QGridLayout(mWidgetExif);
    // layout->setHorizontalSpacing(40);
    // layout->setVerticalSpacing(10);
    //////////////////////////////////////

    //layout->addWidget(new QLabel(""),mExifGridLayoutRowCounter,0,1,2);
    /// mExifGridLayoutRowCounter+=1;


    QToolButton* buttonAddtoAlbum = addElementToExifWidget(layout,"TextAlbum",":/icons/stack_of_photos.png",tr("Album name"));
    connect(buttonAddtoAlbum,SIGNAL(pressed()),this,SLOT(slotSetAlbum()));

    QToolButton* buttonTags = addElementToExifWidget(layout,"TextTags",":/icons/tags.png",tr("Tags"));
    buttonTags->setPopupMode(QToolButton::ToolButtonPopupMode::InstantPopup);
    QAction* buttonAddTags = new QAction(buttonTags);
    buttonAddTags->setText(tr("Add"));
    buttonTags->addAction(buttonAddTags);

    QAction* buttonRemoveTags = new QAction(buttonTags);
    buttonRemoveTags->setText(tr("Remove"));
    buttonTags->addAction(buttonRemoveTags);

    connect(buttonAddTags,SIGNAL(triggered(bool)),this,SLOT(slotSetTags(bool)));
    connect(buttonRemoveTags,SIGNAL(triggered(bool)),this,SLOT(slotRemoveTags(bool)));

    addElementToExifWidget(layout,"TextCameraModel",":/icons/camera.png",tr("Camera information"));
    addElementToExifWidget(layout,"TextDateTime",":/icons/clock.png",tr("Time"));
    addElementToExifWidget(layout,"TextAperture",":/icons/aperture.png",tr("Aperture"));

    QToolButton* buttonGPS = addElementToExifWidget(layout,"TextGPS",":/icons/marker_filled.png",tr("Coordinates"));
    connect(buttonGPS,SIGNAL(pressed()),this,SLOT(slotSetGPS()));


    mWidgetExif->setLayout(layout);
    return mWidgetExif;
}

///
/// \brief      Adds an element with Icon and textfield
/// \author     Joachim Danmayr
/// \date       2017-08-23
///
QToolButton* WidgetPictureInfo::addElementToExifWidget(QGridLayout *layout,QString name, QString icon, QString placeHolder)
{
    QToolButton* l1 = new QToolButton(mWidgetExif);
    QIcon img(icon);
    QString nameLblImg(name);
    nameLblImg.append("Icon");
    l1->setObjectName(nameLblImg);
    l1->setIcon(img);
    l1->setIconSize(QSize(24,24));
    l1->setCursor(Qt::PointingHandCursor);
    QPlainTextEdit* t1 = new QPlainTextEdit(mWidgetExif);
    t1->setPlaceholderText(placeHolder);
    t1->setLineWrapMode(QPlainTextEdit::LineWrapMode::NoWrap);
    t1->setFrameShape(QPlainTextEdit::Shape::NoFrame);
    t1->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    t1->setSizeAdjustPolicy(QPlainTextEdit::SizeAdjustPolicy::AdjustToContents);
    t1->setReadOnly(true);
    t1->setObjectName(name);
    layout->addWidget(l1,mExifGridLayoutRowCounter,0,1,1, Qt::AlignTop);
    layout->addWidget(t1,mExifGridLayoutRowCounter,1,1,1);
    mExifGridLayoutRowCounter+=1;
    return l1;
}

///
/// \brief      Adds a button element
/// \author     Joachim Danmayr
/// \date       2017-08-23
///
QToolButton* WidgetPictureInfo::addElementToExifWidgetWithButton(QGridLayout *layout,QString text, QString name, QString icon)
{
    QToolButton* button = new QToolButton();
    button->setCursor(Qt::PointingHandCursor);
    button->setObjectName(name);
    button->setText(text);
    button->setIcon(QIcon(icon));
    button->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
    layout->addWidget(button,mExifGridLayoutRowCounter,0,1,2, Qt::AlignLeft);
    mExifGridLayoutRowCounter+=1;
    return button;

}

///
/// \brief      Adds a sepperator line
/// \author     Joachim Danmayr
/// \date       2017-08-23
///
void WidgetPictureInfo::addLine(QGridLayout *layout)
{
    QFrame* line = new QFrame(mWidgetExif);
    line->setObjectName(QStringLiteral("line"));
    line->setFrameShape(QFrame::HLine);
    line->setFrameShadow(QFrame::Sunken);
    layout->addWidget(new QLabel("-------------------"),mExifGridLayoutRowCounter,0,1,2);
    mExifGridLayoutRowCounter++;
}

///
/// \brief      The picture info buton has been pressed
/// \author     Joachim Danmayr
/// \date       2017-08-19
/// \param[in]	active true if widget should be shown
///
void WidgetPictureInfo::slotPictureInfoButtonPressed(bool active)
{
    if(true == active){
        setMaximumWidth(300);
        setMinimumWidth(300);
        loadPictureInfo();
    }else{
        setMinimumWidth(0);
        setMaximumWidth(0);
    }
}

///
/// \brief      Display a new picture
/// \author     Joachim Danmayr
/// \date       2017-08-16
/// \param[in]	picture reference to the picture
///
void WidgetPictureInfo::slotSetPicture(Picture& picture)
{
    mActPicture = &picture;
    loadPictureInfo();
}

///
/// \brief      Set tags for the selected picture
/// \author     Joachim Danmayr
/// \date       2017-08-16
///
void WidgetPictureInfo::slotSetTags(bool)
{
    DialogList* di = new DialogList();
    QStringList newTags = di->showDialog(mDatabase->SelectTags());

    if(newTags.size()>0 && mActPicture){
        mActPicture->AddTags(newTags);
        for(auto elem:mWidgetTableView->selectedElements()){
            Picture* picture  = dynamic_cast<Picture*>(VPtr<PicturelistEntry>::asPtr(elem.data()));
            if(picture){
                picture->AddTags(newTags);
            }
        }
        QPlainTextEdit* textEdit = mWidgetExif->findChild<QPlainTextEdit*>("TextTags");
        if(textEdit && mActPicture){
            textEdit->setPlainText(mActPicture->tags().join(";"));
        }
    }
    delete di;
}

///
/// \brief      Removed tags for the selected picture
/// \author     Joachim Danmayr
/// \date       2017-08-16
///
void WidgetPictureInfo::slotRemoveTags(bool)
{
    // Fetch all tags from the selected pictures
    QStringList tagsFromSelectedPictures;
    tagsFromSelectedPictures.clear();
    for(auto elem:mWidgetTableView->selectedElements()){
        Picture* picture  = dynamic_cast<Picture*>(VPtr<PicturelistEntry>::asPtr(elem.data()));
        if(picture){
            tagsFromSelectedPictures.append(picture->tags());
        }
    }
    tagsFromSelectedPictures.removeDuplicates();

    DialogList* di = new DialogList();
    QStringList tagsToRemove = di->showDialog(tagsFromSelectedPictures,true,false);

    if(tagsToRemove.size()>0 && mActPicture){
        mActPicture->RemoveTags(tagsToRemove);
        for(auto elem:mWidgetTableView->selectedElements()){
            Picture* picture  = dynamic_cast<Picture*>(VPtr<PicturelistEntry>::asPtr(elem.data()));
            if(picture){
                picture->RemoveTags(tagsToRemove);
            }
        }
        QPlainTextEdit* textEdit = mWidgetExif->findChild<QPlainTextEdit*>("TextTags");
        if(textEdit && mActPicture){
            textEdit->setPlainText(mActPicture->tags().join(";"));
        }
    }
    delete di;
}

///
/// \brief      Set album for the selected picture
/// \author     Joachim Danmayr
/// \date       2017-08-16
///
void WidgetPictureInfo::slotSetAlbum()
{
    DialogList* di = new DialogList();
    QStringList newTags = di->showDialog(mDatabase->SelectAlbums(),false);

    if(newTags.size()>0 && mActPicture){
        mActPicture->SetAlbum(newTags.at(0));
        for(auto elem:mWidgetTableView->selectedElements()){
            Picture* picture  = dynamic_cast<Picture*>(VPtr<PicturelistEntry>::asPtr(elem.data()));
            if(picture){
                picture->SetAlbum(newTags.at(0));
            }
        }
        QPlainTextEdit* textEdit = mWidgetExif->findChild<QPlainTextEdit*>("TextAlbum");
        if(textEdit && mActPicture){
            textEdit->setPlainText(newTags.at(0));
        }
    }
    delete di;
}

///
/// \brief      Set album for the selected picture
/// \author     Joachim Danmayr
/// \date       2017-08-16
///
void WidgetPictureInfo::slotSetGPS()
{
    if(mActPicture){
        DialogGeoLocation* di = new DialogGeoLocation();
        QGeoLocation location =  di->showDialog(mActPicture->geoLocation());
        delete di;
    }
}

///
/// \brief      Load all information about the selected picture
/// \author     Joachim Danmayr
/// \date       2017-08-19
///
void WidgetPictureInfo::loadPictureInfo()
{
    if(maximumWidth()>0){
        mTagSuggestions->clear();
        mTagSuggestions->appendPlainText(tr("Analyse picture..."));
        if(mActPicture){

            mActPicture->readExif();
            QPlainTextEdit* textEdit = mWidgetExif->findChild<QPlainTextEdit*>("TextTags");
            if(textEdit){
                textEdit->setPlainText(mActPicture->tags().join(";"));
            }

            textEdit = mWidgetExif->findChild<QPlainTextEdit*>("TextAlbum");
            if(textEdit){
                textEdit->setPlainText(mActPicture->album());
            }

            textEdit= mWidgetExif->findChild<QPlainTextEdit*>("TextCameraModel");
            if(textEdit){
                textEdit->setPlainText(mActPicture->cameraModel());
            }

            textEdit = mWidgetExif->findChild<QPlainTextEdit*>("TextDateTime");
            if(textEdit){
                textEdit->setPlainText(mActPicture->datePhotographing().toString());
            }

            textEdit = mWidgetExif->findChild<QPlainTextEdit*>("TextAperture");
            if(textEdit){
                QString info = mActPicture->aperture();
                info.append("\n").append(mActPicture->exposure()).append("\n").append(mActPicture->iso());
                textEdit->setPlainText(info);
            }

            textEdit = mWidgetExif->findChild<QPlainTextEdit*>("TextGPS");
            if(textEdit){
                QGeoLocation loc = mActPicture->geoLocation();
                QString textTemp = loc.coordinate().toString(QGeoCoordinate::CoordinateFormat::Degrees);
                textTemp.append("\n").append(loc.address().city()).append("\n").append(loc.address().street()).append("\n").append(loc.address().countryCode());
                textEdit->setPlainText(textTemp);
            }

            //mLearningAlgorithm.execute(mActPicture->absoluteFilePath());
        }
    }
}

///
/// \brief      Is triggered when the
///             pictue analyse threadhas been finished
/// \author     Joachim Danmayr
/// \date       2017-08-23
///
void WidgetPictureInfo::slotLearningFinished(QStringList suggestionList)
{
    mTagSuggestions->clear();
    mTagSuggestions->appendPlainText(suggestionList.join(";"));
}




